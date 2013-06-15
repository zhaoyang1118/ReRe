// DialogOptionTime.cpp : implementation file
//

#include "stdafx.h"
#include "RelaxReminder.h"
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
#include "DialogSetupWizardWelcome.h"
#include "DialogSetupWizard.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogOptionTime dialog


CDialogOptionTime::CDialogOptionTime(CWnd* pParent /*=NULL*/)
    : CDialog(CDialogOptionTime::IDD, pParent)
{
    //{{AFX_DATA_INIT(CDialogOptionTime)
    m_bEnableLongRelax = FALSE;
    m_strLongRelaxDuration = _T("");
    m_strLongRelaxFrequency = _T("");
    m_strShortRelaxDuration = _T("");
    m_strWorkDuration = _T("");
    //}}AFX_DATA_INIT
}


void CDialogOptionTime::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDialogOptionTime)
    DDX_Check(pDX, IDC_CHECK_ENABLE_LONG_RELAX, m_bEnableLongRelax);
    DDX_CBString(pDX, IDC_COMBO_LONG_RELAX_DURATION, m_strLongRelaxDuration);
    DDX_CBString(pDX, IDC_COMBO_LONG_RELAX_FREQUENCY, m_strLongRelaxFrequency);
    DDX_CBString(pDX, IDC_COMBO_SHORT_RELAX_DURATION, m_strShortRelaxDuration);
    DDX_CBString(pDX, IDC_COMBO_WORK_DURATION, m_strWorkDuration);
    //}}AFX_DATA_MAP
    DDX_Control(pDX, IDC_BUTTON_NEXT, m_btnNext);
}


BEGIN_MESSAGE_MAP(CDialogOptionTime, CDialog)
    //{{AFX_MSG_MAP(CDialogOptionTime)
    ON_BN_CLICKED(IDC_CHECK_ENABLE_LONG_RELAX, OnCheckEnableLongRelax)
    ON_CBN_EDITUPDATE(IDC_COMBO_WORK_DURATION, OnEditupdateComboWorkDuration)
    ON_CBN_SELCHANGE(IDC_COMBO_WORK_DURATION, OnSelchangeComboWorkDuration)
    ON_CBN_EDITCHANGE(IDC_COMBO_SHORT_RELAX_DURATION, OnEditchangeComboShortRelaxDuration)
    ON_CBN_SELCHANGE(IDC_COMBO_SHORT_RELAX_DURATION, OnSelchangeComboShortRelaxDuration)
    ON_CBN_EDITCHANGE(IDC_COMBO_LONG_RELAX_FREQUENCY, OnEditchangeComboLongRelaxFrequency)
    ON_CBN_SELCHANGE(IDC_COMBO_LONG_RELAX_FREQUENCY, OnSelchangeComboLongRelaxFrequency)
    ON_CBN_EDITCHANGE(IDC_COMBO_LONG_RELAX_DURATION, OnEditchangeComboLongRelaxDuration)
    ON_CBN_SELCHANGE(IDC_COMBO_LONG_RELAX_DURATION, OnSelchangeComboLongRelaxDuration)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, OnButtonNext)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogOptionTime message handlers

