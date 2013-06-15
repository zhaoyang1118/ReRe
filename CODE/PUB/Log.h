#ifndef _LOG_H
#define _LOG_H

#define AppLog      LogBase("MainApp", __FILE__, __LINE__); LogMsg
#define AppLog2Buf  LogBase("MainApp", __FILE__, __LINE__); LogMsg2Buf_start

#define LOG_ARCHIVE_NAME_LENGTH     32

typedef enum {
    L_DETAIL = 0,
    L_MSG,
    L_WARN,
    L_ERR,
    L_FAIL,
    MAX_LEVEL_NUM
} ELogLevel;

typedef enum {
    LOG_FILE_SIZE_64K = 0,
    LOG_FILE_SIZE_128K,
    LOG_FILE_SIZE_256K,
    LOG_FILE_SIZE_512K,
    LOG_FILE_SIZE_1024K,
    LOG_FILE_SIZE_2048K,
    LOG_FILE_SIZE_4096K,
} ELogFileSize;

void LogInit(void);
void LogBase(const char *pchModuleName, const char *pchFileName, int iLineNum);
void LogMsg(const ELogLevel eLogLevel, const char *pchFormat, const char *pchArg1 = NULL, const char *pchArg2 = NULL, int iArg3 = 0);
void LogMsg2Buf_prepare(void);
void LogMsg2Buf_start(const ELogLevel eLogLevel, const char *pchFormat, const char *pchArg1 = NULL, const char *pchArg2 = NULL, int iArg3 = 0);
void LogMsg2Buf_clear(void);
void LogBufFlush(void);

BOOL            GetEnableLog(void);
ELogLevel       GetLogLevel(void);
ELogFileSize    GetLogFileSize(void);
void            SetEnableLog(BOOL bEnableLog);
void            SetLogLevel(ELogLevel eLogLevel);
void            SetLogFileSize(ELogFileSize eLogFileSize);

#endif