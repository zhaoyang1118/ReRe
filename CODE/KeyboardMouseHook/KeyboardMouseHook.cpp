// KeyboardMouseHook.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "KeyboardMouseHook.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
//	Note!
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

/////////////////////////////////////////////////////////////////////////////
// CKeyboardMouseHookApp

BEGIN_MESSAGE_MAP(CKeyboardMouseHookApp, CWinApp)
	//{{AFX_MSG_MAP(CKeyboardMouseHookApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKeyboardMouseHookApp construction

CKeyboardMouseHookApp::CKeyboardMouseHookApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CKeyboardMouseHookApp object

CKeyboardMouseHookApp theApp;

//////////////////////////////////////////////////////////////////////////
// 定义和声明
//////////////////////////////////////////////////////////////////////////

// 全局钩子定义
HHOOK g_hKeyboardHook = NULL;
HHOOK g_hMouseHook = NULL;

// 底层钩子函数
LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK LowLevelMouseProc(int nCode, WPARAM wParam, LPARAM lParam);

//////////////////////////////////////////////////////////////////////////
// 底层钩子函数实现
//////////////////////////////////////////////////////////////////////////

// 底层键盘钩子函数
LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode >= HC_ACTION)
	{// nCode大于等于0时，才能调用自己的回调函数处理 (MSDN的要求)
		return TRUE;	// 结束按键消息传递
	}
	else
	{// nCode小于0时，必须调用CallNextHookEx (MSDN的要求)
		return CallNextHookEx(g_hKeyboardHook, nCode, wParam, lParam);
	}
}

// 底层鼠标钩子函数
LRESULT CALLBACK LowLevelMouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode >= HC_ACTION)
	{// nCode大于等于0时，才能调用自己的回调函数处理 (MSDN的要求)
		return TRUE;	// 结束按键消息传递
	}
	else
	{// nCode小于0时，必须调用CallNextHookEx (MSDN的要求)
		return CallNextHookEx(g_hMouseHook, nCode, wParam, lParam);
	}
}

//////////////////////////////////////////////////////////////////////////
// dll导出函数 (外部接口)
//////////////////////////////////////////////////////////////////////////

DllExport BOOL WINAPI DllExport_InstallKeyboardHook()
{
	// 如果已经安装了键盘钩子，则返回TRUE
	if (g_hKeyboardHook != NULL)
	{
		return TRUE;
	}

	// 开始安装键盘钩子
	g_hKeyboardHook = (HHOOK)SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, theApp.m_hInstance, 0);
	if (g_hKeyboardHook == NULL)
	{// 安装键盘钩子失败，则返回FALSE
		return FALSE;
	}	
	return TRUE;
}

DllExport BOOL WINAPI DllExport_UninstallKeyboardHook()
{
	if (UnhookWindowsHookEx(g_hKeyboardHook) == FALSE)
	{
		return FALSE;
	}	
	g_hKeyboardHook = NULL;
	return TRUE;
}

DllExport BOOL WINAPI DllExport_InstallMouseHook()
{
	// 如果已经安装了鼠标钩子，则返回TRUE
	if (g_hMouseHook != NULL)
	{
		return TRUE;
	}

	// 开始安装鼠标钩子
	g_hMouseHook = (HHOOK)SetWindowsHookEx(WH_MOUSE_LL, LowLevelMouseProc, theApp.m_hInstance, 0);
	if (g_hMouseHook == NULL)
	{// 安装鼠标钩子失败，则返回FALSE
		return FALSE;
	}	
	return TRUE;
}

DllExport BOOL WINAPI DllExport_UninstallMouseHook()
{
	if (UnhookWindowsHookEx(g_hMouseHook) == FALSE)
	{
		return FALSE;
	}	
	g_hMouseHook = NULL;
	return TRUE;
}