BOOL CDialogOptionTime::OnInitDialog() 
{
    CDialog::OnInitDialog();
    
    // TODO: Add extra initialization here
    ASSERT(m_pdlgMain != NULL);

    LoadLanguageStrings();

    // 读取当前的设置
    LoadFromCurrentSetting();

    m_btnNext.SetIcon(IDR_MAINFRAME);
    m_btnNext.SetAlign(CButtonST::ST_ALIGN_HORIZ_RIGHT);
    m_btnNext.SetTooltipText(_T("Click to Start!"));
    m_btnNext.SizeToContent();

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDialogOptionTime::LoadFromCurrentSetting()
{
    m_strWorkDuration.Format("%d",            m_pdlgMain->m_tm.GetWD() / 60);
    m_strShortRelaxDuration.Format("%d",    m_pdlgMain->m_tm.GetSRD() / 60);
    m_bEnableLongRelax = m_pdlgMain->m_tm.GetEnableLongRelax();
    m_strLongRelaxFrequency.Format("%d",    m_pdlgMain->m_tm.GetLRF());
    m_strLongRelaxDuration.Format("%d",        m_pdlgMain->m_tm.GetLRD() / 60);

    UpdateControlStatus();
    UpdateData(FALSE);
    return TRUE;
}

void CDialogOptionTime::LoadSettingFromDefault()
{
    m_strWorkDuration.Format("%d",            DEFAULT_WORK_DURATION / 60);
    m_strShortRelaxDuration.Format("%d",    DEFAULT_SHORT_RELAX_DURATION / 60);
    m_bEnableLongRelax = m_pdlgMain->m_tm.GetEnableLongRelax();
    m_strLongRelaxFrequency.Format("%d",    DEFAULT_LONG_RELAX_FREQUENCY);
    m_strLongRelaxDuration.Format("%d",        DEFAULT_LONG_RELAX_DURATION / 60);

    UpdateControlStatus();
    UpdateData(FALSE);
}

void CDialogOptionTime::UpdateControlStatus()
{
    GetDlgItem(IDC_COMBO_LONG_RELAX_FREQUENCY)->EnableWindow(m_bEnableLongRelax);
    GetDlgItem(IDC_COMBO_LONG_RELAX_DURATION)->EnableWindow(m_bEnableLongRelax);

    BOOL bSetupWizard = FALSE;
    bSetupWizard = (m_pdlgOption == NULL);
    GetDlgItem(IDC_STATIC_TIPS)->ShowWindow(bSetupWizard ? SW_HIDE : SW_SHOW);
    GetDlgItem(IDC_BUTTON_NEXT)->ShowWindow(bSetupWizard ? SW_SHOW : SW_HIDE);
    GetDlgItem(IDC_STATIC_START)->ShowWindow(bSetupWizard ? SW_SHOW : SW_HIDE);
}

BOOL CDialogOptionTime::CheckSetting()
{
    CStringTable *pst = &(m_pdlgMain->m_str);

    // 取出当前设置窗口中的值
    UpdateData(TRUE);

    // 首先检查所有的下拉框中是否是数字
    if (IsNumber(m_strWorkDuration) == FALSE)
    {
        return FALSE;
    }
    if (IsNumber(m_strShortRelaxDuration) == FALSE)
    {
        return FALSE;
    }
    if (IsNumber(m_strLongRelaxFrequency) == FALSE)
    {
        return FALSE;
    }
    if (IsNumber(m_strLongRelaxDuration) == FALSE)
    {
        return FALSE;
    }

    // 检查参数设置是否合理
    // 工作时间不能小于5分钟
    if (atoi(m_strWorkDuration) < 5)
    {
        MessageBox(pst->GetStr(OPTION_TIME_CHECK_FAIL_WORK_DURATION),
                   pst->GetStr(OPTION_CHECK_FAIL_CAPTION),
                   MB_ICONSTOP);
        return FALSE;
    }
    // 短休息时间不能小于1分钟
    if (atoi(m_strShortRelaxDuration) < 1)
    {
        MessageBox(pst->GetStr(OPTION_TIME_CHECK_FAIL_SHORT_RELAX_DURATION),
                   pst->GetStr(OPTION_CHECK_FAIL_CAPTION),
                   MB_ICONSTOP);
        return FALSE;
    }
    // 如果启用了长休息，那么长休息时间不能小于短休息时间
    if (m_bEnableLongRelax == TRUE && atoi(m_strLongRelaxDuration) < atoi(m_strShortRelaxDuration))
    {
        MessageBox(pst->GetStr(OPTION_TIME_CHECK_FAIL_LONG_RELAX_DURATION),
                   pst->GetStr(OPTION_CHECK_FAIL_CAPTION),
                   MB_ICONSTOP);
        return FALSE;
    }

    return TRUE;
}

BOOL CDialogOptionTime::ApplySetting()
{
    RelaxTimer  *ptm = &(m_pdlgMain->m_tm);

    ptm->SetWD(atoi(m_strWorkDuration) * 60);
    ptm->SetSRD(atoi(m_strShortRelaxDuration) * 60);
    ptm->SetEnableLongRelax(m_bEnableLongRelax);
    ptm->SetLRF(atoi(m_strLongRelaxFrequency));
    ptm->SetLRD(atoi(m_strLongRelaxDuration) * 60);

    return TRUE;
}

void CDialogOptionTime::UpdateButtonStatusBySettingChange()
{
    if (NULL == m_pdlgOption)
    {
        return;
    }

    m_pdlgOption->ChangeButtonStatus(OPTION_SETTING_CHANGED);
}

void CDialogOptionTime::LoadLanguageStrings()
{
    CStringTable *pst;

    pst = &(m_pdlgMain->m_str);
    SetDlgItemText(IDC_STATIC_SHORT_RELAX, pst->GetStr(OPTION_TIME_SHORT_RELAX));
    SetDlgItemText(IDC_STATIC_SHORT_RELAX_WD, pst->GetStr(OPTION_TIME_SHORT_RELAX_WD));
    SetDlgItemText(IDC_STATIC_SHORT_RELAX_WD_UNIT, pst->GetStr(OPTION_TIME_SHORT_RELAX_WD_UNIT));
    SetDlgItemText(IDC_STATIC_SHORT_RELAX_SRD, pst->GetStr(OPTION_TIME_SHORT_RELAX_SRD));
    SetDlgItemText(IDC_STATIC_SHORT_RELAX_SRD_UNIT, pst->GetStr(OPTION_TIME_SHORT_RELAX_SRD_UNIT));
    SetDlgItemText(IDC_CHECK_ENABLE_LONG_RELAX, pst->GetStr(OPTION_TIME_LONG_RELAX));
    SetDlgItemText(IDC_STATIC_LONG_RELAX_LRF, pst->GetStr(OPTION_TIME_LONG_RELAX_LRF));
    SetDlgItemText(IDC_STATIC_LONG_RELAX_LRF_UNIT, pst->GetStr(OPTION_TIME_LONG_RELAX_LRF_UNIT));
    SetDlgItemText(IDC_STATIC_LONG_RELAX_LRD, pst->GetStr(OPTION_TIME_LONG_RELAX_LRD));
    SetDlgItemText(IDC_STATIC_LONG_RELAX_LRD_UNIT, pst->GetStr(OPTION_TIME_LONG_RELAX_LRD_UNIT));
    SetDlgItemText(IDC_STATIC_TIPS, pst->GetStr(OPTION_TIME_TIPS));
    SetDlgItemText(IDC_STATIC_SETTING_REFERENCE, pst->GetStr(OPTION_TIME_SETTING_REFERENCE));
    Invalidate(TRUE);
}

void CDialogOptionTime::OnCheckEnableLongRelax() 
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
    UpdateControlStatus();
    UpdateButtonStatusBySettingChange();
    UpdateData(FALSE);
}

