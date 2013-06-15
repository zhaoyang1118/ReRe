#ifndef _VERSION_H
#define _VERSION_H


// 获取文件版本号
CString GetFileVersion(const char *pchFile);
// 版本字符串转换为UINT型版本号
UINT VersionString2Num(const char *pchVersion);
// UINT型版本号转换为版本字符串
CString VersionNum2String(UINT dwVersion);
// 获取文件修改时间
CString GetFileData(const char *pchFile);
// 获取文件PrivateBuild
CString GetFileVerInfoItem(const char *pchFileName, const char *pchItem);


#endif