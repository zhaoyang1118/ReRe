#if !defined(AFX_DIALOGABOUTSTATISTICS_H__78970513_3963_4348_8BF3_3F15100C146C__INCLUDED_)
#define AFX_DIALOGABOUTSTATISTICS_H__78970513_3963_4348_8BF3_3F15100C146C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogAboutStatistics.h : header file
//


// 统计量显示序号
typedef enum _StatisticDisplayIndex{
    TIME_HEADLINE = 0,        // 第0行 Time行的标题
    TIME_TOTAL,
    TIME_WORK,
    TIME_SRELAX,
    TIME_LRELAX,
    TIME_PAUSE,
    TIME_RESET,
    TIME_ENDLINE,            // 第7行 Time结束空行
    RELAX_HEADLINE = 8,        // 第8行 Relax行的标题
    RELAX_SRELAX,
    RELAX_LRELAX,
    RELAX_DELAYED,
    RELAX_SKIPPED,
    RELAX_ENDLINE            // 第12行 Relax结束空行(不显示)
} StatisticDisplayIndex;


/////////////////////////////////////////////////////////////////////////////
// CDialogAboutStatistics dialog

class CDialogAboutStatistics : public CDialog
{
public:    
    CRelaxReminderDlg        *m_pdlgMain;
    void    InitStatistic();
    void    UpdateTimeStatistic();
    void    UpdateRelaxStatistic();
    void    LoadLanguageStrings();
private:
    BOOL    InsertHeadline(UINT nIndex, char* pchHeadline);
    BOOL    InsertEndline(UINT nIndex);
    BOOL    InsertItem(UINT nIndex, char* pchItem, UINT nValue = 0, float fRatio = 0.0);
    BOOL    UpdateItem(UINT nIndex, UINT nValue, float fRatio);
// Construction
public:
    CDialogAboutStatistics(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
    //{{AFX_DATA(CDialogAboutStatistics)
    enum { IDD = IDD_DIALOG_ABOUT_STATISTICS };
    CListCtrl    m_listStatistic;
    //}}AFX_DATA


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CDialogAboutStatistics)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(CDialogAboutStatistics)
    virtual BOOL OnInitDialog();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGABOUTSTATISTICS_H__78970513_3963_4348_8BF3_3F15100C146C__INCLUDED_)
