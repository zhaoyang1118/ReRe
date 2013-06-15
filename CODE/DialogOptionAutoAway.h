#if !defined(AFX_DIALOGOPTIONAUTOAWAY_H__AC1915C3_2D82_405E_9F31_AAAAAABE8A05__INCLUDED_)
#define AFX_DIALOGOPTIONAUTOAWAY_H__AC1915C3_2D82_405E_9F31_AAAAAABE8A05__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogOptionAutoAway.h : header file
//


/////////////////////////////////////////////////////////////////////////////
// CDialogOptionAutoAway dialog

class CDialogOptionAutoAway : public CDialog
{
public:
    CRelaxReminderDlg       *m_pdlgMain;
    CDialogOption           *m_pdlgOption;
    BOOL                    LoadFromCurrentSetting();
    void                    LoadSettingFromDefault();
    // 根据是否启用自动状态转换，设置自动状态转换的选项是否可用
    void                    UpdateSettingStatusByCheck();
    BOOL                    CheckSetting();
    BOOL                    ApplySetting();
    // 根据Option窗口的状态，设置Option窗口的按钮是否可用
    void                    UpdateButtonStatusBySettingChange();
    // 加载界面语言
    void                    LoadLanguageStrings();

    // Construction
public:
    CDialogOptionAutoAway(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
    //{{AFX_DATA(CDialogOptionAutoAway)
	enum { IDD = IDD_DIALOG_OPTION_AUTO_AWAY };
    BOOL    m_bEnableAutoPause;
    BOOL    m_bEnableAutoReset;
    CString    m_strAutoPauseThreshold;
    CString    m_strAutoResetThreshold;
	BOOL	m_bEnableFullScreenPause;
	//}}AFX_DATA


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CDialogOptionAutoAway)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(CDialogOptionAutoAway)
    virtual BOOL OnInitDialog();
    afx_msg void OnCheckEnableAutoPause();
    afx_msg void OnCheckEnableAutoReset();
    afx_msg void OnEditchangeComboAutoPauseThreshold();
    afx_msg void OnSelchangeComboAutoPauseThreshold();
    afx_msg void OnEditchangeComboAutoResetThreshold();
    afx_msg void OnSelchangeComboAutoResetThreshold();
	afx_msg void OnCheckFullscreenPause();
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGOPTIONAUTOAWAY_H__AC1915C3_2D82_405E_9F31_AAAAAABE8A05__INCLUDED_)
