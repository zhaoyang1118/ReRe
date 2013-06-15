#if !defined(AFX_DIALOGOPTION_H__439D931E_62EE_473F_8132_190028E841A9__INCLUDED_)
#define AFX_DIALOGOPTION_H__439D931E_62EE_473F_8132_190028E841A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogOption.h : header file
//

typedef enum {
    PAGE_OPTION_WIZARD_WELCOME = 0,
    PAGE_OPTION_TIME,
    PAGE_OPTION_NOTIFY,
    PAGE_OPTION_AUTO_AWAY,
    PAGE_OPTION_LANGUAGE,
    PAGE_OPTION_MISC,

    PAGE_OPTION_FIRST = PAGE_OPTION_TIME,
    PAGE_OPTION_LAST = PAGE_OPTION_MISC,

    PAGE_OPTION_WIZARD_FIRST = PAGE_OPTION_WIZARD_WELCOME,
    PAGE_OPTION_WIZARD_LAST = PAGE_OPTION_TIME,
} EOptionPageIndex;

typedef enum {
    OPTION_SETTING_UNCHANGED = 0,
    OPTION_SETTING_CHANGED,
    OPTION_SETTING_APPLIED,
    OPTION_SETTING_SAVED,

    OPTION_SETTING_FIRST = OPTION_SETTING_UNCHANGED,
    OPTION_SETTING_LAST = OPTION_SETTING_SAVED,
} EOptionSettingStatus;


/////////////////////////////////////////////////////////////////////////////
// CDialogOption dialog

class CDialogOption : public CDialog
{
public:
    // tab窗口定义
    CDialogOptionTime       m_dlgTime;
    CDialogOptionNotify     m_dlgNotify;
    CDialogOptionAutoAway   m_dlgAutoAway;
    CDialogOptionLanguage   m_dlgLanguage;
    CDialogOptionMisc       m_dlgMisc;
    // 主界面窗口指针
    CRelaxReminderDlg       *m_pdlgMain;
    // 页面按钮按下时的字体
    CFont                   m_fontPageButtonNormal;
    CFont                   m_fontPageButtonPressed;

    // 选择新页面
    void                    PageSelect(EOptionPageIndex eIndex);
    // 根据配置是否被更改的状态，改变按钮状态
    void                    ChangeButtonStatus(EOptionSettingStatus eStatus);
    // 加载界面语言
    void                    LoadLanguageStrings();

// Construction
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
    CDialogOption(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
    //{{AFX_DATA(CDialogOption)
	enum { IDD = IDD_DIALOG_OPTION };
	int		m_iPage;
	//}}AFX_DATA


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CDialogOption)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:
	CToolTipCtrl m_tooltip;

    // Generated message map functions
    //{{AFX_MSG(CDialogOption)
    virtual BOOL OnInitDialog();
    afx_msg void OnButtonApply();
    afx_msg void OnButtonReset();
    afx_msg void OnButtonSave();
	afx_msg void OnRadioOptionTime();
	afx_msg void OnRadioOptionNotify();
	afx_msg void OnRadioOptionAutoAway();
	afx_msg void OnRadioOptionLanguage();
	afx_msg void OnRadioOptionMisc();
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGOPTION_H__439D931E_62EE_473F_8132_190028E841A9__INCLUDED_)
