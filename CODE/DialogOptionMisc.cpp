// DialogOptionMisc.cpp : implementation file
//

#include "stdafx.h"
#include "relaxreminder.h"
#include "DefaultValue.h"
#include "PubFunc.h"
#include "LibFunc.h"
#include "BtnST.h"
#include "Log.h"
#include "StringTable.h"
#include "RelaxTimer.h"
#include "DialogTrayWindow.h"
#include "DialogDarkerScreen.h"
#include "RelaxReminderDlg.h"
#include "DialogOptionTime.h"
#include "DialogOptionNotify.h"
#include "DialogOptionAutoAway.h"
#include "DialogOptionLanguage.h"
#include "DialogOptionMisc.h"
#include "DialogOption.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogOptionMisc dialog


CDialogOptionMisc::CDialogOptionMisc(CWnd* pParent /*=NULL*/)
    : CDialog(CDialogOptionMisc::IDD, pParent)
{
    //{{AFX_DATA_INIT(CDialogOptionMisc)
    m_bCloseMonitor = FALSE;
    m_bLockComputer = FALSE;
	m_bEnableLog = FALSE;
	m_iLogFileSize = -1;
	m_iLogLevel = -1;
	m_bAutoStart = FALSE;
	m_bShowFloatingWindowAtStartup = FALSE;
	m_bShowTrayIconAtStartup = FALSE;
	//}}AFX_DATA_INIT
}


void CDialogOptionMisc::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDialogOptionMisc)
    DDX_Check(pDX, IDC_CHECK_CLOSE_MONITOR, m_bCloseMonitor);
    DDX_Check(pDX, IDC_CHECK_LOCK_COMPTER, m_bLockComputer);
	DDX_Check(pDX, IDC_CHECK_ENABLE_LOG, m_bEnableLog);
	DDX_CBIndex(pDX, IDC_COMBO_LOG_FILE_SIZE, m_iLogFileSize);
	DDX_CBIndex(pDX, IDC_COMBO_LOG_LEVEL, m_iLogLevel);
	DDX_Check(pDX, IDC_CHECK_AUTO_START, m_bAutoStart);
	DDX_Check(pDX, IDC_CHECK_SHOW_FLOATING_WINDOW, m_bShowFloatingWindowAtStartup);
	DDX_Check(pDX, IDC_CHECK_SHOW_TRAY_ICON, m_bShowTrayIconAtStartup);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogOptionMisc, CDialog)
    //{{AFX_MSG_MAP(CDialogOptionMisc)
    ON_BN_CLICKED(IDC_CHECK_LOCK_COMPTER, OnCheckLockCompter)
    ON_BN_CLICKED(IDC_CHECK_CLOSE_MONITOR, OnCheckCloseMonitor)
	ON_BN_CLICKED(IDC_CHECK_SHOW_FLOATING_WINDOW, OnCheckShowFloatingWindow)
	ON_BN_CLICKED(IDC_CHECK_ENABLE_LOG, OnCheckEnableLog)
	ON_CBN_SELCHANGE(IDC_COMBO_LOG_LEVEL, OnSelchangeComboLogLevel)
	ON_CBN_SELCHANGE(IDC_COMBO_LOG_FILE_SIZE, OnSelchangeComboLogFileSize)
	ON_BN_CLICKED(IDC_CHECK_AUTO_START, OnCheckAutoStart)
	ON_BN_CLICKED(IDC_CHECK_SHOW_TRAY_ICON, OnCheckShowTrayIcon)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogOptionMisc message handlers

