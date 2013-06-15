#if !defined(AFX_DIALOGTRAYWINDOW_H__E9D9414A_A92D_4CD8_A1AC_FC957AE840D7__INCLUDED_)
#define AFX_DIALOGTRAYWINDOW_H__E9D9414A_A92D_4CD8_A1AC_FC957AE840D7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogTrayWindow.h : header file
//


/////////////////////////////////////////////////////////////////////////////
// CDialogTrayWindow dialog
class CRelaxReminderDlg;

class CDialogTrayWindow : public CDialog
{
public:
    PFNTransparentWindow    m_pfnTransparentWindow;
    CRelaxReminderDlg       *m_pwndParent;
    CRect m_rectTrayWindow;
    CRect m_rectApproach;
    CRect m_rectMonitor;
    CFont m_fontTimeTips;
    UINT  m_nApproachAreaStay;
    int m_iAlpha;
    int m_iAlphaStep;
    void SetWindowTransparent(BYTE byAlpha);
    void MoveWindowToOtherSide(void);
    void MoveToBottomRight(void);
    void MoveToBottomLeft(void);
    void DisplayChange(void);
    void InitTrayWindow(CWnd *pwndParent);
    void ShowTrayWindow(char *szCaption, char *szTimetips);
    void UpdateTrayWindow(char *szCaption, char *szTimetips);
    void DeleteTrayWindow();
    void CursorDetect();
    // º”‘ÿΩÁ√Ê”Ô—‘
    void LoadLanguageStrings();
// Construction
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
    CDialogTrayWindow(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
    //{{AFX_DATA(CDialogTrayWindow)
    enum { IDD = IDD_DIALOG_TRAY_WINDOW };
    //}}AFX_DATA


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CDialogTrayWindow)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:
	CToolTipCtrl m_tooltip;

    // Generated message map functions
    //{{AFX_MSG(CDialogTrayWindow)
    virtual BOOL OnInitDialog();
    afx_msg void OnTimer(UINT nIDEvent);
    afx_msg void OnButtonDelay();
	afx_msg void OnButtonSkip();
	afx_msg void OnButtonHide();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGTRAYWINDOW_H__E9D9414A_A92D_4CD8_A1AC_FC957AE840D7__INCLUDED_)
