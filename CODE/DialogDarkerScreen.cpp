// DialogDarkerScreen.cpp : implementation file
//

#include "stdafx.h"
#include "RelaxReminder.h"
#include "PubFunc.h"
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

// DarkerScreen窗口动画定时器
#define TIMER_DARKER_SCREEN_ANIMATE     3
#define DARKER_SCREEN_ANIMATE_INTERVAL  10


/////////////////////////////////////////////////////////////////////////////
// CDialogDarkerScreen dialog


CDialogDarkerScreen::CDialogDarkerScreen(CWnd* pParent /*=NULL*/)
    : CDialog(CDialogDarkerScreen::IDD, pParent)
{
    //{{AFX_DATA_INIT(CDialogDarkerScreen)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
}


void CDialogDarkerScreen::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDialogDarkerScreen)
        // NOTE: the ClassWizard will add DDX and DDV calls here
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogDarkerScreen, CDialog)
    //{{AFX_MSG_MAP(CDialogDarkerScreen)
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogDarkerScreen message handlers

BOOL CDialogDarkerScreen::OnInitDialog() 
{
    CDialog::OnInitDialog();
    
    // TODO: Add extra initialization here
    // 初始化函数指针
    m_pfnTransparentWindow = GetSysLibraryTransparentWindow();

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

// 初始化暗屏窗口
void CDialogDarkerScreen::InitDarkerScreen(void)
{
    Create(IDD_DIALOG_DARKER_SCREEN, NULL);
    
    // 设置窗口点击穿透属性
    SetWindowLong(this->GetSafeHwnd(), GWL_EXSTYLE,
        GetWindowLong(this->GetSafeHwnd(), GWL_EXSTYLE)|WS_EX_TRANSPARENT);
    
    // 设置窗口置顶
    SetWindowPos(&wndTopMost,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE|SWP_NOACTIVATE);
}

// 显示暗屏窗口
void CDialogDarkerScreen::ShowDarkerScreen(int iAlpha,
                                           COLORREF color,
                                           EAnimateType eAnimateType)
{
    // 设置窗口位置
    MoveWindow(&m_rectScreen);
    GetDlgItem(IDC_STATIC_MASK)->MoveWindow(0, 0, m_rectScreen.Width(), m_rectScreen.Height());
    
    // 设置窗口透明
    m_eAnimateType = eAnimateType;
    m_color = color;
    m_iAlpha = iAlpha;
    m_iAlphaStepCount = 0;
    m_flAlphaStep = (float)iAlpha * DARKER_SCREEN_ANIMATE_INTERVAL
                    / m_eAnimateType / 1000;
    if (iAlpha)
    {
        if (ANIMATE_OFF == eAnimateType)
        {
            SetWindowTransparent((BYTE)iAlpha);
        }
        else
        {
            SetWindowTransparent(1);
            SetTimer(TIMER_DARKER_SCREEN_ANIMATE,
                     DARKER_SCREEN_ANIMATE_INTERVAL,
                     NULL);
        }
    }

    ShowWindow(SW_SHOWNA);
}

// 分辨率改变的处理函数
void CDialogDarkerScreen::DisplayChange()
{
    // 移动窗口到新位置
    MoveWindow(&m_rectScreen);
    GetDlgItem(IDC_STATIC_MASK)->MoveWindow(0,
                                            0,
                                            m_rectScreen.Width(),
                                            m_rectScreen.Height());
}

// 删除暗屏窗口
void CDialogDarkerScreen::DeleteDarkerScreen()
{
    ShowWindow(SW_HIDE);
}

// 设置提示窗口透明度
void CDialogDarkerScreen::SetWindowTransparent(BYTE byAlpha)
{
    if (m_iAlphaCurrent == byAlpha)
    {
        return;
    }

    SetWindowLong(this->GetSafeHwnd(), GWL_EXSTYLE,
        GetWindowLong(this->GetSafeHwnd(), GWL_EXSTYLE)|0x80000);
    m_pfnTransparentWindow(this->GetSafeHwnd(), 0, byAlpha, 2);
    m_iAlphaCurrent = byAlpha;
}

void CDialogDarkerScreen::OnTimer(UINT nIDEvent) 
{

	// TODO: Add your message handler code here and/or call default
    if(nIDEvent == TIMER_DARKER_SCREEN_ANIMATE)        
    {
        BYTE byNextAlpha = (BYTE)(m_flAlphaStep * (++m_iAlphaStepCount));
        SetWindowTransparent(byNextAlpha);
        if (byNextAlpha >= m_iAlpha)
        {
            KillTimer(TIMER_DARKER_SCREEN_ANIMATE);
        }
    }

	CDialog::OnTimer(nIDEvent);
}

HBRUSH CDialogDarkerScreen::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
    if (CTLCOLOR_STATIC == nCtlColor)
    {
        return CreateSolidBrush(m_color);
    }
	// TODO: Return a different brush if the default is not desired
	return hbr;
}
