#if !defined(AFX_DIALOGSETUPWIZARDWELCOME_H__61A6C6CB_3A1D_4172_AD59_9F83C34BB395__INCLUDED_)
#define AFX_DIALOGSETUPWIZARDWELCOME_H__61A6C6CB_3A1D_4172_AD59_9F83C34BB395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogSetupWizardWelcome.h : header file
//


/////////////////////////////////////////////////////////////////////////////
// CDialogSetupWizardWelcome dialog

class CDialogSetupWizardWelcome : public CDialog
{
public:
    CRelaxReminderDlg       *m_pdlgMain;
    CButtonST               m_btnNext;
// Construction
public:
	CDialogSetupWizardWelcome(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogSetupWizardWelcome)
	enum { IDD = IDD_DIALOG_SETUP_WIZARD_WELCOME };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogSetupWizardWelcome)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogSetupWizardWelcome)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonNext();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGSETUPWIZARDWELCOME_H__61A6C6CB_3A1D_4172_AD59_9F83C34BB395__INCLUDED_)
