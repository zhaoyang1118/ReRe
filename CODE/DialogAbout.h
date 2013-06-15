#if !defined(AFX_DIALOGABOUT_H__FDBFC417_5B4A_4CA6_A397_D297F937E7FA__INCLUDED_)
#define AFX_DIALOGABOUT_H__FDBFC417_5B4A_4CA6_A397_D297F937E7FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogAbout.h : header file
//


typedef enum {
    PAGE_ABOUT_ABOUT = 0,
    PAGE_ABOUT_THANKS,
    PAGE_ABOUT_CHANGELOG,
    PAGE_ABOUT_STATISTICS,
    PAGE_ABOUT_DONATE,
    
    PAGE_ABOUT_FIRST = PAGE_ABOUT_ABOUT,
    PAGE_ABOUT_LAST = PAGE_ABOUT_DONATE,
} EAboutPageIndex;


/////////////////////////////////////////////////////////////////////////////
// CDialogAbout dialog

class CDialogAbout : public CDialog
{
public:
    // tab窗口定义
    CDialogAboutAbout           m_dlgAbout;
    CDialogAboutThanks          m_dlgThanks;
    CDialogAboutChangelog       m_dlgChangelog;
    CDialogAboutStatistics      m_dlgStatistics;
    CDialogAboutDonate          m_dlgDonate;
    // 主界面窗口指针
    CRelaxReminderDlg           *m_pdlgMain;
    // 页面按钮按下时的字体
    CFont                       m_fontPageButtonNormal;
    CFont                       m_fontPageButtonPressed;
public:
    // 选择新页面
    void                        PageSelect(EAboutPageIndex eIndex);
    // 加载界面语言
    void                        LoadLanguageStrings();
// Construction
public:
    CDialogAbout(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
    //{{AFX_DATA(CDialogAbout)
	enum { IDD = IDD_DIALOG_ABOUT };
	int		m_iPage;
	//}}AFX_DATA


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CDialogAbout)
	protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(CDialogAbout)
    virtual BOOL OnInitDialog();
	afx_msg void OnRadioAboutAbout();
	afx_msg void OnRadioAboutThanks();
	afx_msg void OnRadioAboutChangelog();
	afx_msg void OnRadioAboutStatistics();
	afx_msg void OnRadioAboutDonate();
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGABOUT_H__FDBFC417_5B4A_4CA6_A397_D297F937E7FA__INCLUDED_)
