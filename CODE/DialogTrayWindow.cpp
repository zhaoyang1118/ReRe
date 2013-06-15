// DialogTrayWindow.cpp : implementation file
//

#include "stdafx.h"
#include "RelaxReminder.h"
#include "PubFunc.h"
#include "Log.h"
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

// 鼠标位置检测定时器
#define TIMER_CURSOR_DETECT                 1
#define CURSOR_DETECT_INTERVAL              50
#define TRAY_WINDOW_ANIMATE_MILLISECONDS    300

// 任务栏窗口透明度
#define TRAY_WINDOW_TRANSPARENCY            236
#define MOUSE_HOVER_TRANSPARENCY            30

// 鼠标在接近区停留的时间(在此时间内tray window不改变透明度)
#define APPROACH_AREA_STAY_MILLISECOND      300


/////////////////////////////////////////////////////////////////////////////
// CDialogTrayWindow dialog


CDialogTrayWindow::CDialogTrayWindow(CWnd* pParent /*=NULL*/)
    : CDialog(CDialogTrayWindow::IDD, pParent)
{
    //{{AFX_DATA_INIT(CDialogTrayWindow)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
}


void CDialogTrayWindow::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDialogTrayWindow)
        // NOTE: the ClassWizard will add DDX and DDV calls here
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogTrayWindow, CDialog)
    //{{AFX_MSG_MAP(CDialogTrayWindow)
    ON_WM_TIMER()
    ON_BN_CLICKED(IDC_BUTTON_DELAY, OnButtonDelay)
	ON_BN_CLICKED(IDC_BUTTON_SKIP, OnButtonSkip)
	ON_BN_CLICKED(IDC_BUTTON_HIDE, OnButtonHide)
	ON_WM_RBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogTrayWindow message handlers