BOOL CDialogOptionMisc::OnInitDialog() 
{
    CDialog::OnInitDialog();
    
    // TODO: Add extra initialization here
    // 读取当前的设置
    LoadFromCurrentSetting();

    LoadLanguageStrings();

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDialogOptionMisc::LoadFromCurrentSetting()
{
    m_bLockComputer = m_pdlgMain->m_bLockComputer;
    m_bCloseMonitor = m_pdlgMain->m_bCloseMonitor;
    m_bShowFloatingWindowAtStartup  = m_pdlgMain->m_bShowFloatingWindowAtStartup;
    m_bShowTrayIconAtStartup        = m_pdlgMain->m_bShowTrayIconAtStartup;
    m_bEnableLog    = GetEnableLog();
    m_iLogLevel     = GetLogLevel();
    m_iLogFileSize  = GetLogFileSize();
    m_bAutoStart    = GetAppAutoStartWithSystem();

    UpdateData(FALSE);
    UpdateControlStatus();
    return TRUE;
}

void CDialogOptionMisc::LoadSettingFromDefault()
{
    m_bLockComputer = DEFAULT_ENABLE_LOCK_COMPUTER;
    m_bCloseMonitor = DEFAULT_ENABLE_CLOSE_MONITOR;
    m_bShowFloatingWindowAtStartup  = DEFAULT_SHOW_FLOATING_WINDOW;
    m_bShowTrayIconAtStartup        = DEFAULT_SHOW_TRAY_ICON;
    m_bEnableLog    = DEFAULT_ENABLE_LOG;
    m_iLogLevel     = DEFAULT_LOG_LEVEL;
    m_iLogFileSize  = DEFAULT_LOG_FILE_SIZE;
    m_bAutoStart    = DEFAULT_AUTO_START;

    UpdateData(FALSE);
    UpdateControlStatus();
}

void CDialogOptionMisc::UpdateControlStatus()
{
    UpdateData(TRUE);
    
    GetDlgItem(IDC_COMBO_LOG_LEVEL)->EnableWindow(m_bEnableLog);
    GetDlgItem(IDC_COMBO_LOG_FILE_SIZE)->EnableWindow(m_bEnableLog);
    
    UpdateData(FALSE);
}

BOOL CDialogOptionMisc::CheckSetting()
{
    // 取出当前设置窗口中的值
    UpdateData(TRUE);

    return TRUE;
}

BOOL CDialogOptionMisc::ApplySetting()
{
    m_pdlgMain->m_bLockComputer = m_bLockComputer;
    m_pdlgMain->m_bCloseMonitor = m_bCloseMonitor;
    m_pdlgMain->m_bShowFloatingWindowAtStartup  = m_bShowFloatingWindowAtStartup;
    m_pdlgMain->m_bShowTrayIconAtStartup        = m_bShowTrayIconAtStartup;
    SetEnableLog(m_bEnableLog);
    SetLogLevel((ELogLevel)m_iLogLevel);
    SetLogFileSize((ELogFileSize)m_iLogFileSize);
    BOOL bOK = SetAppAutoStartWithSystem(m_bAutoStart,
                                         m_pdlgMain->m_strAppFile);
    if (FALSE == bOK)
    {
        MessageBox(m_pdlgMain->m_str.GetStr(OPTION_MISC_CHECK_FAIL_STARTUP_WITH_WINDOWS),
                   m_pdlgMain->m_str.GetStr(OPTION_CHECK_FAIL_CAPTION),
                   MB_ICONSTOP);
        ((CButton*)(GetDlgItem(IDC_CHECK_AUTO_START)))->SetCheck(GetAppAutoStartWithSystem());
    }

    return TRUE;
}

void CDialogOptionMisc::UpdateButtonStatusBySettingChange()
{
    if (NULL == m_pdlgOption)
    {
        return;
    }
    
    m_pdlgOption->ChangeButtonStatus(OPTION_SETTING_CHANGED);
}

void CDialogOptionMisc::LoadLanguageStrings()
{
    CStringTable *pst;
    
    pst = &(m_pdlgMain->m_str);
    SetDlgItemText(IDC_CHECK_LOCK_COMPTER, pst->GetStr(OPTION_MISC_LOCK_COMPUTER));
    SetDlgItemText(IDC_CHECK_CLOSE_MONITOR, pst->GetStr(OPTION_MISC_CLOSE_MONITOR));
    SetDlgItemText(IDC_CHECK_SHOW_FLOATING_WINDOW, pst->GetStr(OPTION_MISC_SHOW_FLOATING_WINDOW));
    SetDlgItemText(IDC_CHECK_SHOW_TRAY_ICON, pst->GetStr(OPTION_MISC_SHOW_TRAY_ICON));
    SetDlgItemText(IDC_CHECK_ENABLE_LOG, pst->GetStr(OPTION_MISC_LOG));
    SetDlgItemText(IDC_STATIC_LOG_LEVEL, pst->GetStr(OPTION_MISC_LOG_LEVEL));
    SetDlgItemText(IDC_STATIC_LOG_FILE_SIZE, pst->GetStr(OPTION_MISC_LOG_FILE_SIZE));
    SetDlgItemText(IDC_CHECK_AUTO_START, pst->GetStr(OPTION_MISC_STARTUP_WITH_WINDOWS));
    Invalidate(TRUE);
}

void CDialogOptionMisc::OnCheckLockCompter() 
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
    UpdateButtonStatusBySettingChange();
    UpdateData(FALSE);
}

void CDialogOptionMisc::OnCheckCloseMonitor() 
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
    UpdateButtonStatusBySettingChange();
    UpdateData(FALSE);
}

void CDialogOptionMisc::OnCheckShowFloatingWindow() 
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
    UpdateButtonStatusBySettingChange();
    UpdateData(FALSE);
}

void CDialogOptionMisc::OnCheckShowTrayIcon() 
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
    UpdateButtonStatusBySettingChange();
    UpdateData(FALSE);
}

void CDialogOptionMisc::OnCheckEnableLog() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    UpdateButtonStatusBySettingChange();
    UpdateControlStatus();
    UpdateData(FALSE);
}

void CDialogOptionMisc::OnSelchangeComboLogLevel() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    UpdateButtonStatusBySettingChange();
    UpdateData(FALSE);
}

void CDialogOptionMisc::OnSelchangeComboLogFileSize() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    UpdateButtonStatusBySettingChange();
    UpdateData(FALSE);
}

void CDialogOptionMisc::OnCheckAutoStart() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    UpdateButtonStatusBySettingChange();
    UpdateData(FALSE);
}
