#if !defined(AFX_DIALOGOPTIONNOTIFY_H__892F99CC_BA45_4203_AFA6_5E1B9F4AF1FE__INCLUDED_)
#define AFX_DIALOGOPTIONNOTIFY_H__892F99CC_BA45_4203_AFA6_5E1B9F4AF1FE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogOptionNotify.h : header file
//


// 锁定输入的类型定义
typedef enum {
    RELAX_LOCK_KEYBOARD = 0,
    RELAX_LOCK_MOUSE,
    RELAX_LOCK_BOTH,
} ELockType;


/////////////////////////////////////////////////////////////////////////////
// CDialogOptionNotify dialog

class CDialogOptionNotify : public CDialog
{
public:
    CRelaxReminderDlg       *m_pdlgMain;
    CDialogOption           *m_pdlgOption;
    int                     m_iAlpha;
    CRect                   m_rectColorView;
    COLORREF                m_color;
    BOOL                    LoadFromCurrentSetting();
    void                    LoadSettingFromDefault();
    void                    UpdateControlStatus();
    BOOL                    CheckSetting();
    BOOL                    ApplySetting();
    // 根据Option窗口的状态，设置Option窗口的按钮是否可用
    void                    UpdateButtonStatusBySettingChange();
    // 加载界面语言
    void                    LoadLanguageStrings();

    // Construction
public:
    CDialogOptionNotify(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
    //{{AFX_DATA(CDialogOptionNotify)
	enum { IDD = IDD_DIALOG_OPTION_NOTIFY };
    CSliderCtrl    m_sliderAlpha;
    BOOL    m_bPreNotify;
    BOOL    m_bLockInput;
    int     m_iLockType;
    BOOL    m_bDarkerScreen;
	int		m_iAnimateType;
	int		m_iColorType;
	int		m_iDarkerScreenType;
	int		m_iNotifyWindowType;
	//}}AFX_DATA


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CDialogOptionNotify)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(CDialogOptionNotify)
    virtual BOOL OnInitDialog();
    afx_msg void OnCheckPrenotify();
    afx_msg void OnCheckLockInput();
    afx_msg void OnRadioLockKeyboard();
    afx_msg void OnRadioLockMouse();
    afx_msg void OnRadioLockBoth();
    afx_msg void OnCheckDarkerScreen();
    afx_msg void OnCustomdrawSliderAlpha(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRadioAnimationOff();
	afx_msg void OnRadioAnimationFast();
	afx_msg void OnRadioAnimationMedium();
	afx_msg void OnRadioAnimationSlow();
	afx_msg void OnRadioColorBlack();
	afx_msg void OnRadioColorCustom();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRadioMultimonDarkerScreenMaster();
	afx_msg void OnRadioMultimonDarkerScreenCursor();
	afx_msg void OnRadioMultimonDarkerScreenAll();
	afx_msg void OnRadioMultimonNotifyWindowMaster();
	afx_msg void OnRadioMultimonNotifyWindowCursor();
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGOPTIONNOTIFY_H__892F99CC_BA45_4203_AFA6_5E1B9F4AF1FE__INCLUDED_)
