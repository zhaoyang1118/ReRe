// DialogOption.cpp : implementation file
//

#include "stdafx.h"
#include "RelaxReminder.h"
#include "PubFunc.h"
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
// CDialogOption dialog


CDialogOption::CDialogOption(CWnd* pParent /*=NULL*/)
    : CDialog(CDialogOption::IDD, pParent)
{
    //{{AFX_DATA_INIT(CDialogOption)
	m_iPage = -1;
	//}}AFX_DATA_INIT
}


void CDialogOption::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDialogOption)
	DDX_Radio(pDX, IDC_RADIO_OPTION_TIME, m_iPage);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogOption, CDialog)
    //{{AFX_MSG_MAP(CDialogOption)
    ON_BN_CLICKED(IDC_BUTTON_APPLY, OnButtonApply)
    ON_BN_CLICKED(IDC_BUTTON_RESET, OnButtonReset)
    ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
	ON_BN_CLICKED(IDC_RADIO_OPTION_TIME, OnRadioOptionTime)
	ON_BN_CLICKED(IDC_RADIO_OPTION_NOTIFY, OnRadioOptionNotify)
	ON_BN_CLICKED(IDC_RADIO_OPTION_AUTO_AWAY, OnRadioOptionAutoAway)
	ON_BN_CLICKED(IDC_RADIO_OPTION_LANGUAGE, OnRadioOptionLanguage)
	ON_BN_CLICKED(IDC_RADIO_OPTION_MISC, OnRadioOptionMisc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogOption message handlers

BOOL CDialogOption::OnInitDialog() 
{
    CDialog::OnInitDialog();
    
    // TODO: Add extra initialization here
    CenterWindow(GetDesktopWindow());

    // 设置窗口指针
    ASSERT(m_pdlgMain != NULL);
    m_dlgTime.m_pdlgMain        = m_pdlgMain;
    m_dlgTime.m_pdlgOption      = this;
    m_dlgNotify.m_pdlgMain      = m_pdlgMain;
    m_dlgNotify.m_pdlgOption    = this;
    m_dlgAutoAway.m_pdlgMain    = m_pdlgMain;
    m_dlgAutoAway.m_pdlgOption  = this;
    m_dlgLanguage.m_pdlgMain    = m_pdlgMain;
    m_dlgLanguage.m_pdlgOption  = this;
    m_dlgMisc.m_pdlgMain        = m_pdlgMain;
    m_dlgMisc.m_pdlgOption      = this;

    // 创建子对话框
    m_dlgTime.Create(IDD_DIALOG_OPTION_TIME, this);
    m_dlgNotify.Create(IDD_DIALOG_OPTION_NOTIFY, this);
    m_dlgAutoAway.Create(IDD_DIALOG_OPTION_AUTO_AWAY, this);
    m_dlgLanguage.Create(IDD_DIALOG_OPTION_LANGUAGE, this);
    m_dlgMisc.Create(IDD_DIALOG_OPTION_MISC, this);

    // 调整子对话框在父窗口中的位置
    CRect rs;
    GetDlgItem(IDC_STATIC_PLAT)->GetClientRect(rs);
    GetDlgItem(IDC_STATIC_PLAT)->ClientToScreen(rs);
    ScreenToClient(rs);
    
    
    // 设置子对话框尺寸并移动到指定位置
    m_dlgTime.MoveWindow(rs);
    m_dlgNotify.MoveWindow(rs);
    m_dlgAutoAway.MoveWindow(rs);
    m_dlgLanguage.MoveWindow(rs);
    m_dlgMisc.MoveWindow(rs);

    // 设置页面按钮字体
    m_fontPageButtonNormal.CreateFont(13,0,0,0,FW_NORMAL,FALSE,FALSE,FALSE,  
        ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,  
        DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"Tahoma");
    m_fontPageButtonPressed.CreateFont(16,0,0,0,FW_BOLD,FALSE,FALSE,FALSE,  
        ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,  
        DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"Tahoma");

    // 显示第一页tab内容
    ((CButton*)GetDlgItem(IDC_RADIO_OPTION_TIME))->SetCheck(TRUE);
    PageSelect(PAGE_OPTION_TIME);

    // 初始化时，配置状态为未更改
    ChangeButtonStatus(OPTION_SETTING_UNCHANGED);

    // CG: The following block was added by the ToolTips component.
    {
        // Create the ToolTip control.
        m_tooltip.Create(this);
        m_tooltip.SetDelayTime(TTDT_AUTOPOP, 20000);
        m_tooltip.SetMaxTipWidth(270);
        m_tooltip.Activate(TRUE);

        // TODO: Use one of the following forms to add controls:
        CStringTable *pst = &(m_pdlgMain->m_str);
        m_tooltip.AddTool(GetDlgItem(IDC_BUTTON_RESET),
                          pst->GetStr(OPTION_BUTTON_RESET_TIP));
        m_tooltip.AddTool(GetDlgItem(IDC_BUTTON_APPLY),
                          pst->GetStr(OPTION_BUTTON_APPLY_TIP));
        m_tooltip.AddTool(GetDlgItem(IDC_BUTTON_SAVE),
                          pst->GetStr(OPTION_BUTTON_SAVE_TIP));
    }
    
    LoadLanguageStrings();

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}
    
void CDialogOption::PageSelect(EOptionPageIndex eIndex)
{
    CWnd *pwndBtnTime = GetDlgItem(IDC_RADIO_OPTION_TIME);
    CWnd *pwndBtnNotify = GetDlgItem(IDC_RADIO_OPTION_NOTIFY);
    CWnd *pwndBtnAutoAway = GetDlgItem(IDC_RADIO_OPTION_AUTO_AWAY);
    CWnd *pwndBtnLanguage = GetDlgItem(IDC_RADIO_OPTION_LANGUAGE);
    CWnd *pwndBtnMisc = GetDlgItem(IDC_RADIO_OPTION_MISC);

    m_dlgTime.ShowWindow(PAGE_OPTION_TIME == eIndex);
    m_dlgNotify.ShowWindow(PAGE_OPTION_NOTIFY == eIndex);
    m_dlgAutoAway.ShowWindow(PAGE_OPTION_AUTO_AWAY == eIndex);
    m_dlgLanguage.ShowWindow(PAGE_OPTION_LANGUAGE == eIndex);
    m_dlgMisc.ShowWindow(PAGE_OPTION_MISC == eIndex);

    pwndBtnTime->SetFont((PAGE_OPTION_TIME == eIndex) ? &m_fontPageButtonPressed : &m_fontPageButtonNormal);
    pwndBtnNotify->SetFont((PAGE_OPTION_NOTIFY == eIndex) ? &m_fontPageButtonPressed : &m_fontPageButtonNormal);
    pwndBtnAutoAway->SetFont((PAGE_OPTION_AUTO_AWAY == eIndex) ? &m_fontPageButtonPressed : &m_fontPageButtonNormal);
    pwndBtnLanguage->SetFont((PAGE_OPTION_LANGUAGE == eIndex) ? &m_fontPageButtonPressed : &m_fontPageButtonNormal);
    pwndBtnMisc->SetFont((PAGE_OPTION_MISC == eIndex) ? &m_fontPageButtonPressed : &m_fontPageButtonNormal);
}

void CDialogOption::ChangeButtonStatus(EOptionSettingStatus eStatus)
{
    CWnd    *pwndBtnApply   = GetDlgItem(IDC_BUTTON_APPLY);
    CWnd    *pwndBtnSave    = GetDlgItem(IDC_BUTTON_SAVE);

    switch (eStatus)
    {
    case OPTION_SETTING_UNCHANGED:
    case OPTION_SETTING_SAVED:
        pwndBtnApply->EnableWindow(FALSE);
        pwndBtnSave->EnableWindow(FALSE);
        break;
    case OPTION_SETTING_CHANGED:
        pwndBtnApply->EnableWindow(TRUE);
        pwndBtnSave->EnableWindow(FALSE);
        break;
    case OPTION_SETTING_APPLIED:
        pwndBtnApply->EnableWindow(FALSE);
        pwndBtnSave->EnableWindow(TRUE);
    	break;
    default:
        break;
    }
}

void CDialogOption::LoadLanguageStrings()
{
    CStringTable *pst = &(m_pdlgMain->m_str);

    SetWindowText(pst->GetStr(OPTION_CAPTION));

    SetDlgItemText(IDC_RADIO_OPTION_TIME, pst->GetStr(OPTION_PAGE_TIME));
    SetDlgItemText(IDC_RADIO_OPTION_NOTIFY, pst->GetStr(OPTION_PAGE_NOTIFY));
    SetDlgItemText(IDC_RADIO_OPTION_AUTO_AWAY, pst->GetStr(OPTION_PAGE_AUTO_AWAY));
    SetDlgItemText(IDC_RADIO_OPTION_LANGUAGE, pst->GetStr(OPTION_PAGE_LANGUAGE));
    SetDlgItemText(IDC_RADIO_OPTION_MISC, pst->GetStr(OPTION_PAGE_MISC));

    SetDlgItemText(IDC_BUTTON_RESET, pst->GetStr(OPTION_BUTTON_RESET));
    SetDlgItemText(IDC_BUTTON_APPLY, pst->GetStr(OPTION_BUTTON_APPLY));
    SetDlgItemText(IDC_BUTTON_SAVE, pst->GetStr(OPTION_BUTTON_SAVE));

    m_tooltip.UpdateTipText(pst->GetStr(OPTION_BUTTON_RESET_TIP),
                            GetDlgItem(IDC_BUTTON_RESET));
    m_tooltip.UpdateTipText(pst->GetStr(OPTION_BUTTON_APPLY_TIP),
                            GetDlgItem(IDC_BUTTON_APPLY));
    m_tooltip.UpdateTipText(pst->GetStr(OPTION_BUTTON_SAVE_TIP),
                            GetDlgItem(IDC_BUTTON_SAVE));
    Invalidate(TRUE);
}

void CDialogOption::OnButtonReset() 
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);

    switch (PAGE_OPTION_FIRST + m_iPage)
    {
    case PAGE_OPTION_TIME:
        m_dlgTime.LoadSettingFromDefault();
        break;
    case PAGE_OPTION_NOTIFY:
        m_dlgNotify.LoadSettingFromDefault();
        break;
    case PAGE_OPTION_AUTO_AWAY:
        m_dlgAutoAway.LoadSettingFromDefault();
        break;
    case PAGE_OPTION_LANGUAGE:
        m_dlgLanguage.LoadSettingFromDefault();
        break;
    case PAGE_OPTION_MISC:
        m_dlgMisc.LoadSettingFromDefault();
        break;
    default:
        break;
    }

    // 设置按钮状态
    ChangeButtonStatus(OPTION_SETTING_CHANGED);
}

