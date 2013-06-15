#if !defined(AFX_DIALOGDARKERSCREEN_H__761F186F_C93E_493E_AF07_60076F6AD865__INCLUDED_)
#define AFX_DIALOGDARKERSCREEN_H__761F186F_C93E_493E_AF07_60076F6AD865__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogDarkerScreen.h : header file
//
typedef enum {
    ANIMATE_OFF = 0,
    ANIMATE_FAST,
    ANIMATE_MEDIUM,
    ANIMATE_SLOW,
} EAnimateType;


/////////////////////////////////////////////////////////////////////////////
// CDialogDarkerScreen dialog

class CDialogDarkerScreen : public CDialog
{
public:
    PFNTransparentWindow    m_pfnTransparentWindow;
    EAnimateType m_eAnimateType;
    COLORREF m_color;
    CRect m_rectScreen;
    float m_flAlphaStep;
    int m_iAlphaStepCount;
    int m_iAlphaCurrent;
    int m_iAlpha;
    void SetWindowTransparent(BYTE byAlpha);
    void CalcWindowPos(void);
    void DisplayChange(void);
    void InitDarkerScreen(void);
    void ShowDarkerScreen(int iAlpha, COLORREF color,
                          EAnimateType eAnimateType);
    void DeleteDarkerScreen();
// Construction
public:
    CDialogDarkerScreen(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
    //{{AFX_DATA(CDialogDarkerScreen)
    enum { IDD = IDD_DIALOG_DARKER_SCREEN };
        // NOTE: the ClassWizard will add data members here
    //}}AFX_DATA


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CDialogDarkerScreen)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(CDialogDarkerScreen)
    virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGDARKERSCREEN_H__761F186F_C93E_493E_AF07_60076F6AD865__INCLUDED_)
