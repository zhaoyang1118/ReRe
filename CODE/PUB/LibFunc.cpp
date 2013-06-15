#include "StdAfx.h"
#include "Global.h"
#include "KeyboardMouseHook/KeyboardMouseHook.h"
#include "LibFunc.h"


// 只运行一个程序实例的窗口遍历函数
BOOL CALLBACK EnumWndProc(HWND hwnd,LPARAM lParam)
{
    HANDLE h = GetProp(hwnd, g_szPropName);
    if( h == g_hValue)
    {
        *(HWND*)lParam = hwnd;
        return false;
    }
    return true;
}

// 将秒数转化为时间的显示格式(12:34)，超过1小时，只显示小时和分钟
BOOL Seconds2Time(UINT nSeconds, char *pchTime, TimeFormat eFormat)
{
    if (NULL == pchTime)
    {
        return FALSE;
    }

    if (nSeconds >= 3600)
    {
        sprintf(pchTime, "%1d%1d" "%s" "%1d%1d", 
            nSeconds / 3600 / 10,
            nSeconds / 3600 % 10,
            (eFormat == FIXED_COLON || nSeconds % 2 == 0) ? ":" : " ",
            nSeconds % 3600 / 60 / 10,
            nSeconds % 3600 / 60 % 10);
    }
    else
    {
        sprintf(pchTime, "%1d%1d" "%s" "%1d%1d", 
            nSeconds / 60 / 10,
            nSeconds / 60 % 10,
            (eFormat == FIXED_COLON || nSeconds % 2 == 0) ? ":" : " ",
            nSeconds % 60 / 10,
            nSeconds % 60 % 10);
    }
    return TRUE;
}

// 判断一个字符串是否全是数字
BOOL IsNumber(CString str)
{
    if (str.SpanIncluding("0123456789") == str)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

// 计算两点之间的距离(街区距离)
UINT MakeDistance(POINTS a, POINTS b)
{
    return abs(a.x - b.x) + abs(a.y - b.y);
}

void LockKeyboard(BOOL bValue)
{
    if (bValue == TRUE)
    {
        DllExport_InstallKeyboardHook();
    }
    else
    {
        DllExport_UninstallKeyboardHook();
    }
}

void LockMouse(BOOL bValue)
{
    if (bValue == TRUE)
    {
        DllExport_InstallMouseHook();
    }
    else
    {
        DllExport_UninstallMouseHook();
    }
}

void LockKeyBoardAndMouse(BOOL bValue)
{
    LockKeyboard(bValue);
    LockMouse(bValue);
}

// 查询程序开机启动
BOOL GetAppAutoStartWithSystem(void)
{
    LPCTSTR lpRun = "Software\\Microsoft\\Windows\\CurrentVersion\\Run";
    HKEY hKey = 0;
    long lRet = 0;
    
    // 打开启动项Key
    lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, lpRun, 0, KEY_QUERY_VALUE, &hKey);
    if(lRet != ERROR_SUCCESS)
    {
        return FALSE;
    }
    
    lRet = RegQueryValueEx(hKey, "ReRe", 0, NULL, NULL, NULL); 
    if(lRet != ERROR_SUCCESS)
    {
        RegCloseKey(hKey);
        return FALSE;
    }
    
    // 关闭注册表
    RegCloseKey(hKey);
    return TRUE;
}

// 设置程序开机启动
BOOL SetAppAutoStartWithSystem(BOOL bAutoStart, const char *pchAppPath)
{
    LPCTSTR lpRun = "Software\\Microsoft\\Windows\\CurrentVersion\\Run";
    HKEY hKey = 0;
    long lRet = 0;

    // 打开启动项Key
    lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, lpRun, 0, KEY_WRITE, &hKey);
    if(lRet != ERROR_SUCCESS)
    {
        return FALSE;
    }

    if (TRUE == bAutoStart)
    {// 添加一个Value
        if (NULL == pchAppPath)
        {
            RegCloseKey(hKey);
            return FALSE;
        }
        lRet = RegSetValueEx(hKey, "ReRe", 0, REG_SZ, (BYTE*)pchAppPath,
            strlen(pchAppPath)); 
    } 
    else
    {// 删除一个Value
        if (FALSE == GetAppAutoStartWithSystem())
        {
            return TRUE;
        }
        lRet = RegDeleteValue(hKey, "ReRe"); 
    }
    if(lRet != ERROR_SUCCESS)
    {
        RegCloseKey(hKey);
        return FALSE;
    }

    // 关闭注册表
    RegCloseKey(hKey);
    return TRUE;
}

// 全屏模式检测
BOOL FullscreenModeDectect(void)
{
    POINT   ptTopLeft, ptTopRight, ptBottomLeft, ptBottomRight;
    HWND    hwndTopLeft, hwndTopRight, hwndBottomLeft, hwndBottomRight;
    
    
    ptTopLeft.x = 0;
    ptTopLeft.y = 0;
    ptTopRight.x = GetSystemMetrics(SM_CXSCREEN) - 1;
    ptTopRight.y = 0;
    ptBottomLeft.x = 0;
    ptBottomLeft.y = GetSystemMetrics(SM_CYSCREEN) - 1;
    ptBottomRight.x = GetSystemMetrics(SM_CXSCREEN) - 1;
    ptBottomRight.y = GetSystemMetrics(SM_CYSCREEN) - 1;
    
    hwndTopLeft = (CWnd::FromHandle(::WindowFromPoint(ptTopLeft)))->GetTopLevelParent()->GetSafeHwnd();
    
    hwndBottomRight = (CWnd::FromHandle(::WindowFromPoint(ptBottomRight)))->GetTopLevelParent()->GetSafeHwnd();
    if (hwndTopLeft != hwndBottomRight)
    {
        return FALSE;
    }

    hwndTopRight = (CWnd::FromHandle(::WindowFromPoint(ptTopRight)))->GetTopLevelParent()->GetSafeHwnd();
    if (hwndTopLeft != hwndTopRight)
    {
        return FALSE;
    }
    
    hwndBottomLeft = (CWnd::FromHandle(::WindowFromPoint(ptBottomLeft)))->GetTopLevelParent()->GetSafeHwnd();
    if (hwndTopLeft != hwndBottomLeft)
    {
        return FALSE;
    }

    return TRUE;
}