void CDialogOption::OnButtonApply() 
{
    // TODO: Add your control notification handler code here
    BOOL    bSettingCheckOK = TRUE;

    bSettingCheckOK &= m_dlgTime.CheckSetting();
    bSettingCheckOK &= m_dlgNotify.CheckSetting();
    bSettingCheckOK &= m_dlgAutoAway.CheckSetting();
    bSettingCheckOK &= m_dlgLanguage.CheckSetting();
    bSettingCheckOK &= m_dlgMisc.CheckSetting();

    if (FALSE == bSettingCheckOK)
    {
        return;
    }

    m_dlgTime.ApplySetting();
    m_dlgNotify.ApplySetting();
    m_dlgAutoAway.ApplySetting();
    m_dlgLanguage.ApplySetting();
    m_dlgMisc.ApplySetting();

    ChangeButtonStatus(OPTION_SETTING_APPLIED);
}

void CDialogOption::OnButtonSave() 
{
    // TODO: Add your control notification handler code here

    // 注意：保存设置之前，应当确保已经应用了当前设置
    m_pdlgMain->SaveSettingToIniFile();

    // 关闭Option窗口
    EndDialog(0);
}

BOOL CDialogOption::PreTranslateMessage(MSG* pMsg)
{
	// CG: The following block was added by the ToolTips component.
	{
		// Let the ToolTip process this message.
		m_tooltip.RelayEvent(pMsg);
	}
	return CDialog::PreTranslateMessage(pMsg);	// CG: This was added by the ToolTips component.
}

void CDialogOption::OnRadioOptionTime() 
{
	// TODO: Add your control notification handler code here
    PageSelect(PAGE_OPTION_TIME);
}

void CDialogOption::OnRadioOptionNotify() 
{
	// TODO: Add your control notification handler code here
    PageSelect(PAGE_OPTION_NOTIFY);
}

void CDialogOption::OnRadioOptionAutoAway() 
{
	// TODO: Add your control notification handler code here
    PageSelect(PAGE_OPTION_AUTO_AWAY);
}

void CDialogOption::OnRadioOptionLanguage() 
{
	// TODO: Add your control notification handler code here
    PageSelect(PAGE_OPTION_LANGUAGE);
}

void CDialogOption::OnRadioOptionMisc() 
{
	// TODO: Add your control notification handler code here
    PageSelect(PAGE_OPTION_MISC);
}
