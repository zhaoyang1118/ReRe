// DialogAboutDonate.cpp : implementation file
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
#include "DialogAboutDonate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ADD_DONATOR(NAME)                                   \
{                                                           \
    strDonators += FmtName + NAME + FmtLineEnd + FmtEnd;    \
}

/////////////////////////////////////////////////////////////////////////////
// CDialogAboutDonate dialog


CDialogAboutDonate::CDialogAboutDonate(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogAboutDonate::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogAboutDonate)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDialogAboutDonate::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogAboutDonate)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogAboutDonate, CDialog)
	//{{AFX_MSG_MAP(CDialogAboutDonate)
	ON_WM_CTLCOLOR()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogAboutDonate message handlers

BOOL CDialogAboutDonate::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    CString FmtName     = "<font align='left' size='12'>";
    CString FmtEnd      = "</font>";
    CString FmtLineEnd  = "<br>";

    m_fontAppeal.CreateFont(15,0,0,0,FW_BOLD,FALSE,FALSE,FALSE,  
        ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,  
        DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"Tahoma");
    GetDlgItem(IDC_STATIC_DONATION_APPEAL)->SetFont(&m_fontAppeal);

    CString strDonators;
    strDonators.Empty();
    ADD_DONATOR("p****q@yeah.net");
    strDonators += FmtLineEnd + FmtLineEnd + FmtLineEnd + FmtLineEnd + FmtLineEnd;    // padding

    m_wndDonators.FormatDataString(strDonators);
    m_wndDonators.m_crInternalTransparentColor = GetSysColor(COLOR_3DFACE);
    m_wndDonators.m_nTimerSpeed = 60;
    m_wndDonators.Create(0, WS_VISIBLE | WS_CHILD, IDC_STATIC_DONATORS,
        this, 0, 0, 0);

    SetDlgItemText(IDC_EDIT_DONATION_ACCOUNT, "zhaoyang1118@gmail.com");
    GetDlgItem(IDC_STATIC_PAYPAL_LOGO)->GetWindowRect(m_rectPaypal);
    GetDlgItem(IDC_STATIC_ALIPAY_LOGO)->GetWindowRect(m_rectAlipay);
    ScreenToClient(m_rectPaypal);
    ScreenToClient(m_rectAlipay);

    LoadLanguageStrings();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

HBRUSH CDialogAboutDonate::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
    if (pWnd->GetDlgCtrlID() == IDC_STATIC_DONATION_APPEAL) 
    {
        pDC->SetTextColor(RGB(0, 0, 127));
        pDC->SetBkMode(TRANSPARENT);
    }

	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CDialogAboutDonate::LoadLanguageStrings()
{
    CStringTable *pst = &(m_pdlgMain->m_str);
    
    SetDlgItemText(IDC_STATIC_DONATION_APPEAL, pst->GetStr(ABOUT_DONATE_DONATION_APPEAL));
    SetDlgItemText(IDC_STATIC_DONATION_LIST, pst->GetStr(ABOUT_DONATE_DONATION_LIST_HEADER));
    SetDlgItemText(IDC_STATIC_TIPS, pst->GetStr(ABOUT_DONATE_DONATION_TIPS));
    Invalidate(TRUE);
}

void CDialogAboutDonate::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
    if (m_rectPaypal.PtInRect(point) || m_rectAlipay.PtInRect(point))
    {
        SetCursor(AfxGetApp()->LoadOEMCursor(OCR_HAND));
    }
	
	CDialog::OnMouseMove(nFlags, point);
}

void CDialogAboutDonate::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
    if (m_rectPaypal.PtInRect(point))
    {
        if (nFlags == MK_LBUTTON) 
        {
            ShellExecute(NULL, NULL, "http://www.paypal.com", NULL, NULL, SW_NORMAL); 
        }
    }
    if (m_rectAlipay.PtInRect(point))
    {
        if (nFlags == MK_LBUTTON) 
        {
            ShellExecute(NULL, NULL, "http://www.alipay.com", NULL, NULL, SW_NORMAL); 
        }
    }
	
	CDialog::OnLButtonDown(nFlags, point);
}