void CDialogOptionTime::OnEditupdateComboWorkDuration() 
{
    // TODO: Add your control notification handler code here
    UpdateButtonStatusBySettingChange();
}

void CDialogOptionTime::OnSelchangeComboWorkDuration() 
{
    // TODO: Add your control notification handler code here
    UpdateButtonStatusBySettingChange();
}

void CDialogOptionTime::OnEditchangeComboShortRelaxDuration() 
{
    // TODO: Add your control notification handler code here
    UpdateButtonStatusBySettingChange();
}

void CDialogOptionTime::OnSelchangeComboShortRelaxDuration() 
{
    // TODO: Add your control notification handler code here
    UpdateButtonStatusBySettingChange();
}

void CDialogOptionTime::OnEditchangeComboLongRelaxFrequency() 
{
    // TODO: Add your control notification handler code here
    UpdateButtonStatusBySettingChange();
}

void CDialogOptionTime::OnSelchangeComboLongRelaxFrequency() 
{
    // TODO: Add your control notification handler code here
    UpdateButtonStatusBySettingChange();
}

void CDialogOptionTime::OnEditchangeComboLongRelaxDuration() 
{
    // TODO: Add your control notification handler code here
    UpdateButtonStatusBySettingChange();
}

void CDialogOptionTime::OnSelchangeComboLongRelaxDuration() 
{
    // TODO: Add your control notification handler code here
    UpdateButtonStatusBySettingChange();
}

void CDialogOptionTime::OnButtonNext() 
{
	// TODO: Add your control notification handler code here
    ((CDialogSetupWizard*)GetParent())->FinishProcess();
}
