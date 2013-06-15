// DialogOptionNotify.cpp : implementation file
//

#include "stdafx.h"
#include "RelaxReminder.h"
#include "DefaultValue.h"
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


typedef enum {
    COLOR_BLACK = 0,
    COLOR_CUSTOM,
} EColorType;


/////////////////////////////////////////////////////////////////////////////
// CDialogOptionNotify dialog


CDialogOptionNotify::CDialogOptionNotify(CWnd* pParent /*=NULL*/)
    : CDialog(CDialogOptionNotify::IDD, pParent)
{
    //{{AFX_DATA_INIT(CDialogOptionNotify)
    m_bPreNotify = FALSE;
    m_bLockInput = FALSE;
    m_iLockType = -1;
    m_bDarkerScreen = FALSE;
	m_iAnimateType = -1;
	m_iColorType = -1;
	m_iDarkerScreenType = -1;
	m_iNotifyWindowType = -1;
	//}}AFX_DATA_INIT
}


void CDialogOptionNotify::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDialogOptionNotify)
    DDX_Control(pDX, IDC_SLIDER_ALPHA, m_sliderAlpha);
    DDX_Check(pDX, IDC_CHECK_PRENOTIFY, m_bPreNotify);
    DDX_Check(pDX, IDC_CHECK_LOCK_INPUT, m_bLockInput);
    DDX_Radio(pDX, IDC_RADIO_LOCK_KEYBOARD, m_iLockType);
    DDX_Check(pDX, IDC_CHECK_DARKER_SCREEN, m_bDarkerScreen);
	DDX_Radio(pDX, IDC_RADIO_ANIMATION_OFF, m_iAnimateType);
	DDX_Radio(pDX, IDC_RADIO_COLOR_BLACK, m_iColorType);
	DDX_Radio(pDX, IDC_RADIO_MULTIMON_DARKER_SCREEN_MASTER, m_iDarkerScreenType);
	DDX_Radio(pDX, IDC_RADIO_MULTIMON_NOTIFY_WINDOW_MASTER, m_iNotifyWindowType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogOptionNotify, CDialog)
    //{{AFX_MSG_MAP(CDialogOptionNotify)
    ON_BN_CLICKED(IDC_CHECK_PRENOTIFY, OnCheckPrenotify)
    ON_BN_CLICKED(IDC_CHECK_LOCK_INPUT, OnCheckLockInput)
    ON_BN_CLICKED(IDC_RADIO_LOCK_KEYBOARD, OnRadioLockKeyboard)
    ON_BN_CLICKED(IDC_RADIO_LOCK_MOUSE, OnRadioLockMouse)
    ON_BN_CLICKED(IDC_RADIO_LOCK_BOTH, OnRadioLockBoth)
    ON_BN_CLICKED(IDC_CHECK_DARKER_SCREEN, OnCheckDarkerScreen)
    ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_ALPHA, OnCustomdrawSliderAlpha)
	ON_BN_CLICKED(IDC_RADIO_ANIMATION_OFF, OnRadioAnimationOff)
	ON_BN_CLICKED(IDC_RADIO_ANIMATION_FAST, OnRadioAnimationFast)
	ON_BN_CLICKED(IDC_RADIO_ANIMATION_MEDIUM, OnRadioAnimationMedium)
	ON_BN_CLICKED(IDC_RADIO_ANIMATION_SLOW, OnRadioAnimationSlow)
	ON_BN_CLICKED(IDC_RADIO_COLOR_BLACK, OnRadioColorBlack)
	ON_BN_CLICKED(IDC_RADIO_COLOR_CUSTOM, OnRadioColorCustom)
	ON_WM_PAINT()
	ON_WM_LBUTTONDBLCLK()
	ON_BN_CLICKED(IDC_RADIO_MULTIMON_DARKER_SCREEN_MASTER, OnRadioMultimonDarkerScreenMaster)
	ON_BN_CLICKED(IDC_RADIO_MULTIMON_DARKER_SCREEN_CURSOR, OnRadioMultimonDarkerScreenCursor)
	ON_BN_CLICKED(IDC_RADIO_MULTIMON_DARKER_SCREEN_ALL, OnRadioMultimonDarkerScreenAll)
	ON_BN_CLICKED(IDC_RADIO_MULTIMON_NOTIFY_WINDOW_MASTER, OnRadioMultimonNotifyWindowMaster)
	ON_BN_CLICKED(IDC_RADIO_MULTIMON_NOTIFY_WINDOW_CURSOR, OnRadioMultimonNotifyWindowCursor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogOptionNotify message handlers

BOOL CDialogOptionNotify::OnInitDialog() 
{
    CDialog::OnInitDialog();
    
    // TODO: Add extra initialization here
    m_sliderAlpha.SetRange(1,255);

    GetDlgItem(IDC_STATIC_COLOR)->GetWindowRect(m_rectColorView);
    m_rectColorView.DeflateRect(2, 2, 3, 3);
    ScreenToClient(&m_rectColorView);

    // 读取当前的设置
    LoadFromCurrentSetting();

    LoadLanguageStrings();
    
    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDialogOptionNotify::LoadFromCurrentSetting()
{
    m_bPreNotify = m_pdlgMain->m_bPreNotify;
    m_bLockInput = m_pdlgMain->m_bLockInput;
    m_iLockType  = m_pdlgMain->m_iLockType;
    m_bDarkerScreen = m_pdlgMain->m_bDarkerScreen;
    m_iAlpha        = m_pdlgMain->m_iDarkerScreenAlpha;
    m_iAnimateType  = m_pdlgMain->m_eDarkerScreenAnimateType;
    m_color         = m_pdlgMain->m_colorDarkerScreen;
    m_iColorType    = (m_color == RGB(0,0,0)) ? COLOR_BLACK : COLOR_CUSTOM;
    m_iDarkerScreenType = m_pdlgMain->m_eDarkerScreenType;
    m_iNotifyWindowType = m_pdlgMain->m_eNotifyWindowType;

    UpdateData(FALSE);
    UpdateControlStatus();
    return TRUE;
}

void CDialogOptionNotify::LoadSettingFromDefault()
{
    m_bPreNotify = DEFAULT_ENABLE_PRENOTIFY;
    m_bLockInput = DEFAULT_ENABLE_LOCK_INPUT;
    m_iLockType  = DEFAULT_LOCK_TYPE;
    m_bDarkerScreen = DEFAULT_ENABLE_DARKER_SCREEN;
    m_iAlpha        = DEFAULT_DARKER_SCREEN_ALPHA;
    m_iAnimateType  = DEFAULT_DARKER_SCREEN_ANIMATE;
    m_color         = DEFAULT_DARKER_SCREEN_COLOR;
    m_iColorType    = (m_color == RGB(0,0,0)) ? COLOR_BLACK : COLOR_CUSTOM;
    m_iDarkerScreenType = DEFAULT_DARKER_SCREEN_TYPE;
    m_iNotifyWindowType = DEFAULT_NOTIFY_WINDOW_TYPE;

    UpdateData(FALSE);
    UpdateControlStatus();
}

void CDialogOptionNotify::UpdateControlStatus()
{
    UpdateData(TRUE);

    GetDlgItem(IDC_RADIO_LOCK_KEYBOARD)->EnableWindow(m_bLockInput);
    GetDlgItem(IDC_RADIO_LOCK_MOUSE)->EnableWindow(m_bLockInput);
    GetDlgItem(IDC_RADIO_LOCK_BOTH)->EnableWindow(m_bLockInput);

    ((CButton*)GetDlgItem(IDC_CHECK_DARKER_SCREEN))->SetCheck(m_bDarkerScreen);
    GetDlgItem(IDC_STATIC_SCREEN_MASK_TRANSPARENCY)->EnableWindow(m_bDarkerScreen);
    GetDlgItem(IDC_STATIC_SCREEN_MASK_TRANSPARENCY_TRANSPARENT)->EnableWindow(m_bDarkerScreen);
    GetDlgItem(IDC_STATIC_SCREEN_MASK_TRANSPARENCY_OPAQUE)->EnableWindow(m_bDarkerScreen);
    GetDlgItem(IDC_SLIDER_ALPHA)->EnableWindow(m_bDarkerScreen);
    GetDlgItem(IDC_STATIC_SCREEN_MASK_COLOR)->EnableWindow(m_bDarkerScreen);
    GetDlgItem(IDC_RADIO_COLOR_BLACK)->EnableWindow(m_bDarkerScreen);
    GetDlgItem(IDC_RADIO_COLOR_CUSTOM)->EnableWindow(m_bDarkerScreen);
    GetDlgItem(IDC_STATIC_SCREEN_MASK_ANIMATION)->EnableWindow(m_bDarkerScreen);
    GetDlgItem(IDC_RADIO_ANIMATION_OFF)->EnableWindow(m_bDarkerScreen);
    GetDlgItem(IDC_RADIO_ANIMATION_FAST)->EnableWindow(m_bDarkerScreen);
    GetDlgItem(IDC_RADIO_ANIMATION_MEDIUM)->EnableWindow(m_bDarkerScreen);
    GetDlgItem(IDC_RADIO_ANIMATION_SLOW)->EnableWindow(m_bDarkerScreen);
    m_sliderAlpha.SetPos(m_iAlpha);

    InvalidateRect(m_rectColorView);    // 更新color view区域

    BOOL bMultiMonitorDetected = (m_pdlgMain->m_iMonitorCount > 1);
    GetDlgItem(IDC_STATIC_MULTIMON)->EnableWindow(bMultiMonitorDetected);
    GetDlgItem(IDC_STATIC_MULTIMON_DARKER_SCREEN)->EnableWindow(bMultiMonitorDetected && m_bDarkerScreen);
    GetDlgItem(IDC_RADIO_MULTIMON_DARKER_SCREEN_MASTER)->EnableWindow(bMultiMonitorDetected && m_bDarkerScreen);
    GetDlgItem(IDC_RADIO_MULTIMON_DARKER_SCREEN_CURSOR)->EnableWindow(bMultiMonitorDetected && m_bDarkerScreen);
    GetDlgItem(IDC_RADIO_MULTIMON_DARKER_SCREEN_ALL)->EnableWindow(bMultiMonitorDetected && m_bDarkerScreen);
    GetDlgItem(IDC_STATIC_MULTIMON_NOTIFY_WINDOW)->EnableWindow(bMultiMonitorDetected);
    GetDlgItem(IDC_RADIO_MULTIMON_NOTIFY_WINDOW_MASTER)->EnableWindow(bMultiMonitorDetected);
    GetDlgItem(IDC_RADIO_MULTIMON_NOTIFY_WINDOW_CURSOR)->EnableWindow(bMultiMonitorDetected);

    UpdateData(FALSE);
}

BOOL CDialogOptionNotify::CheckSetting()
{
    // 取出当前设置窗口中的值
    UpdateData(TRUE);

    return TRUE;
}

BOOL CDialogOptionNotify::ApplySetting()
{
    m_pdlgMain->m_bPreNotify = m_bPreNotify;
    m_pdlgMain->m_bLockInput = m_bLockInput;
    m_pdlgMain->m_iLockType  = m_iLockType;
    m_pdlgMain->m_bDarkerScreen         = m_bDarkerScreen;
    m_pdlgMain->m_iDarkerScreenAlpha    = m_iAlpha;
    m_pdlgMain->m_eDarkerScreenAnimateType  = (EAnimateType)m_iAnimateType;
    m_pdlgMain->m_colorDarkerScreen = (m_iColorType == COLOR_BLACK) ? RGB(0,0,0) : m_color;
    m_pdlgMain->m_eDarkerScreenType = (EMultiMonitorType)m_iDarkerScreenType;
    m_pdlgMain->m_eNotifyWindowType = (EMultiMonitorType)m_iNotifyWindowType;
    
    return TRUE;
}

void CDialogOptionNotify::UpdateButtonStatusBySettingChange()
{
    if (NULL == m_pdlgOption)
    {
        return;
    }
    
    m_pdlgOption->ChangeButtonStatus(OPTION_SETTING_CHANGED);
}

void CDialogOptionNotify::LoadLanguageStrings()
{
    CStringTable *pst;
    
    pst = &(m_pdlgMain->m_str);
    SetDlgItemText(IDC_CHECK_PRENOTIFY, pst->GetStr(OPTION_NOTIFY_PRENOTIFY));
    SetDlgItemText(IDC_CHECK_LOCK_INPUT, pst->GetStr(OPTION_NOTIFY_LOCK_INPUT));
    SetDlgItemText(IDC_RADIO_LOCK_KEYBOARD, pst->GetStr(OPTION_NOTIFY_LOCK_INPUT_KEYBOARD));
    SetDlgItemText(IDC_RADIO_LOCK_MOUSE, pst->GetStr(OPTION_NOTIFY_LOCK_INPUT_MOUSE));
    SetDlgItemText(IDC_RADIO_LOCK_BOTH, pst->GetStr(OPTION_NOTIFY_LOCK_INPUT_BOTH));
    SetDlgItemText(IDC_CHECK_DARKER_SCREEN, pst->GetStr(OPTION_NOTIFY_SCREEN_MASK));
    SetDlgItemText(IDC_STATIC_SCREEN_MASK_TRANSPARENCY, pst->GetStr(OPTION_NOTIFY_SCREEN_MASK_TRANSPARENCY));
    SetDlgItemText(IDC_STATIC_SCREEN_MASK_TRANSPARENCY_TRANSPARENT, pst->GetStr(OPTION_NOTIFY_SCREEN_MASK_TRANSPARENCY_TRANSPARENT));
    SetDlgItemText(IDC_STATIC_SCREEN_MASK_TRANSPARENCY_OPAQUE, pst->GetStr(OPTION_NOTIFY_SCREEN_MASK_TRANSPARENCY_OPAQUE));
    SetDlgItemText(IDC_STATIC_SCREEN_MASK_COLOR, pst->GetStr(OPTION_NOTIFY_SCREEN_MASK_COLOR));
    SetDlgItemText(IDC_RADIO_COLOR_BLACK, pst->GetStr(OPTION_NOTIFY_SCREEN_MASK_COLOR_BLACK));
    SetDlgItemText(IDC_RADIO_COLOR_CUSTOM, pst->GetStr(OPTION_NOTIFY_SCREEN_MASK_COLOR_CUSTOM));
    SetDlgItemText(IDC_STATIC_SCREEN_MASK_ANIMATION, pst->GetStr(OPTION_NOTIFY_SCREEN_MASK_ANIMATION));
    SetDlgItemText(IDC_RADIO_ANIMATION_OFF, pst->GetStr(OPTION_NOTIFY_SCREEN_MASK_ANIMATION_OFF));
    SetDlgItemText(IDC_RADIO_ANIMATION_FAST, pst->GetStr(OPTION_NOTIFY_SCREEN_MASK_ANIMATION_FAST));
    SetDlgItemText(IDC_RADIO_ANIMATION_MEDIUM, pst->GetStr(OPTION_NOTIFY_SCREEN_MASK_ANIMATION_MEDIUM));
    SetDlgItemText(IDC_RADIO_ANIMATION_SLOW, pst->GetStr(OPTION_NOTIFY_SCREEN_MASK_ANIMATION_SLOW));

    SetDlgItemText(IDC_STATIC_MULTIMON, pst->GetStr(OPTION_NOTIFY_MULTIMON));
    SetDlgItemText(IDC_STATIC_MULTIMON_DARKER_SCREEN, pst->GetStr(OPTION_NOTIFY_MULTIMON_DARKER_SCREEN));
    SetDlgItemText(IDC_RADIO_MULTIMON_DARKER_SCREEN_MASTER, pst->GetStr(OPTION_NOTIFY_MULTIMON_DARKER_SCREEN_MASTER));
    SetDlgItemText(IDC_RADIO_MULTIMON_DARKER_SCREEN_CURSOR, pst->GetStr(OPTION_NOTIFY_MULTIMON_DARKER_SCREEN_CURSOR));
    SetDlgItemText(IDC_RADIO_MULTIMON_DARKER_SCREEN_ALL, pst->GetStr(OPTION_NOTIFY_MULTIMON_DARKER_SCREEN_ALL));
    SetDlgItemText(IDC_STATIC_MULTIMON_NOTIFY_WINDOW, pst->GetStr(OPTION_NOTIFY_MULTIMON_NOTIFY_WINDOW));
    SetDlgItemText(IDC_RADIO_MULTIMON_NOTIFY_WINDOW_MASTER, pst->GetStr(OPTION_NOTIFY_MULTIMON_NOTIFY_WINDOW_MASTER));
    SetDlgItemText(IDC_RADIO_MULTIMON_NOTIFY_WINDOW_CURSOR, pst->GetStr(OPTION_NOTIFY_MULTIMON_NOTIFY_WINDOW_CURSOR));

    Invalidate(TRUE);
}

void CDialogOptionNotify::OnCheckPrenotify() 
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
    UpdateButtonStatusBySettingChange();
    UpdateData(FALSE);
}

void CDialogOptionNotify::OnCheckLockInput() 
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
    UpdateControlStatus();
    UpdateButtonStatusBySettingChange();
    UpdateData(FALSE);
}

