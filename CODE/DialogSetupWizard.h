#if !defined(AFX_DIALOGSETUPWIZARD_H__5DC32AAB_7F0E_4A1C_9858_F7761078F27C__INCLUDED_)
#define AFX_DIALOGSETUPWIZARD_H__5DC32AAB_7F0E_4A1C_9858_F7761078F27C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogSetupWizard.h : header file
//


/////////////////////////////////////////////////////////////////////////////
// CDialogSetupWizard dialog

class CDialogSetupWizard : public CDialog
{
public:
    // tab窗口定义
    CDialogSetupWizardWelcome   m_dlgWelcome;
    CDialogOptionTime           m_dlgTime;
    // 主界面窗口指针
    CRelaxReminderDlg           *m_pdlgMain;
    EOptionPageIndex            m_ePage;
    // 选择新页面
    void                        PageSelect(EOptionPageIndex eIndex);
    // Wizard完成，设置选项值
    BOOL                        FinishProcess(void);
// Construction
public:
	CDialogSetupWizard(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogSetupWizard)
	enum { IDD = IDD_DIALOG_SETUP_WIZARD };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogSetupWizard)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogSetupWizard)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGSETUPWIZARD_H__5DC32AAB_7F0E_4A1C_9858_F7761078F27C__INCLUDED_)