BOOL CDialogTrayWindow::OnInitDialog() 
{
    CDialog::OnInitDialog();
    
    // TODO: Add extra initialization here
    // 设置窗口显示时间的字体
    m_fontTimeTips.CreateFont(30,14,0,0,FW_BOLD,FALSE,FALSE,FALSE,
        ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,  
        DEFAULT_QUALITY,FIXED_PITCH | FF_SWISS,"Courier New");
    GetDlgItem(IDC_STATIC_TIMETIPS)->SetFont(&m_fontTimeTips);
    
    // 成员变量初始化
    m_pfnTransparentWindow  = GetSysLibraryTransparentWindow();
    m_nApproachAreaStay     = 0;
    m_iAlpha                = TRAY_WINDOW_TRANSPARENCY;
    m_iAlphaStep            = (TRAY_WINDOW_TRANSPARENCY - MOUSE_HOVER_TRANSPARENCY)
                              * CURSOR_DETECT_INTERVAL / TRAY_WINDOW_ANIMATE_MILLISECONDS;

	// CG: The following block was added by the ToolTips component.
	{
		// Create the ToolTip control.
		m_tooltip.Create(this);
		m_tooltip.Activate(TRUE);

		// TODO: Use one of the following forms to add controls:
        CStringTable *pst = &(m_pwndParent->m_str);
        m_tooltip.AddTool(GetDlgItem(IDC_BUTTON_DELAY),
                          pst->GetStr(TRAY_WINDOW_DELAY_TIPS));
        m_tooltip.AddTool(GetDlgItem(IDC_BUTTON_SKIP),
                          pst->GetStr(TRAY_WINDOW_SKIP_TIPS));
        m_tooltip.AddTool(GetDlgItem(IDC_BUTTON_HIDE),
                          pst->GetStr(TRAY_WINDOW_HIDE_TIPS));
	}

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

// 任务栏窗口移动到右下角
void CDialogTrayWindow::MoveWindowToOtherSide(void)
{
    if (m_rectTrayWindow.left == m_rectMonitor.left)
    {
        MoveToBottomRight();
    }
    else
    {
        MoveToBottomLeft();
    }
}

// 任务栏窗口移动到右下角
void CDialogTrayWindow::MoveToBottomRight(void)
{
    CRect rect;
    GetWindowRect(&rect);

    m_rectTrayWindow.SetRect(m_rectMonitor.right - rect.Width(),
                             m_rectMonitor.bottom - rect.Height(),
                             m_rectMonitor.right,
                             m_rectMonitor.bottom);
    MoveWindow(m_rectTrayWindow);

    m_rectApproach = m_rectTrayWindow;
    m_rectApproach.InflateRect(150, 90, 150, 0);
}

// 任务栏窗口移动到左下角
void CDialogTrayWindow::MoveToBottomLeft(void)
{
    CRect rect;
    GetWindowRect(&rect);
    
    m_rectTrayWindow.SetRect(m_rectMonitor.left,
                             m_rectMonitor.bottom - rect.Height(),
                             m_rectMonitor.left + rect.Width(),
                             m_rectMonitor.bottom);
    MoveWindow(m_rectTrayWindow);
    
    m_rectApproach = m_rectTrayWindow;
    m_rectApproach.InflateRect(150, 90, 150, 0);
}

// 初始化任务栏窗口
void CDialogTrayWindow::InitTrayWindow(CWnd *pwndParent)
{
    // 保存传入的参数
    m_pwndParent = (CRelaxReminderDlg*)pwndParent;
    
    Create(IDD_DIALOG_TRAY_WINDOW, NULL);
    
    // 设置窗口透明
    SetWindowTransparent(TRAY_WINDOW_TRANSPARENCY);
    
    // 设置窗口置顶
    SetWindowPos(&wndTopMost,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE|SWP_NOACTIVATE);
}

// 显示任务栏窗口
void CDialogTrayWindow::ShowTrayWindow(char *szCaption, char *szTimetips)
{
    // 设置窗口显示内容
    GetDlgItem(IDC_STATIC_CAPTION)->SetWindowText(szCaption);
    GetDlgItem(IDC_STATIC_TIMETIPS)->SetWindowText(szTimetips);

    // 设置窗口位置
    MoveToBottomRight();

    LoadLanguageStrings();

    ShowWindow(SW_SHOWNA);

    // 设置DarkerScreen位于TrayWindow之下
    m_pwndParent->PutDarkerScreenUnderTrayWindow();

    // 开始鼠标位置检测
    SetTimer(TIMER_CURSOR_DETECT, CURSOR_DETECT_INTERVAL, NULL);
}

// 更新任务栏窗口
void CDialogTrayWindow::UpdateTrayWindow(char *szCaption, char *szTimetips)
{
    if (szCaption)
    {
        GetDlgItem(IDC_STATIC_CAPTION)->SetWindowText(szCaption);
    }
    if (szTimetips)
    {
        GetDlgItem(IDC_STATIC_TIMETIPS)->SetWindowText(szTimetips);
    }
}

// 分辨率改变的处理函数
void CDialogTrayWindow::DisplayChange()
{
    // 移动窗口到新位置
    MoveToBottomRight();
}

// 删除任务栏窗口
void CDialogTrayWindow::DeleteTrayWindow()
{
    KillTimer(TIMER_CURSOR_DETECT);
    ShowWindow(SW_HIDE);
}

// 设置提示窗口透明度
void CDialogTrayWindow::SetWindowTransparent(BYTE byAlpha)
{
    SetWindowLong(this->GetSafeHwnd(), GWL_EXSTYLE,
        GetWindowLong(this->GetSafeHwnd(), GWL_EXSTYLE)|0x80000);
    m_pfnTransparentWindow(this->GetSafeHwnd(), 0, byAlpha, 2);
    m_iAlpha = byAlpha;
}

void CDialogTrayWindow::OnTimer(UINT nIDEvent) 
{
    // TODO: Add your message handler code here and/or call default
    switch (nIDEvent)
    {
    case TIMER_CURSOR_DETECT:
        CursorDetect();
        break;
    }

    CDialog::OnTimer(nIDEvent);
}

void CDialogTrayWindow::OnButtonDelay() 
{
    // TODO: Add your control notification handler code here
    AppLog(L_MSG, " --> relax delay.");

    m_pwndParent->m_tm.RelaxDelay();
    
    // 如果darker screen正在显示，则关闭它
    m_pwndParent->HideDarkerScreen();

    DeleteTrayWindow();
}

void CDialogTrayWindow::OnButtonSkip() 
{
    // TODO: Add your control notification handler code here
    AppLog(L_MSG, " --> relax skip.");

    m_pwndParent->m_tm.RelaxSkip();
    
    // 如果darker screen正在显示，则关闭它
    m_pwndParent->HideDarkerScreen();
    
    DeleteTrayWindow();
}

void CDialogTrayWindow::OnButtonHide() 
{
    // TODO: Add your control notification handler code here
    DeleteTrayWindow();
}

void CDialogTrayWindow::OnRButtonUp(UINT nFlags, CPoint point) 
{
    // TODO: Add your message handler code here and/or call default
    m_pwndParent->ShowRightClickMenu();

    CDialog::OnRButtonUp(nFlags, point);
}

BOOL CDialogTrayWindow::PreTranslateMessage(MSG* pMsg)
{
	// CG: The following block was added by the ToolTips component.
	{
		// Let the ToolTip process this message.
		m_tooltip.RelayEvent(pMsg);
	}
	return CDialog::PreTranslateMessage(pMsg);	// CG: This was added by the ToolTips component.
}

// 鼠标位置检测
void CDialogTrayWindow::CursorDetect()
{
    CPoint point;

    GetCursorPos(&point);

    if (m_rectApproach.PtInRect(point) && !m_rectTrayWindow.PtInRect(point))
    {// 鼠标指针在接近框内，但在TrayWindow之外
        if (++m_nApproachAreaStay >= APPROACH_AREA_STAY_MILLISECOND / CURSOR_DETECT_INTERVAL)
        {
            if (m_iAlpha > MOUSE_HOVER_TRANSPARENCY)
            {
                SetWindowTransparent(max(m_iAlpha - m_iAlphaStep, MOUSE_HOVER_TRANSPARENCY));
            }
            else
            {
                MoveWindowToOtherSide();
            }
        }
    }
    else
    {// 鼠标指针离开接近框，或进入TrayWindow范围
        m_nApproachAreaStay = 0;
        if (m_iAlpha < TRAY_WINDOW_TRANSPARENCY)
        {
            SetWindowTransparent(min(m_iAlpha + m_iAlphaStep, TRAY_WINDOW_TRANSPARENCY));
        }
    }
}

void CDialogTrayWindow::LoadLanguageStrings()
{
    CStringTable *pst;
    
    pst = &(m_pwndParent->m_str);
    SetDlgItemText(IDC_BUTTON_DELAY, pst->GetStr(TRAY_WINDOW_DELAY));
    SetDlgItemText(IDC_BUTTON_SKIP, pst->GetStr(TRAY_WINDOW_SKIP));
    SetDlgItemText(IDC_BUTTON_HIDE, pst->GetStr(TRAY_WINDOW_HIDE));
    m_tooltip.UpdateTipText(pst->GetStr(TRAY_WINDOW_DELAY_TIPS),
                            GetDlgItem(IDC_BUTTON_DELAY));
    m_tooltip.UpdateTipText(pst->GetStr(TRAY_WINDOW_SKIP_TIPS),
                            GetDlgItem(IDC_BUTTON_SKIP));
    m_tooltip.UpdateTipText(pst->GetStr(TRAY_WINDOW_HIDE_TIPS),
                            GetDlgItem(IDC_BUTTON_HIDE));
    Invalidate(TRUE);
}
