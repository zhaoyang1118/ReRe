#if !defined(AFX_DIALOGOPTIONLANGUAGE_H__688D4DC8_E4D0_40A9_9FF8_5BFA6B0A731C__INCLUDED_)
#define AFX_DIALOGOPTIONLANGUAGE_H__688D4DC8_E4D0_40A9_9FF8_5BFA6B0A731C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogOptionLanguage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogOptionLanguage dialog

class CDialogOptionLanguage : public CDialog
{
public:
    CRelaxReminderDlg       *m_pdlgMain;
    CDialogOption           *m_pdlgOption;
    CString                 m_strLanguageId;
    BOOL                    LoadLanguageListFromIniFile();
    void                    LoadListCtrl();
    BOOL                    InsertItem(char *pchLanguageId, char *pchLanguageName, BOOL bAvailable = TRUE);
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
	CDialogOptionLanguage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogOptionLanguage)
	enum { IDD = IDD_DIALOG_OPTION_LANGUAGE };
	CListCtrl	m_listLanguages;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogOptionLanguage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogOptionLanguage)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickListLanguages(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGOPTIONLANGUAGE_H__688D4DC8_E4D0_40A9_9FF8_5BFA6B0A731C__INCLUDED_)
