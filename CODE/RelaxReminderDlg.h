// RelaxReminderDlg.h : header file
//

#if !defined(AFX_RELAXREMINDERDLG_H__CB299B95_7483_4ABD_A430_8B4A953B75C0__INCLUDED_)
#define AFX_RELAXREMINDERDLG_H__CB299B95_7483_4ABD_A430_8B4A953B75C0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>


#define FONT_SIZE_ARRAY_NUM     (35)
#define MULTI_MONITOR_NUM       (10)


typedef enum {
    MASTER_MONITOR = 0,
    CURSOR_MONITOR,
    ALL_MONITOR,
} EMultiMonitorType;


/////////////////////////////////////////////////////////////////////////////
// CRelaxReminderDlg dialog

class CDialogDarkerScreen;
class CDialogTrayWindow;
class CDialogOption;
class CDialogAbout;

class CRelaxReminderDlg : public CDialog
{
public:
    // 界面尺寸
    CRect               m_rectFloatingWindow;
    // 时钟秒数
    int                 m_iCountDown;
    char                m_achTime[6];               // HH:MM or MM:SS
    char                m_achTwinklingTime[6];      // HH:MM or MM:SS
    // 时钟字体
    CFont               m_fontTime;
    int                 m_fs[FONT_SIZE_ARRAY_NUM];  // font size table
    // 托盘图标
    BOOL                m_bTrayIconVisible;
    UINT                m_uIconID;
    NOTIFYICONDATA      m_nd;
    // 全屏时隐藏悬浮窗口
    BOOL                m_bFloatingWindowHidebyFullscr;
    // 时钟核心
    RelaxTimer          m_tm;
    // 当前版本号
    UINT                m_dwVersion;
    // Option选项设置
    BOOL                m_bPreNotify;
    BOOL                m_bLockInput;
    int                 m_iLockType;
    int                 m_iGraceTimeBeforeLockInput;
    int                 m_bDarkerScreen;
    int                 m_iDarkerScreenAlpha;
    EAnimateType        m_eDarkerScreenAnimateType;
    COLORREF            m_colorDarkerScreen;
    EMultiMonitorType   m_eDarkerScreenType;
    EMultiMonitorType   m_eNotifyWindowType;
    BOOL                m_bLockComputer;
    BOOL                m_bCloseMonitor;
    BOOL                m_bShowFloatingWindowAtStartup;
    BOOL                m_bShowTrayIconAtStartup;
    BOOL                m_bAutoStartWithSystem;
    // 语言设置
    CString             m_strLanguageId;
    // 字符串表
    CStringTable        m_str;
    // INI文件读写互斥
    CRITICAL_SECTION    m_csSettingFile;
    CRITICAL_SECTION    m_csStatisticFile;
    // 提示窗口
    CDialogDarkerScreen m_adlgDarkerScreen[MULTI_MONITOR_NUM];
    int                 m_iMonitorCount;
    int                 m_iUsedDarkerScreen;
    CDialogTrayWindow   m_dlgRelaxNotify;
    // 子窗口指针
    CDialogOption           *m_pdlgOption;
    CDialogAbout            *m_pdlgAbout;
    // 程序主目录和文件
    CString             m_strHomeDirectory;
    CString             m_strLogDirectory;

    CString             m_strAppFile;
    CString             m_strConfigFile;
    CString             m_strStatisticFile;
    CString             m_strLanguageFile;

    // 窗口透明函数指针
    PFNTransparentWindow    m_pfnTransparentWindow;

