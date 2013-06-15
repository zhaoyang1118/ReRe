#if !defined(AFX_DIALOGABOUTDONATE_H__B232B1D7_BAB5_46DE_9136_DAE6172D0543__INCLUDED_)
#define AFX_DIALOGABOUTDONATE_H__B232B1D7_BAB5_46DE_9136_DAE6172D0543__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogAboutDonate.h : header file
//


/////////////////////////////////////////////////////////////////////////////
// CDialogAboutDonate dialog

class CDialogAboutDonate : public CDialog
{
public:
    CRelaxReminderDlg       *m_pdlgMain;
    CCreditsCtrl            m_wndDonators;
    CFont                   m_fontAppeal;
    CRect                   m_rectPaypal;
    CRect                   m_rectAlipay;
    // º”‘ÿΩÁ√Ê”Ô—‘
    void    LoadLanguageStrings();

// Construction
public:
	CDialogAboutDonate(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogAboutDonate)
	enum { IDD = IDD_DIALOG_ABOUT_DONATE };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogAboutDonate)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogAboutDonate)
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGABOUTDONATE_H__B232B1D7_BAB5_46DE_9136_DAE6172D0543__INCLUDED_)