void CDialogOptionNotify::OnRadioLockKeyboard() 
{
    // TODO: Add your control notification handler code here
    if (m_iLockType != RELAX_LOCK_KEYBOARD)
    {
        UpdateButtonStatusBySettingChange();
    }
}

void CDialogOptionNotify::OnRadioLockMouse() 
{
    // TODO: Add your control notification handler code here
    if (m_iLockType != RELAX_LOCK_MOUSE)
    {
        UpdateButtonStatusBySettingChange();
    }    
}

void CDialogOptionNotify::OnRadioLockBoth() 
{
    // TODO: Add your control notification handler code here
    if (m_iLockType != RELAX_LOCK_BOTH)
    {
        UpdateButtonStatusBySettingChange();
    }
}

void CDialogOptionNotify::OnCheckDarkerScreen() 
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
    m_iAlpha = m_sliderAlpha.GetPos();
    UpdateControlStatus();
    UpdateButtonStatusBySettingChange();
    UpdateData(FALSE);
}

void CDialogOptionNotify::OnCustomdrawSliderAlpha(NMHDR* pNMHDR, LRESULT* pResult) 
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
    if (m_bDarkerScreen)
    {
        if (m_iAlpha != m_sliderAlpha.GetPos())
        {
            m_iAlpha = m_sliderAlpha.GetPos();
            UpdateButtonStatusBySettingChange();
        }
    }
    UpdateData(FALSE);
    *pResult = 0;
}

