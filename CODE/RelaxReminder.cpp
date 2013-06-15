// RelaxReminder.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "RelaxReminder.h"
#include "PubFunc.h"
#include "LibFunc.h"
#include "StringTable.h"
#include "RelaxTimer.h"
#include "DialogTrayWindow.h"
#include "DialogDarkerScreen.h"
#include "RelaxReminderDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRelaxReminderApp

BEGIN_MESSAGE_MAP(CRelaxReminderApp, CWinApp)
    //{{AFX_MSG_MAP(CRelaxReminderApp)
        // NOTE - the ClassWizard will add and remove mapping macros here.
        //    DO NOT EDIT what you see in these blocks of generated code!
    //}}AFX_MSG
    ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRelaxReminderApp construction

CRelaxReminderApp::CRelaxReminderApp()
{
    // TODO: add construction code here,
    // Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CRelaxReminderApp object

CRelaxReminderApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CRelaxReminderApp initialization

BOOL CRelaxReminderApp::InitInstance()
{
    // Standard initialization
    // If you are not using these features and wish to reduce the size
    //  of your final executable, you should remove from the following
    //  the specific initialization routines you do not need.

#ifdef _AFXDLL
    Enable3dControls();            // Call this when using MFC in a shared DLL
#else
    Enable3dControlsStatic();    // Call this when linking to MFC statically
#endif

    // 只允许运行一个实例
    HWND oldHWnd = NULL;
    EnumWindows(EnumWndProc, (LPARAM)&oldHWnd);    //枚举所有运行的窗口
    if(oldHWnd != NULL)
    {
        MessageBox(NULL,
            "Another ReRe instance is already running.",
            "ReRe Startup Check",
            MB_OK | MB_ICONEXCLAMATION);
        return FALSE;                                  //退出本次运行
    }

    // 隐藏主窗口
    CRelaxReminderDlg *dlg = new CRelaxReminderDlg;
    m_pMainWnd = dlg;
    return dlg->Create(IDD_RELAXREMINDER_DIALOG);
}
