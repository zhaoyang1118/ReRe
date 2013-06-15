// KeyboardMouseHook.h : main header file for the KEYBOARDMOUSEHOOK DLL
//

#if !defined(AFX_KEYBOARDMOUSEHOOK_H__98A5AD9E_5463_42E5_9BDC_E5EBB5190C48__INCLUDED_)
#define AFX_KEYBOARDMOUSEHOOK_H__98A5AD9E_5463_42E5_9BDC_E5EBB5190C48__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "winuser.h"

// dll导出函数的宏定义
#define DllExport __declspec(dllexport)

// dll导出函数
DllExport BOOL WINAPI DllExport_InstallKeyboardHook();
DllExport BOOL WINAPI DllExport_UninstallKeyboardHook();
DllExport BOOL WINAPI DllExport_InstallMouseHook();
DllExport BOOL WINAPI DllExport_UninstallMouseHook();


/////////////////////////////////////////////////////////////////////////////
// CKeyboardMouseHookApp
// See KeyboardMouseHook.cpp for the implementation of this class
//

class CKeyboardMouseHookApp : public CWinApp
{
public:
	CKeyboardMouseHookApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKeyboardMouseHookApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CKeyboardMouseHookApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KEYBOARDMOUSEHOOK_H__98A5AD9E_5463_42E5_9BDC_E5EBB5190C48__INCLUDED_)