void CDialogOptionNotify::OnRadioAnimationOff() 
{
	// TODO: Add your control notification handler code here
    if (m_iAnimateType != ANIMATE_OFF)
    {
        UpdateButtonStatusBySettingChange();
    }
}

void CDialogOptionNotify::OnRadioAnimationFast() 
{
	// TODO: Add your control notification handler code here
    if (m_iAnimateType != ANIMATE_FAST)
    {
        UpdateButtonStatusBySettingChange();
    }
}

void CDialogOptionNotify::OnRadioAnimationMedium() 
{
	// TODO: Add your control notification handler code here
    if (m_iAnimateType != ANIMATE_MEDIUM)
    {
        UpdateButtonStatusBySettingChange();
    }
}

void CDialogOptionNotify::OnRadioAnimationSlow() 
{
	// TODO: Add your control notification handler code here
    if (m_iAnimateType != ANIMATE_SLOW)
    {
        UpdateButtonStatusBySettingChange();
    }
}

void CDialogOptionNotify::OnRadioColorBlack() 
{
	// TODO: Add your control notification handler code here
    if (m_iColorType != COLOR_BLACK)
    {
        UpdateData(TRUE);
        InvalidateRect(m_rectColorView);    // 更新color view区域
        UpdateButtonStatusBySettingChange();
    }
}

