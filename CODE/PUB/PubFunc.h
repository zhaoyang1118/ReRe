#ifndef _PUB_FUNC_H
#define _PUB_FUNC_H


// 文件是否存在
BOOL FileExists(const char *pchFile);


// 设置窗口透明度
typedef BOOL (__stdcall *PFNTransparentWindow)(HWND, COLORREF, BYTE, DWORD); 
PFNTransparentWindow    GetSysLibraryTransparentWindow();

#endif