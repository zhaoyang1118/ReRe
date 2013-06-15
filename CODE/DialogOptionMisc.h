#if !defined(AFX_DIALOGOPTIONMISC_H__E2FD0797_67EC_48EC_8A80_874328C50704__INCLUDED_)
#define AFX_DIALOGOPTIONMISC_H__E2FD0797_67EC_48EC_8A80_874328C50704__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogOptionMisc.h : header file
//


/////////////////////////////////////////////////////////////////////////////
// CDialogOptionMisc dialog

class CDialogOptionMisc : public CDialog
{
public:
    CRelaxReminderDlg       *m_pdlgMain;
    CDialogOption           *m_pdlgOption;
    BOOL                    LoadFromCurrentSetting();
    void                    LoadSettingFromDefault();
    void                    UpdateControlStatus();
    BOOL                    CheckSetting();
    BOOL                    ApplySetting();
    // 根据Option窗口的状态，设置Option窗口的按钮是否可用
    void                    UpdateButtonStatusBySettingChange();
    // 加载界面语言
    void                    LoadLanguageStrings();

// Construction
public:
    CDialogOptionMisc(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
    //{{AFX_DATA(CDialogOptionMisc)
	enum { IDD = IDD_DIALOG_OPTION_MISC };
    BOOL    m_bCloseMonitor;
    BOOL    m_bLockComputer;
	BOOL	m_bEnableLog;
	int		m_iLogFileSize;
	int		m_iLogLevel;
	BOOL	m_bAutoStart;
	BOOL	m_bShowFloatingWindowAtStartup;
	BOOL	m_bShowTrayIconAtStartup;
	//}}AFX_DATA


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CDialogOptionMisc)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(CDialogOptionMisc)
    virtual BOOL OnInitDialog();
    afx_msg void OnCheckLockCompter();
    afx_msg void OnCheckCloseMonitor();
    afx_msg void OnCheckShowFloatingWindow();
    afx_msg void OnCheckShowTrayIcon();
    afx_msg void OnCheckEnableLog();
	afx_msg void OnSelchangeComboLogLevel();
	afx_msg void OnSelchangeComboLogFileSize();
	afx_msg void OnCheckAutoStart();
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGOPTIONMISC_H__E2FD0797_67EC_48EC_8A80_874328C50704__INCLUDED_)
