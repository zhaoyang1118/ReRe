// DialogAbout.cpp : implementation file
//

#include "stdafx.h"
#include "RelaxReminder.h"
#include "PubFunc.h"
#include "CreditsCtrl.h"
#include "StringTable.h"
#include "RelaxTimer.h"
#include "DialogTrayWindow.h"
#include "DialogDarkerScreen.h"
#include "RelaxReminderDlg.h"
#include "DialogAboutAbout.h"
#include "DialogAboutThanks.h"
#include "DialogAboutChangelog.h"
#include "DialogAboutStatistics.h"
#include "DialogAboutDonate.h"
#include "DialogAbout.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CDialogAbout dialog


CDialogAbout::CDialogAbout(CWnd* pParent /*=NULL*/)
    : CDialog(CDialogAbout::IDD, pParent)
{
    //{{AFX_DATA_INIT(CDialogAbout)
	m_iPage = -1;
	//}}AFX_DATA_INIT
}


void CDialogAbout::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDialogAbout)
	DDX_Radio(pDX, IDC_RADIO_ABOUT_ABOUT, m_iPage);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogAbout, CDialog)
    //{{AFX_MSG_MAP(CDialogAbout)
	ON_BN_CLICKED(IDC_RADIO_ABOUT_ABOUT, OnRadioAboutAbout)
	ON_BN_CLICKED(IDC_RADIO_ABOUT_THANKS, OnRadioAboutThanks)
	ON_BN_CLICKED(IDC_RADIO_ABOUT_CHANGELOG, OnRadioAboutChangelog)
	ON_BN_CLICKED(IDC_RADIO_ABOUT_STATISTICS, OnRadioAboutStatistics)
	ON_BN_CLICKED(IDC_RADIO_ABOUT_DONATE, OnRadioAboutDonate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogAbout message handlers

BOOL CDialogAbout::OnInitDialog() 
{
    CDialog::OnInitDialog();
    
    // TODO: Add extra initialization here
    CenterWindow(GetDesktopWindow());

    // 设置窗口指针
    ASSERT(m_pdlgMain != NULL);
    m_dlgAbout.m_pdlgMain           = m_pdlgMain;
    m_dlgThanks.m_pdlgMain          = m_pdlgMain;
    m_dlgChangelog.m_pdlgMain       = m_pdlgMain;
    m_dlgStatistics.m_pdlgMain      = m_pdlgMain;
    m_dlgDonate.m_pdlgMain          = m_pdlgMain;

    // 创建子对话框
    m_dlgAbout.Create(IDD_DIALOG_ABOUT_ABOUT, this);
    m_dlgThanks.Create(IDD_DIALOG_ABOUT_THANKS, this);
    m_dlgChangelog.Create(IDD_DIALOG_ABOUT_CHANGELOG, this);
    m_dlgStatistics.Create(IDD_DIALOG_ABOUT_STATISTICS, this);
    m_dlgDonate.Create(IDD_DIALOG_ABOUT_DONATE, this);

    // 调整子对话框在父窗口中的位置
    CRect rs;
    GetDlgItem(IDC_STATIC_PLAT)->GetClientRect(rs);
    GetDlgItem(IDC_STATIC_PLAT)->ClientToScreen(rs);
    ScreenToClient(rs);
    
    // 设置子对话框尺寸并移动到指定位置
    m_dlgAbout.MoveWindow(rs);
    m_dlgThanks.MoveWindow(rs);
    m_dlgChangelog.MoveWindow(rs);
    m_dlgStatistics.MoveWindow(rs);
    m_dlgDonate.MoveWindow(rs);

    // 设置页面按钮字体
    m_fontPageButtonNormal.CreateFont(13,0,0,0,FW_NORMAL,FALSE,FALSE,FALSE,  
        ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,  
        DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"Tahoma");
    m_fontPageButtonPressed.CreateFont(16,0,0,0,FW_BOLD,FALSE,FALSE,FALSE,  
        ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,  
        DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"Tahoma");

    // 分别设置隐藏和显示
    m_iPage = PAGE_ABOUT_ABOUT;
    UpdateData(FALSE);
    PageSelect((EAboutPageIndex)m_iPage);

    LoadLanguageStrings();

    return FALSE;  // return TRUE unless you set the focus to a control
                   // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialogAbout::PageSelect(EAboutPageIndex eIndex)
{
    CWnd *pwndBtnAbout = GetDlgItem(IDC_RADIO_ABOUT_ABOUT);
    CWnd *pwndBtnThanks = GetDlgItem(IDC_RADIO_ABOUT_THANKS);
    CWnd *pwndBtnChangelog = GetDlgItem(IDC_RADIO_ABOUT_CHANGELOG);
    CWnd *pwndBtnStatistics = GetDlgItem(IDC_RADIO_ABOUT_STATISTICS);
    CWnd *pwndBtnDonate = GetDlgItem(IDC_RADIO_ABOUT_DONATE);
    
    m_dlgAbout.ShowWindow(PAGE_ABOUT_ABOUT == eIndex);
    m_dlgThanks.ShowWindow(PAGE_ABOUT_THANKS == eIndex);
    m_dlgChangelog.ShowWindow(PAGE_ABOUT_CHANGELOG == eIndex);
    m_dlgStatistics.ShowWindow(PAGE_ABOUT_STATISTICS == eIndex);
    m_dlgDonate.ShowWindow(PAGE_ABOUT_DONATE == eIndex);
    
    pwndBtnAbout->SetFont((PAGE_ABOUT_ABOUT == eIndex) ? &m_fontPageButtonPressed : &m_fontPageButtonNormal);
    pwndBtnThanks->SetFont((PAGE_ABOUT_THANKS == eIndex) ? &m_fontPageButtonPressed : &m_fontPageButtonNormal);
    pwndBtnChangelog->SetFont((PAGE_ABOUT_CHANGELOG == eIndex) ? &m_fontPageButtonPressed : &m_fontPageButtonNormal);
    pwndBtnStatistics->SetFont((PAGE_ABOUT_STATISTICS == eIndex) ? &m_fontPageButtonPressed : &m_fontPageButtonNormal);
    pwndBtnDonate->SetFont((PAGE_ABOUT_DONATE == eIndex) ? &m_fontPageButtonPressed : &m_fontPageButtonNormal);
}

void CDialogAbout::LoadLanguageStrings()
{
    CStringTable *pst = &(m_pdlgMain->m_str);

    SetWindowText(pst->GetStr(ABOUT_CAPTION));
    
    SetDlgItemText(IDC_RADIO_ABOUT_ABOUT, pst->GetStr(ABOUT_PAGE_ABOUT));
    SetDlgItemText(IDC_RADIO_ABOUT_THANKS, pst->GetStr(ABOUT_PAGE_THANKS));
    SetDlgItemText(IDC_RADIO_ABOUT_CHANGELOG, pst->GetStr(ABOUT_PAGE_CHANGELOG));
    SetDlgItemText(IDC_RADIO_ABOUT_STATISTICS, pst->GetStr(ABOUT_PAGE_STATISTICS));
    SetDlgItemText(IDC_RADIO_ABOUT_DONATE, pst->GetStr(ABOUT_PAGE_DONATE));

    Invalidate(TRUE);
}

void CDialogAbout::OnRadioAboutAbout() 
{
	// TODO: Add your control notification handler code here
	PageSelect(PAGE_ABOUT_ABOUT);
}

void CDialogAbout::OnRadioAboutThanks() 
{
	// TODO: Add your control notification handler code here
	PageSelect(PAGE_ABOUT_THANKS);
}

void CDialogAbout::OnRadioAboutChangelog() 
{
	// TODO: Add your control notification handler code here
	PageSelect(PAGE_ABOUT_CHANGELOG);
}

void CDialogAbout::OnRadioAboutStatistics() 
{
	// TODO: Add your control notification handler code here
	PageSelect(PAGE_ABOUT_STATISTICS);
}

void CDialogAbout::OnRadioAboutDonate() 
{
	// TODO: Add your control notification handler code here
    PageSelect(PAGE_ABOUT_DONATE);
}
