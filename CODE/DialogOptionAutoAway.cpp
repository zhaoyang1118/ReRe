// DialogOptionAutoAway.cpp : implementation file
//

#include "stdafx.h"
#include "relaxreminder.h"
#include "DefaultValue.h"
#include "PubFunc.h"
#include "LibFunc.h"
#include "BtnST.h"
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
// CDialogOptionAutoAway dialog


CDialogOptionAutoAway::CDialogOptionAutoAway(CWnd* pParent /*=NULL*/)
    : CDialog(CDialogOptionAutoAway::IDD, pParent)
{
    //{{AFX_DATA_INIT(CDialogOptionAutoAway)
    m_bEnableAutoPause = FALSE;
    m_bEnableAutoReset = FALSE;
    m_strAutoPauseThreshold = _T("");
    m_strAutoResetThreshold = _T("");
	m_bEnableFullScreenPause = FALSE;
	//}}AFX_DATA_INIT
}


void CDialogOptionAutoAway::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDialogOptionAutoAway)
    DDX_Check(pDX, IDC_CHECK_ENABLE_AUTO_PAUSE, m_bEnableAutoPause);
    DDX_Check(pDX, IDC_CHECK_ENABLE_AUTO_RESET, m_bEnableAutoReset);
    DDX_CBString(pDX, IDC_COMBO_AUTO_PAUSE_THRESHOLD, m_strAutoPauseThreshold);
    DDX_CBString(pDX, IDC_COMBO_AUTO_RESET_THRESHOLD, m_strAutoResetThreshold);
	DDX_Check(pDX, IDC_CHECK_FULLSCREEN_PAUSE, m_bEnableFullScreenPause);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogOptionAutoAway, CDialog)
    //{{AFX_MSG_MAP(CDialogOptionAutoAway)
    ON_BN_CLICKED(IDC_CHECK_ENABLE_AUTO_PAUSE, OnCheckEnableAutoPause)
    ON_BN_CLICKED(IDC_CHECK_ENABLE_AUTO_RESET, OnCheckEnableAutoReset)
    ON_CBN_EDITCHANGE(IDC_COMBO_AUTO_PAUSE_THRESHOLD, OnEditchangeComboAutoPauseThreshold)
    ON_CBN_SELCHANGE(IDC_COMBO_AUTO_PAUSE_THRESHOLD, OnSelchangeComboAutoPauseThreshold)
    ON_CBN_EDITCHANGE(IDC_COMBO_AUTO_RESET_THRESHOLD, OnEditchangeComboAutoResetThreshold)
    ON_CBN_SELCHANGE(IDC_COMBO_AUTO_RESET_THRESHOLD, OnSelchangeComboAutoResetThreshold)
	ON_BN_CLICKED(IDC_CHECK_FULLSCREEN_PAUSE, OnCheckFullscreenPause)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogOptionAutoAway message handlers

