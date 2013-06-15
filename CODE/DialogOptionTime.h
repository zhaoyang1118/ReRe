#if !defined(AFX_DIALOGOPTIONTIME_H__8265AAFA_04E4_46F4_8910_39C080F54692__INCLUDED_)
#define AFX_DIALOGOPTIONTIME_H__8265AAFA_04E4_46F4_8910_39C080F54692__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogOptionTime.h : header file
//


/////////////////////////////////////////////////////////////////////////////
// CDialogOptionTime dialog

class CDialogOptionTime : public CDialog
{
public:
    CRelaxReminderDlg       *m_pdlgMain;
    CDialogOption           *m_pdlgOption;
    CButtonST               m_btnNext;
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
    CDialogOptionTime(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
    //{{AFX_DATA(CDialogOptionTime)
    enum { IDD = IDD_DIALOG_OPTION_TIME };
    BOOL    m_bEnableLongRelax;
    CString    m_strLongRelaxDuration;
    CString    m_strLongRelaxFrequency;
    CString    m_strShortRelaxDuration;
    CString    m_strWorkDuration;
    //}}AFX_DATA


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CDialogOptionTime)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(CDialogOptionTime)
    virtual BOOL OnInitDialog();
    afx_msg void OnCheckEnableLongRelax();
    afx_msg void OnEditupdateComboWorkDuration();
    afx_msg void OnSelchangeComboWorkDuration();
    afx_msg void OnEditchangeComboShortRelaxDuration();
    afx_msg void OnSelchangeComboShortRelaxDuration();
    afx_msg void OnEditchangeComboLongRelaxFrequency();
    afx_msg void OnSelchangeComboLongRelaxFrequency();
    afx_msg void OnEditchangeComboLongRelaxDuration();
    afx_msg void OnSelchangeComboLongRelaxDuration();
	afx_msg void OnButtonNext();
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGOPTIONTIME_H__8265AAFA_04E4_46F4_8910_39C080F54692__INCLUDED_)
