#include "StdAfx.h"
#include "Log.h"

/************************************************************************
                            静态变量
************************************************************************/
// 临界区扣护变量
static CRITICAL_SECTION s_csLog;
// GetLastError错误码
static int              s_iLastErrorCode;
// 模块名/文件名/行号
static CString          s_strModuleName;
static CString          s_strFileName;
static int              s_iLineNum;
// 打印级别
static BOOL             s_bEnableLog;
static ELogLevel        s_eLogLevel;
static ELogFileSize     s_eLogFileSize;
static CString          s_astrLevel[MAX_LEVEL_NUM] = {"",
                                                      "MSG",
                                                      "WARN",
                                                      "ERR",
                                                      "FAIL"};
// 打印缓存区
static CString          s_strLogBuf;


/************************************************************************
                            静态函数声明
************************************************************************/
static void LogArchive(void);
static int GetSizeInBytes(ELogFileSize eLogFileSize);


/************************************************************************
                            函数实现
************************************************************************/
void LogInit(void)
{
    InitializeCriticalSection(&s_csLog);
    SetEnableLog(FALSE);
    SetLogLevel(L_MSG);
    SetLogFileSize(LOG_FILE_SIZE_256K);
    CreateDirectory("log", NULL);
}

void LogBase(const char *pchModuleName, const char *pchFileName, int iLineNum)
{
    // 进入临界区保护，在LogMsg函数中退出保护
    EnterCriticalSection(&s_csLog);
    s_iLastErrorCode = GetLastError();
    s_strModuleName = pchModuleName;
    s_strFileName = pchFileName;
    s_iLineNum = iLineNum;
}

void LogMsg(const ELogLevel eLogLevel, const char *pchFormat,
            const char *pchArg1, const char *pchArg2, int iArg3)
{
    LogMsg2Buf_prepare();
    LogMsg2Buf_start(eLogLevel, pchFormat, pchArg1, pchArg2, iArg3);
    LogMsg2Buf_clear();
    LogBufFlush();
}

void LogMsg2Buf_prepare(void)
{
    s_strLogBuf.Empty();
    return;
}

void LogMsg2Buf_start(const ELogLevel eLogLevel, const char *pchFormat,
                      const char *pchArg1, const char *pchArg2, int iArg3)
{
    SYSTEMTIME  time;
    CString     str;
    
    // 检查打印开关
    if (FALSE == s_bEnableLog)
    {
        return;
    }
    
    // 检查打印级别
    if (eLogLevel < s_eLogLevel)
    {
        return;
    }
    
    // 打印模块
    str.Format("%-8s ", s_strModuleName); s_strLogBuf += str;
    
    // 打印级别
    str.Format("%-4s ", s_astrLevel[eLogLevel]); s_strLogBuf += str;
    
    // 错误代码
    str.Format("[%4d] ", s_iLastErrorCode); s_strLogBuf += str;
    
    // 打印时间
    GetLocalTime(&time);
    str.Format("[%4d-%02d-%02d %02d:%02d:%02d.%03d] ",
        time.wYear, time.wMonth, time.wDay,
        time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);
    s_strLogBuf += str;
    
    // 打印内容
    str.Format(pchFormat, pchArg1, pchArg2, iArg3); s_strLogBuf += str;
    
    // 打印文件名/行号
    str.Format(" <%s, %d>\n", s_strFileName.Right(s_strFileName.GetLength() - s_strFileName.ReverseFind('\\') - 1), s_iLineNum);
    s_strLogBuf += str;
    
    return;
}

void LogMsg2Buf_clear(void)
{
    // 离开临界区保护
    LeaveCriticalSection(&s_csLog);
    return;
}

void LogBufFlush(void)
{
    FILE    *fpLog = NULL;
    
    // 打印之前，如果log文件已经较大，则先存档此文件，并新建一个log文件
    LogArchive();

    fpLog = fopen("log\\ReRe.log", "a+");
    if (NULL == fpLog)
    {
        return;
    }

    fprintf(fpLog, "%s", s_strLogBuf);
    
    fclose(fpLog);

}

BOOL GetEnableLog(void)
{
    return s_bEnableLog;
}

ELogLevel GetLogLevel(void)
{
    return s_eLogLevel;
}

ELogFileSize GetLogFileSize(void)
{
    return s_eLogFileSize;
}

void SetEnableLog(BOOL bEnableLog)
{
    s_bEnableLog = bEnableLog;
}

void SetLogLevel(ELogLevel eLogLevel)
{
    s_eLogLevel = eLogLevel;
}

void SetLogFileSize(ELogFileSize eLogFileSize)

{
    s_eLogFileSize = eLogFileSize;
}

static void LogArchive(void)
{
    SYSTEMTIME  time;
    HANDLE      hFile = INVALID_HANDLE_VALUE;
    char        achArchiveFileName[LOG_ARCHIVE_NAME_LENGTH];
    int         iFileSize = 0;

    hFile = CreateFile("log\\ReRe.log", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, 0);
    if (INVALID_HANDLE_VALUE == hFile)
    {// 如果log文件不存在，则不需要存档log文件
        return;
    }

    iFileSize = GetFileSize(hFile, NULL);
    CloseHandle(hFile);

    if (iFileSize + s_strLogBuf.GetLength() < GetSizeInBytes(s_eLogFileSize))
    {// 如果log文件加上将要记录的内容低于设置的存档大小，则不用存档log文件
        return;
    }

    // 开始存档log文件
    GetLocalTime(&time);
    sprintf(achArchiveFileName, "log\\ReRe_%04d%02d%02d_%02d%02d%02d.log",
        time.wYear, time.wMonth, time.wDay,
        time.wHour, time.wMinute, time.wSecond);
    MoveFileEx("log\\ReRe.log", achArchiveFileName,
               MOVEFILE_REPLACE_EXISTING|MOVEFILE_WRITE_THROUGH);
}

static int GetSizeInBytes(ELogFileSize eLogFileSize)
{
    switch(eLogFileSize)
    {
    case LOG_FILE_SIZE_64K:
        return (64 * 1024);
    case LOG_FILE_SIZE_128K:
        return (128 * 1024);
    case LOG_FILE_SIZE_256K:
        return (256 * 1024);
    case LOG_FILE_SIZE_512K:
        return (512 * 1024);
    case LOG_FILE_SIZE_1024K:
        return (1024 * 1024);
    case LOG_FILE_SIZE_2048K:
        return (2048 * 1024);
    case LOG_FILE_SIZE_4096K:
        return (4096 * 1024);
    default:
        return 0x7fffffff;
    }
}