BOOL CDialogOptionAutoAway::OnInitDialog() 
{
    CDialog::OnInitDialog();
    
    // TODO: Add extra initialization here
    // 读取当前的设置
    LoadFromCurrentSetting();

    LoadLanguageStrings();
    
    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDialogOptionAutoAway::LoadFromCurrentSetting()
{
    m_bEnableAutoPause          = m_pdlgMain->m_tm.GetEnableAutoPause();
    m_bEnableFullScreenPause    = m_pdlgMain->m_tm.GetEnableFullScreenPause();
    m_bEnableAutoReset          = m_pdlgMain->m_tm.GetEnableAutoReset();
    UpdateData(FALSE);
    UpdateSettingStatusByCheck();
    m_strAutoPauseThreshold.Format("%d", m_pdlgMain->m_tm.GetAPT() / 60);
    m_strAutoResetThreshold.Format("%d", m_pdlgMain->m_tm.GetART() / 60);
    GetDlgItem(IDC_COMBO_AUTO_PAUSE_THRESHOLD)->SetWindowText(m_strAutoPauseThreshold);
    GetDlgItem(IDC_COMBO_AUTO_RESET_THRESHOLD)->SetWindowText(m_strAutoResetThreshold);
    return TRUE;
}

void CDialogOptionAutoAway::LoadSettingFromDefault()
{
    m_bEnableAutoPause          = DEFAULT_ENABLE_AUTO_PAUSE;
    m_bEnableFullScreenPause    = DEFAULT_ENABLE_FULLSCREEN_PAUSE;
    m_bEnableAutoReset          = DEFAULT_ENABLE_AUTO_RESET;
    UpdateSettingStatusByCheck();
    UpdateData(FALSE);
    m_strAutoPauseThreshold.Format("%d", DEFAULT_AUTO_PAUSE_THRESHOLD / 60);
    m_strAutoResetThreshold.Format("%d", DEFAULT_AUTO_RESET_THRESHOLD / 60);
    GetDlgItem(IDC_COMBO_AUTO_PAUSE_THRESHOLD)->SetWindowText(m_strAutoPauseThreshold);
    GetDlgItem(IDC_COMBO_AUTO_RESET_THRESHOLD)->SetWindowText(m_strAutoResetThreshold);
}

void CDialogOptionAutoAway::UpdateSettingStatusByCheck()
{
    GetDlgItem(IDC_COMBO_AUTO_PAUSE_THRESHOLD)->EnableWindow(m_bEnableAutoPause);
    GetDlgItem(IDC_COMBO_AUTO_RESET_THRESHOLD)->EnableWindow(m_bEnableAutoReset);
}

BOOL CDialogOptionAutoAway::CheckSetting()
{
    // 取出当前设置窗口中的值
    UpdateData(TRUE);

    // 首先检查所有的下拉框中是否是数字
    if (IsNumber(m_strAutoPauseThreshold) == FALSE)
    {
        return FALSE;
    }
    if (IsNumber(m_strAutoResetThreshold) == FALSE)
    {
        return FALSE;
    }
    
    // 检查参数设置是否合理
    // 自动暂停时间不能超过自动复位时间
    if (m_bEnableAutoPause && m_bEnableAutoReset)
    {
        if (atoi(m_strAutoPauseThreshold) > atoi(m_strAutoResetThreshold))
        {
            CStringTable *pst = &(m_pdlgMain->m_str);
            MessageBox(pst->GetStr(OPTION_AUTOAWAY_CHECK_FAIL_AUTO_RESET_INTERVAL),
                       pst->GetStr(OPTION_CHECK_FAIL_CAPTION),
                       MB_ICONSTOP);
            return FALSE;
        }
    }

    return TRUE;
}

BOOL CDialogOptionAutoAway::ApplySetting()
{
    RelaxTimer  *ptm = &(m_pdlgMain->m_tm);

    ptm->SetEnableAutoPause(m_bEnableAutoPause);
    ptm->SetAPT(atoi(m_strAutoPauseThreshold) * 60);
    ptm->SetEnableFullScreenPause(m_bEnableFullScreenPause);
    ptm->SetEnableAutoReset(m_bEnableAutoReset);
    ptm->SetART(atoi(m_strAutoResetThreshold) * 60);

    return TRUE;
}

void CDialogOptionAutoAway::UpdateButtonStatusBySettingChange()
{
    if (NULL == m_pdlgOption)
    {
        return;
    }
    
    m_pdlgOption->ChangeButtonStatus(OPTION_SETTING_CHANGED);
}

void CDialogOptionAutoAway::LoadLanguageStrings()
{
    CStringTable *pst;
    
    pst = &(m_pdlgMain->m_str);
    SetDlgItemText(IDC_STATIC_AUTO_PAUSE, pst->GetStr(OPTION_AUTOAWAY_AUTO_PAUSE));
    SetDlgItemText(IDC_CHECK_ENABLE_AUTO_PAUSE, pst->GetStr(OPTION_AUTOAWAY_AUTO_PAUSE_AFTER));
    SetDlgItemText(IDC_STATIC_AUTO_PAUSE_IDLE, pst->GetStr(OPTION_AUTOAWAY_AUTO_PAUSE_IDLE));
    SetDlgItemText(IDC_CHECK_FULLSCREEN_PAUSE, pst->GetStr(OPTION_AUTOAWAY_AUTO_PAUSE_FULLSCREEN));
    SetDlgItemText(IDC_STATIC_AUTO_RESET, pst->GetStr(OPTION_AUTOAWAY_AUTO_RESET));
    SetDlgItemText(IDC_CHECK_ENABLE_AUTO_RESET, pst->GetStr(OPTION_AUTOAWAY_AUTO_RESET_AFTER));
    SetDlgItemText(IDC_STATIC_AUTO_RESET_IDLE, pst->GetStr(OPTION_AUTOAWAY_AUTO_RESET_IDLE));
    Invalidate(TRUE);
}

void CDialogOptionAutoAway::OnCheckEnableAutoPause() 
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
    UpdateSettingStatusByCheck();
    UpdateButtonStatusBySettingChange();
}

void CDialogOptionAutoAway::OnCheckEnableAutoReset() 
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
    UpdateSettingStatusByCheck();
    UpdateButtonStatusBySettingChange();
}

void CDialogOptionAutoAway::OnEditchangeComboAutoPauseThreshold() 
{
    // TODO: Add your control notification handler code here
    UpdateButtonStatusBySettingChange();
}

void CDialogOptionAutoAway::OnSelchangeComboAutoPauseThreshold() 
{
    // TODO: Add your control notification handler code here
    UpdateButtonStatusBySettingChange();
}

void CDialogOptionAutoAway::OnEditchangeComboAutoResetThreshold() 
{
    // TODO: Add your control notification handler code here
    UpdateButtonStatusBySettingChange();
}

void CDialogOptionAutoAway::OnSelchangeComboAutoResetThreshold() 
{
    // TODO: Add your control notification handler code here
    UpdateButtonStatusBySettingChange();
}

void CDialogOptionAutoAway::OnCheckFullscreenPause() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    UpdateButtonStatusBySettingChange();
}
