#include "StdAfx.h"
#include "Version.h"


// 获取文件版本号
CString GetFileVersion(const char *pchFile)
{
    CString strFileVersion;
    char achFilePath[_MAX_PATH];
    
    strncpy(achFilePath, pchFile, _MAX_PATH);
    
    int iVerInfoSize = GetFileVersionInfoSize(achFilePath,NULL);
    if(iVerInfoSize != 0)
    {
        char *pBuf = new char[iVerInfoSize];
        if(GetFileVersionInfo(achFilePath, 0, iVerInfoSize, pBuf))
        {
            VS_FIXEDFILEINFO *pVsInfo;
            unsigned int iFileInfoSize = sizeof(VS_FIXEDFILEINFO);
            if(VerQueryValue(pBuf, "\\",(void **)&pVsInfo,&iFileInfoSize))
            {
                strFileVersion.Format("%d.%d.%d",
                    HIWORD(pVsInfo->dwFileVersionMS),
                    LOWORD(pVsInfo->dwFileVersionMS),
                    HIWORD(pVsInfo->dwFileVersionLS));
            }
        }
        delete pBuf;
    }
    return strFileVersion;
}

// 版本字符串转换为UINT型版本号
UINT VersionString2Num(const char *pchVersion)
{
    // 版本号字符串  XX.YY.ZZ => 0xXXYYZZ00
    // 例：0.7.4 => 0x00070400
    CString strVersion = pchVersion;
    CString strTemp;
    UINT    dwVersionNum = 0;
    int     iPosStart = 0;
    int     iPosEnd = 0;

    // XXYY
    for (int i = 3; i > 1; i--)
    {
        iPosEnd = strVersion.Find('.', iPosStart);
        strTemp = strVersion.Mid(iPosStart, iPosEnd - iPosStart);
        iPosStart = iPosEnd + 1;
        dwVersionNum += atoi(strTemp) << (8*i);
    }
    // ZZ00
    strTemp = strVersion.Mid(iPosStart);
    dwVersionNum += atoi(strTemp) << 8;

    return dwVersionNum;
}

// UINT型版本号转换为版本字符串
CString VersionNum2String(UINT dwVersion)
{
    CString strVersion;
    strVersion.Format("%d.%d.%d",
        (dwVersion >> 24) & 0xFF,
        (dwVersion >> 16) & 0xFF,
        (dwVersion >> 8) & 0xFF);
    return strVersion;
}

// 获取文件修改时间
CString GetFileData(const char *pchFile)
{   
    WIN32_FIND_DATA ffd ;   
    HANDLE hFind = FindFirstFile(pchFile,&ffd);   
    SYSTEMTIME stUTC, stLocal;   
    FileTimeToSystemTime(&(ffd.ftLastWriteTime), &stUTC);   
    SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);   
    CString strTmp;   
    strTmp.Format(" (%4d-%02d-%02d)", stLocal.wYear,stLocal.wMonth,stLocal.wDay);   
    return strTmp;   
}

// 获取文件Ver信息中的指定项
CString GetFileVerInfoItem(const char *pchFile, const char *pchItem)
{
    CString strValue;
    char achFilePath[_MAX_PATH];
    
    strncpy(achFilePath, pchFile, _MAX_PATH);
    
    int iVerInfoSize = GetFileVersionInfoSize(achFilePath,NULL);
    
    if(iVerInfoSize != 0)
    {
        char *pBlock = new char[iVerInfoSize];
        if(GetFileVersionInfo(achFilePath, 0, iVerInfoSize, pBlock))
        {
            char *pBuffer;
            unsigned int uiBytes;
            CString strSubBlock = "\\StringFileInfo\\040904b0\\";
            strSubBlock += pchItem;
           if(VerQueryValue(pBlock, strSubBlock.GetBuffer(0),
                             (void**)&pBuffer, &uiBytes))
            {
                strValue = pBuffer;
            }
        }
        delete pBlock;
    }
    return strValue;
}
