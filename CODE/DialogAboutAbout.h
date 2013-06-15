#if !defined(AFX_DIALOGABOUTABOUT_H__F0B082C7_6187_41FB_984E_DD0968AEFBB2__INCLUDED_)
#define AFX_DIALOGABOUTABOUT_H__F0B082C7_6187_41FB_984E_DD0968AEFBB2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogAboutAbout.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogAboutAbout dialog

class CDialogAboutAbout : public CDialog
{
public:
    CRelaxReminderDlg       *m_pdlgMain;
    // 加载界面语言
    void    LoadLanguageStrings();
private:
    // HttpLink的字体类型
    CRect   m_rectHttp;
    CRect   m_rectEmail;
    CFont   m_fontLink;
    CFont   m_fontLinkMouseOn;
// Construction
public:
    CDialogAboutAbout(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
    //{{AFX_DATA(CDialogAboutAbout)
    enum { IDD = IDD_DIALOG_ABOUT_ABOUT };
        // NOTE: the ClassWizard will add data members here
    //}}AFX_DATA


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CDialogAboutAbout)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(CDialogAboutAbout)
    virtual BOOL OnInitDialog();
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGABOUTABOUT_H__F0B082C7_6187_41FB_984E_DD0968AEFBB2__INCLUDED_)