    // 初始化设置
    void            InitProcess();
    void            GetDirectoriesAndFiles();
    void            InitNotifyWindow();
    // 参数加载函数
    void            InitLoadSetting();
    void            ReadCurrentVersionFromExeFile();
    void            LoadSettingFromDefault();
    BOOL            LoadSettingFromIniFile();
    void            SaveSettingToIniFile();
    void            CreateIniFileHeader(const char* pchFile);
    void            RunSetupWizard(void);
    // 统计变量处理函数
    void            ProcessStatistics();
    void            LoadStatisticsFromDefault();
    BOOL            LoadStatisticsFromIniFile();
    void            SaveStatisticsToIniFile();
    void            AutoSaveStatistics();
    // 设置窗口透明度函数
    void            SetWindowTransparent(BYTE byAlpha);
    // 更新所有状态(悬浮窗口/通知栏图标/统计信息)
    void            UpdateAll();
    // 获取时间字符串
    void            ProcessCountDownTimer();
    void            MakeTimeString();
    char*           GetFixedColonTime();
    char*           GetTwinklingTime();
    // 初始化显示悬浮窗口和通知栏图标
    void            InitShowFloatingWindow(void);
    void            InitFloatingWindowPos(void);
    void            InitFloatingWindowFontSize();
    void            InitShowTrayIcon(void);
    // 悬浮窗口状态处理函数
    void            ProcessFloatingWindow();
    void            MakeFloatingWindowMovable();
    void            MakeFloatingWindowFixed();
    void            MakeFloatingWindowInvisible();
    void            FloatingWindowMouseHoverDetect();
    void            FloatingWindowInitStatus();
    void            FloatingWindowWorkStatus();
    void            FloatingWindowShortRelaxStatus();
    void            FloatingWindowLongRelaxStatus();
    void            FloatingWindowPauseStatus();
    void            FloatingWindowResetStatus();
    void            FloatingWindowAutoPauseStatus();
    void            FloatingWindowAutoResetStatus();
    // 休息前提示/休息时锁定的处理函数
    void            ProcessRelaxNotify();
    void            PreRelaxNotify();
    void            RelaxNotify();
    void            RelaxNotifyEnd();
    // 托盘图标处理函数
    void            ProcessIconStatus();
    void            ShowTrayIcon();
    void            UpdateTrayIcon(const char* szTip);
    void            DeleteTrayIcon();
    LONG            OnNotifyIcon(WPARAM wParam, LPARAM lParam);
    void            ShowRightClickMenu();
    void            LoadMenuLanguageString(CMenu *pMenu);
    // 分辨率改变的处理函数
    void            OnDisplayChange(WPARAM wParam, LPARAM lParam);
    // 休息提示窗口的处理函数
    void            CalcNotifyWindowPos();
    void            GetAllMonitorInfo();
    void            PutDarkerScreenUnderTrayWindow();
    void            ShowDarkerScreen(int iAlpha, COLORREF color, EAnimateType eAnimateType);
    void            HideDarkerScreen();
    // 退出处理函数
    void            QuitProcess(void);

// Construction
public:
    CRelaxReminderDlg(CWnd* pParent = NULL);    // standard constructor

// Dialog Data
    //{{AFX_DATA(CRelaxReminderDlg)
    enum { IDD = IDD_RELAXREMINDER_DIALOG };
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CRelaxReminderDlg)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:
    HICON m_hIcon;

    // Generated message map functions
    //{{AFX_MSG(CRelaxReminderDlg)
    virtual BOOL OnInitDialog();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    afx_msg void OnTimer(UINT nIDEvent);
    afx_msg void OnMenuMainWindow();
    afx_msg void OnMenuTrayIcon();
    afx_msg void OnMenuStartWork();
    afx_msg void OnMenuShortRelax();
    afx_msg void OnMenuLongRelax();
    afx_msg void OnMenuPause();
    afx_msg void OnMenuReset();
    afx_msg void OnMenuOption();
    afx_msg void OnMenuPluginsManager();
    afx_msg void OnMenuAbout();
    afx_msg void OnMenuExit();
    afx_msg void OnDestroy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnNcLButtonUp(UINT nHitTest, CPoint point);
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RELAXREMINDERDLG_H__CB299B95_7483_4ABD_A430_8B4A953B75C0__INCLUDED_)
