// DialogSetupWizardWelcome.cpp : implementation file
//

#include "stdafx.h"
#include "relaxreminder.h"
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
#include "DialogSetupWizardWelcome.h"
#include "DialogSetupWizard.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogSetupWizardWelcome dialog


CDialogSetupWizardWelcome::CDialogSetupWizardWelcome(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogSetupWizardWelcome::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogSetupWizardWelcome)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDialogSetupWizardWelcome::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogSetupWizardWelcome)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
    DDX_Control(pDX, IDC_BUTTON_NEXT, m_btnNext);
}


BEGIN_MESSAGE_MAP(CDialogSetupWizardWelcome, CDialog)
	//{{AFX_MSG_MAP(CDialogSetupWizardWelcome)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, OnButtonNext)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogSetupWizardWelcome message handlers

BOOL CDialogSetupWizardWelcome::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    m_btnNext.SetBitmaps(IDB_BITMAP_WIZARD_LOGO_IN, RGB(255, 255, 255),
                         IDB_BITMAP_WIZARD_LOGO_OUT, RGB(255, 255, 255));
    m_btnNext.SetAlign(CButtonST::ST_ALIGN_VERT, FALSE);
    m_btnNext.SetPressedStyle(CButtonST::BTNST_PRESSED_LEFTRIGHT, FALSE);
    m_btnNext.SizeToContent();
    m_btnNext.DrawBorder(FALSE, FALSE);
    m_btnNext.SetTooltipText(_T("Click to continue..."));
    m_btnNext.CenterWindow();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialogSetupWizardWelcome::OnButtonNext() 
{
	// TODO: Add your control notification handler code here
    ((CDialogSetupWizard*)GetParent())->PageSelect(PAGE_OPTION_TIME);
}