void CDialogOptionNotify::OnRadioColorCustom() 
{
	// TODO: Add your control notification handler code here
    if (m_iColorType != COLOR_CUSTOM)
    {
        UpdateData(TRUE);
        CColorDialog colordlg(m_color);
        colordlg.m_cc.Flags |= CC_FULLOPEN;	// 颜色对话框显示全部
        if(colordlg.DoModal() == IDOK)
        {
            m_color = colordlg.GetColor();
        }
        InvalidateRect(m_rectColorView);    // 更新color view区域
        UpdateButtonStatusBySettingChange();
    }
}

void CDialogOptionNotify::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
    COLORREF color;
    color = (m_bDarkerScreen && (m_iColorType == COLOR_CUSTOM)) ?
            m_color : GetSysColor(COLOR_3DFACE);
    CBrush br(color);
    dc.FillRect(m_rectColorView, &br);
	// Do not call CDialog::OnPaint() for painting messages
}

void CDialogOptionNotify::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
    if (m_bDarkerScreen && (m_iColorType == COLOR_CUSTOM))
    {
        if(m_rectColorView.PtInRect(point))
        {			
            CColorDialog colordlg(m_color);
            colordlg.m_cc.Flags |= CC_FULLOPEN;	// 颜色对话框显示全部
            if(colordlg.DoModal() == IDOK)
            {
                m_color = colordlg.GetColor();
                UpdateButtonStatusBySettingChange();
            }
            InvalidateRect(m_rectColorView);    // 更新color view区域
        }
    }
	CDialog::OnLButtonDblClk(nFlags, point);
}

void CDialogOptionNotify::OnRadioMultimonDarkerScreenMaster() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    UpdateButtonStatusBySettingChange();
    m_iNotifyWindowType = m_iDarkerScreenType;
    UpdateData(FALSE);
}

void CDialogOptionNotify::OnRadioMultimonDarkerScreenCursor() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    UpdateButtonStatusBySettingChange();
    m_iNotifyWindowType = m_iDarkerScreenType;
    UpdateData(FALSE);
}

void CDialogOptionNotify::OnRadioMultimonDarkerScreenAll() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    UpdateButtonStatusBySettingChange();
    UpdateData(FALSE);
}

void CDialogOptionNotify::OnRadioMultimonNotifyWindowMaster() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    UpdateButtonStatusBySettingChange();
    if (m_iDarkerScreenType != ALL_MONITOR)
    {
        m_iDarkerScreenType = m_iNotifyWindowType;
    }
    UpdateData(FALSE);
}

void CDialogOptionNotify::OnRadioMultimonNotifyWindowCursor() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    UpdateButtonStatusBySettingChange();
    if (m_iDarkerScreenType != ALL_MONITOR)
    {
        m_iDarkerScreenType = m_iNotifyWindowType;
    }
    UpdateData(FALSE);
}
