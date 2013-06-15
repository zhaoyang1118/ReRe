#if !defined(AFX_DIALOGABOUTCHANGELOG_H__5A440B54_108F_41A6_B53E_6CA6AAB61B0E__INCLUDED_)
#define AFX_DIALOGABOUTCHANGELOG_H__5A440B54_108F_41A6_B53E_6CA6AAB61B0E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogAboutChangelog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogAboutChangelog dialog

class CDialogAboutChangelog : public CDialog
{
public:
    CRelaxReminderDlg       *m_pdlgMain;
    // º”‘ÿΩÁ√Ê”Ô—‘
    void    LoadLanguageStrings();
private:
    CCreditsCtrl    m_wndChangelog;

// Construction
public:
	CDialogAboutChangelog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogAboutChangelog)
	enum { IDD = IDD_DIALOG_ABOUT_CHANGELOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogAboutChangelog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogAboutChangelog)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGABOUTCHANGELOG_H__5A440B54_108F_41A6_B53E_6CA6AAB61B0E__INCLUDED_)
