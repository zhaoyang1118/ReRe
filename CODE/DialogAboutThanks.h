#if !defined(AFX_DIALOGABOUTTHANKS_H__EEEB0117_3363_41E5_8915_B35CC26F83C0__INCLUDED_)
#define AFX_DIALOGABOUTTHANKS_H__EEEB0117_3363_41E5_8915_B35CC26F83C0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogAboutThanks.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogAboutThanks dialog

class CDialogAboutThanks : public CDialog
{
public:
    CRelaxReminderDlg       *m_pdlgMain;
    // 加载界面语言
    void    LoadLanguageStrings();
private:
    // Contributers的字体类型
    CCreditsCtrl    m_wndCtbter, m_wndExtCtbter;

// Construction
public:
    CDialogAboutThanks(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
    //{{AFX_DATA(CDialogAboutThanks)
    enum { IDD = IDD_DIALOG_ABOUT_THANKS };
        // NOTE: the ClassWizard will add data members here
    //}}AFX_DATA


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CDialogAboutThanks)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(CDialogAboutThanks)
    virtual BOOL OnInitDialog();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGABOUTTHANKS_H__EEEB0117_3363_41E5_8915_B35CC26F83C0__INCLUDED_)
