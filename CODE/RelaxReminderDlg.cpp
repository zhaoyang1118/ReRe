// RelaxReminderDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RelaxReminder.h"
#include "DefaultValue.h"
#include "Global.h"
#include "PubFunc.h"
#include "LibFunc.h"
#include "BtnST.h"
#include "CreditsCtrl.h"
#include "Log.h"
#include "Ini.h"
#include "Version.h"
#include "StringTable.h"
#include "RelaxTimer.h"
#include "DialogTrayWindow.h"
#include "DialogDarkerScreen.h"
#include "RelaxReminderDlg.h"
#include "DialogOptionTime.h"
#include "DialogOptionNotify.h"
#include "DialogOptionAutoAway.h"
#include "DialogOptionLanguage.h"
#include "DialogOptionMisc.h"
#include "DialogOption.h"
#include "DialogSetupWizardWelcome.h"
#include "DialogSetupWizard.h"
#include "KeyboardMouseHook/KeyboardMouseHook.h"
#include "DialogAboutAbout.h"
#include "DialogAboutThanks.h"
#include "DialogAboutChangelog.h"
#include "DialogAboutStatistics.h"
#include "DialogAboutDonate.h"
#include "DialogAbout.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// 托盘图标的消息定义
#define WM_NOTIFYICON       WM_USER + 5

// 路径名定义
#define LOG_DIRECTORY_NAME      "log"
// 文件名定义
#define CONFIG_FILE_NAME        "ReRe.ini"
#define STATISTIC_FILE_NAME     "Statistic.ini"
#define LANGUAGE_FILE_NAME      "Language.ini"

// 版本信息宏定义
#define VERSION_0_7_4    0x00070400
#define VERSION_0_7_5    0x00070500
#define VERSION_0_7_6    0x00070600
#define VERSION_0_7_7    0x00070700
#define VERSION_0_7_8    0x00070800
#define VERSION_0_7_9    0x00070900
#define VERSION_0_7_10   0x00070a00
#define VERSION_0_7_11   0x00070b00
#define VERSION_0_7_12   0x00070c00
#define VERSION_0_7_13   0x00070d00
#define VERSION_0_7_14   0x00070e00
#define VERSION_0_8      0x00080000
#define VERSION_0_8_1    0x00080100
#define VERSION_0_8_2    0x00080200
#define VERSION_0_8_3    0x00080300
#define VERSION_0_8_4    0x00080400

// 休息预提示窗口的显示时间
#define PRE_NOTIFY_WINDOW_TTL               11

// TrayWindow比ScrMask延迟显示的时间(单位：秒)
#define TRAY_WINDOW_DELAY                   1

// 悬浮窗口透明度
#define FLOATING_WINDOW_TRANSPARENCY        120
#define POSITION_ADJUST_TRANSPARENCY        255

#define LoadMenuString(COMMANDID, STRIDX)                           \
{                                                                   \
    pMenu->ModifyMenu(COMMANDID, MF_BYCOMMAND|MF_STRING,            \
        COMMANDID, m_str.GetStr(STRIDX));                           \
}


/////////////////////////////////////////////////////////////////////////////
// CRelaxReminderDlg dialog

CRelaxReminderDlg::CRelaxReminderDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CRelaxReminderDlg::IDD, pParent)
{
    //{{AFX_DATA_INIT(CRelaxReminderDlg)
    //}}AFX_DATA_INIT
    // Note that LoadIcon does not require a subsequent DestroyIcon in Win32
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRelaxReminderDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CRelaxReminderDlg)
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CRelaxReminderDlg, CDialog)
    //{{AFX_MSG_MAP(CRelaxReminderDlg)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_WM_TIMER()
    ON_COMMAND(ID_MENU_MAIN_WINDOW, OnMenuMainWindow)
    ON_COMMAND(ID_MENU_START_WORK, OnMenuStartWork)
    ON_COMMAND(ID_MENU_SHORT_RELAX, OnMenuShortRelax)
    ON_COMMAND(ID_MENU_LONG_RELAX, OnMenuLongRelax)
    ON_COMMAND(ID_MENU_PAUSE, OnMenuPause)
    ON_COMMAND(ID_MENU_RESET, OnMenuReset)
    ON_COMMAND(ID_MENU_OPTION, OnMenuOption)
    ON_COMMAND(ID_MENU_ABOUT, OnMenuAbout)
    ON_COMMAND(ID_MENU_EXIT, OnMenuExit)
    ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONUP()
    ON_WM_NCLBUTTONUP()
	ON_WM_CTLCOLOR()
    ON_MESSAGE(WM_DISPLAYCHANGE, OnDisplayChange)
	ON_COMMAND(ID_MENU_TRAY_ICON, OnMenuTrayIcon)
	//}}AFX_MSG_MAP
    ON_MESSAGE(WM_NOTIFYICON, OnNotifyIcon)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRelaxReminderDlg message handlers

BOOL CRelaxReminderDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // Add "About..." menu item to system menu.

    // IDM_ABOUTBOX must be in the system command range.
    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);

    CMenu* pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != NULL)
    {
        CString strAboutMenu;
        strAboutMenu.LoadString(IDS_ABOUTBOX);
        if (!strAboutMenu.IsEmpty())
        {
            pSysMenu->AppendMenu(MF_SEPARATOR);
            pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
        }
    }

    // Set the icon for this dialog.  The framework does this automatically
    //  when the application's main window is not a dialog
    SetIcon(m_hIcon, TRUE);            // Set big icon
    SetIcon(m_hIcon, FALSE);        // Set small icon
    
    // TODO: Add extra initialization here
    // 只允许运行一个程序实例
    SetProp(m_hWnd, g_szPropName, g_hValue);

    // 初始化成员变量、临界区保护资源、打印模块
    InitProcess();

    // 初始化设置参数
    InitLoadSetting();

    // 初始化提示窗口(必须在加载完参数后执行，由于需要加载窗口语言)
    InitNotifyWindow();

    // 初始化显示
    InitShowFloatingWindow();
    InitShowTrayIcon();

    // 开启1s定时器
    SetTimer(TIMER_HEART_BEAT_1S, 1000, NULL);

    // 自动开始计时
    OnMenuStartWork();
    
    return TRUE;  // return TRUE  unless you set the focus to a control
}

void CRelaxReminderDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
    if ((nID & 0xFFF0) == IDM_ABOUTBOX)
    {
        CDialogAbout dlg;
        dlg.m_pdlgMain = this;
        m_pdlgAbout = &dlg;
        dlg.DoModal();
        m_pdlgAbout = NULL;
    }
    else
    {
        CDialog::OnSysCommand(nID, lParam);

        // 移动结束时发送WM_NCLBUTTONUP消息
        if((nID & 0xFFF0) == SC_MOVE)
        {
            PostMessage(WM_NCLBUTTONUP, nID, lParam);
        }
    }
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CRelaxReminderDlg::OnPaint() 
{
    if (IsIconic())
    {
        CPaintDC dc(this); // device context for painting

        SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

        // Center icon in client rectangle
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // Draw the icon
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialog::OnPaint();
    }
}

HBRUSH CRelaxReminderDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
    HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
    
    // TODO: Change any attributes of the DC here
    switch (pWnd->GetDlgCtrlID())
    {
    case IDC_STATIC_TIMETIPS:
        switch (m_tm.GetStatus())
        {
        case STATUS_WORK:
            pDC->SetTextColor(RGB(255, 0, 0));
            break;
        case STATUS_SHORT_RELAX:
        case STATUS_LONG_RELAX:
            pDC->SetTextColor(RGB(0, 255, 0));
            break;
        default:
            pDC->SetTextColor(RGB(128, 128, 128));
            break;
        }
        break;
    }
    
    // TODO: Return a different brush if the default is not desired
    return hbr;
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CRelaxReminderDlg::OnQueryDragIcon()
{
    return (HCURSOR) m_hIcon;
}

void CRelaxReminderDlg::OnTimer(UINT nIDEvent) 
{
    // TODO: Add your message handler code here and/or call default
    switch (nIDEvent)
    {
    case TIMER_HEART_BEAT_1S:
        m_tm.HeartBeat1Second();
        UpdateAll();
        AutoSaveStatistics();
    	break;
    case TIMER_MOUSE_HOVER_DETECT:
        FloatingWindowMouseHoverDetect();
        break;
    default:
        break;
    }

    CDialog::OnTimer(nIDEvent);
}

// 初始化设置
void CRelaxReminderDlg::InitProcess()
{
    m_pdlgOption            = NULL;
    m_pdlgAbout             = NULL;
    m_pfnTransparentWindow  = GetSysLibraryTransparentWindow();

    // 初始化语言字符串表
    m_str.LoadDefaultString();

    // 初始化临界区保护资源
    InitializeCriticalSection(&m_csSettingFile);
    InitializeCriticalSection(&m_csStatisticFile);

    // 初始化打印模块
    LogInit();
    AppLog2Buf(L_MSG, "--------------<starting>--------------");
    
    // 获取程序主目录
    GetDirectoriesAndFiles();
}

void CRelaxReminderDlg::GetDirectoriesAndFiles()
{
    int nPos;
    GetModuleFileName(NULL, m_strAppFile.GetBufferSetLength(MAX_PATH+1) , MAX_PATH);
    nPos = m_strAppFile.ReverseFind('\\');
    m_strHomeDirectory = m_strAppFile.Left(nPos);
    AppLog2Buf(L_MSG, "home directory is %s.", m_strHomeDirectory);

    m_strLogDirectory       = m_strHomeDirectory + '\\' + LOG_DIRECTORY_NAME;

    m_strConfigFile     = m_strHomeDirectory + '\\' + CONFIG_FILE_NAME;
    m_strStatisticFile  = m_strHomeDirectory + '\\' + STATISTIC_FILE_NAME;
    m_strLanguageFile   = m_strHomeDirectory + '\\' + LANGUAGE_FILE_NAME;
}

// 初始化提示窗口
void CRelaxReminderDlg::InitNotifyWindow()
{
    m_dlgRelaxNotify.InitTrayWindow(this);
    for (int i = 0; i < MULTI_MONITOR_NUM; i++)
    {
        m_adlgDarkerScreen[i].InitDarkerScreen();
    }
    CalcNotifyWindowPos();
}

// 参数加载函数
void CRelaxReminderDlg::InitLoadSetting()
{
    // 先获取当前的exe文件版本信息，后面读取INI文件时会用到此信息
    ReadCurrentVersionFromExeFile();

    // 加载当前版本的默认参数，如果有配置文件，后续从配置文件中加载参数
    LoadSettingFromDefault();
    if(FileExists(m_strConfigFile))
    {// 有INI文件存在，则尝试从INI文件加载参数
        if (FALSE == LoadSettingFromIniFile())
        {// 如果返回失败，则表示INI文件中记录的版本号与主程序版本号不一致
            SaveSettingToIniFile();
        }
    }
    else
    {// INI文件不存在，直接使用默认参数生成新的Ini文件
        AppLog2Buf(L_WARN,
            "config file[%s] does NOT exist, open setup wizard.",
            m_strConfigFile);
        RunSetupWizard();
        SaveSettingToIniFile();
    }

    // 加载默认统计数据(全0)，如果有统计文件，后续从统计文件中加载统计数据
    LoadStatisticsFromDefault();
    if(FileExists(m_strStatisticFile))
    {// 有INI文件存在，则尝试从INI文件加载统计数据
        LoadStatisticsFromIniFile();
    }
    else
    {// INI文件不存在，直接使用全0的统计数据生成新的Ini文件
        AppLog2Buf(L_WARN, "statistic file[%s] does NOT exist.", m_strStatisticFile);
        SaveStatisticsToIniFile();
    }
    
    // 加载指定语言
    if (m_strLanguageId.IsEmpty())
    {// 判断语言在配置中是否指定
        AppLog2Buf(L_WARN, "language not specified, use default language.");
    }
    else
    {
        if(FALSE == m_str.LoadStringTable(m_strLanguageFile, m_strLanguageId))
        {// 如果加载失败，则加载默认语言(英文)
            AppLog2Buf(L_WARN, "load language[%s] fail, use default language.",
                       m_strLanguageId);
        }
    }

    // 根据打印设置，将缓存区中的打印更新到log文件中
    if (TRUE == GetEnableLog())
    {
        LogBufFlush();
    }
}

void CRelaxReminderDlg::ReadCurrentVersionFromExeFile()
{
    // 加载当前版本号  XX.YY.ZZ => 0xXXYYZZ00
    CString strVersion = GetFileVersion(m_strAppFile);
    m_dwVersion = VersionString2Num(strVersion);
    AppLog2Buf(L_MSG, "current main app version is %s.", strVersion);
}

void CRelaxReminderDlg::LoadSettingFromDefault()
{
    // 设置时间参数
    m_tm.SetWD(DEFAULT_WORK_DURATION);
    m_tm.SetSRD(DEFAULT_SHORT_RELAX_DURATION);
    m_tm.SetEnableLongRelax(DEFAULT_ENABLE_LONG_RELAX);
    m_tm.SetLRF(DEFAULT_LONG_RELAX_FREQUENCY);
    m_tm.SetLRD(DEFAULT_LONG_RELAX_DURATION);

    // 设置提示参数
    m_bPreNotify = DEFAULT_ENABLE_PRENOTIFY;
    m_bLockInput = DEFAULT_ENABLE_LOCK_INPUT;
    m_iLockType  = DEFAULT_LOCK_TYPE;
    m_iGraceTimeBeforeLockInput = DEFAULT_GRACE_TIME_BEFORE_LOCK_INPUT;
    m_bDarkerScreen         = DEFAULT_ENABLE_DARKER_SCREEN;
    m_iDarkerScreenAlpha    = DEFAULT_DARKER_SCREEN_ALPHA;
    m_eDarkerScreenAnimateType  = DEFAULT_DARKER_SCREEN_ANIMATE;
    m_colorDarkerScreen     = DEFAULT_DARKER_SCREEN_COLOR;
    m_eNotifyWindowType     = DEFAULT_NOTIFY_WINDOW_TYPE;
    m_eDarkerScreenType     = DEFAULT_DARKER_SCREEN_TYPE;

    // 设置自动状态转换参数
    m_tm.SetEnableAutoPause(DEFAULT_ENABLE_AUTO_PAUSE);
    m_tm.SetAPT(DEFAULT_AUTO_PAUSE_THRESHOLD);
    m_tm.SetEnableFullScreenPause(DEFAULT_ENABLE_FULLSCREEN_PAUSE);
    m_tm.SetEnableAutoReset(DEFAULT_ENABLE_AUTO_RESET);
    m_tm.SetART(DEFAULT_AUTO_RESET_THRESHOLD);

    // 设置语言参数
    m_strLanguageId = DEFAULT_LANGUAGE;

    // 设置杂项参数
    m_bLockComputer = DEFAULT_ENABLE_LOCK_COMPUTER;
    m_bCloseMonitor = DEFAULT_ENABLE_CLOSE_MONITOR;
    m_bShowFloatingWindowAtStartup  = DEFAULT_SHOW_FLOATING_WINDOW;
    m_bShowTrayIconAtStartup        = DEFAULT_SHOW_TRAY_ICON;
    SetEnableLog(DEFAULT_ENABLE_LOG);
    SetLogLevel(DEFAULT_LOG_LEVEL);
    SetLogFileSize(DEFAULT_LOG_FILE_SIZE);
    SetAppAutoStartWithSystem(DEFAULT_AUTO_START, m_strAppFile);
}

BOOL CRelaxReminderDlg::LoadSettingFromIniFile()
{
    // 进入临界区保护
    EnterCriticalSection(&m_csSettingFile); 

    // 打开配置文件
    CIni Ini(m_strConfigFile);

    // 先判断版本信息是否存在。若不存在，直接返回FALSE，加载默认参数。
    BOOL bVersionExist = Ini.CheckExist("Version", "CurrentVersion");
    if (bVersionExist == FALSE)
    {
        AppLog2Buf(L_WARN, "config file[%s] does NOT have version info.", m_strConfigFile);
        LeaveCriticalSection(&m_csSettingFile);
        return FALSE;
    }

    // 读取版本信息
    CString strIniFileVersion = Ini.ReadText("Version", "CurrentVersion");
    UINT dwIniFileVersion = VersionString2Num(strIniFileVersion);

    if (dwIniFileVersion == m_dwVersion)
    {
        AppLog2Buf(L_MSG, "config file version is %s, compatible with main app.",
                   strIniFileVersion);
    }
    else
    {
        AppLog2Buf(L_WARN, "config file version is %s, file converting.",
                   strIniFileVersion);
    }

    switch (dwIniFileVersion)
    {
    case VERSION_0_8_4:
        m_eDarkerScreenType = (EMultiMonitorType)Ini.ReadInt("Notify", "DarkerScreenType");
        m_eNotifyWindowType = (EMultiMonitorType)Ini.ReadInt("Notify", "NotifyWindowType");
        m_iGraceTimeBeforeLockInput = Ini.ReadInt("Notify", "GraceTimeBeforeLockInput");
    case VERSION_0_8_3:
    case VERSION_0_8_2:
    case VERSION_0_8_1:
    case VERSION_0_8:
    case VERSION_0_7_14:
        m_strLanguageId = Ini.ReadText("Language", "LanguageId");
    case VERSION_0_7_13:
        m_bShowFloatingWindowAtStartup = Ini.ReadInt("Misc", "ShowFloatingWindow");
        m_bShowTrayIconAtStartup = Ini.ReadInt("Misc", "ShowTrayIcon");
    case VERSION_0_7_12:
        m_tm.SetEnableFullScreenPause(Ini.ReadInt("AutoAway", "FullscreenPause"));
    case VERSION_0_7_11:
    case VERSION_0_7_10:
        m_eDarkerScreenAnimateType = (EAnimateType)Ini.ReadInt("Notify", "DarkerScreenAnimate");
        m_colorDarkerScreen = Ini.ReadInt("Notify", "DarkerScreenColor");
    case VERSION_0_7_9:
    case VERSION_0_7_8:
    case VERSION_0_7_7:
        SetEnableLog(Ini.ReadInt("Misc", "EnableLog"));
        SetLogLevel((ELogLevel)Ini.ReadInt("Misc", "LogLevel"));
        SetLogFileSize((ELogFileSize)Ini.ReadInt("Misc", "LogFileSize"));
        SetAppAutoStartWithSystem(Ini.ReadInt("Misc", "AutoStartWithSystem"),
                                  m_strAppFile);
    case VERSION_0_7_6:
    case VERSION_0_7_5:
    case VERSION_0_7_4:
        // 设置时间参数
        m_tm.SetWD(Ini.ReadInt("Time", "WorkDuration"));
        m_tm.SetSRD(Ini.ReadInt("Time", "ShortRelaxDuration"));
        m_tm.SetEnableLongRelax(Ini.ReadInt("Time", "EnableLongRelax"));
        m_tm.SetLRF(Ini.ReadInt("Time", "LongRelaxFrequency"));
        m_tm.SetLRD(Ini.ReadInt("Time", "LongRelaxDuration"));

        // 设置提示参数
        m_bPreNotify = Ini.ReadInt("Notify", "PreNotify");
        m_bLockInput = Ini.ReadInt("Notify", "LockInput");
        m_iLockType  = Ini.ReadInt("Notify", "LockType");
        m_bDarkerScreen         = Ini.ReadInt("Notify", "DarkerScreen");
        m_iDarkerScreenAlpha    = Ini.ReadInt("Notify", "DarkerScreenAlpha");
    
        // 设置自动状态转换参数
        m_tm.SetEnableAutoPause(Ini.ReadInt("AutoAway", "EnableAutoPause"));
        m_tm.SetAPT(Ini.ReadInt("AutoAway", "AutoPauseThreshold"));
        m_tm.SetEnableAutoReset(Ini.ReadInt("AutoAway", "EnableAutoReset"));
        m_tm.SetART(Ini.ReadInt("AutoAway", "AutoResetThreshold"));

        // 设置杂项参数
        m_bLockComputer = Ini.ReadInt("Misc", "LockComputer");
        m_bCloseMonitor = Ini.ReadInt("Misc", "CloseMonitor");
        break;
    default:
        AppLog2Buf(L_WARN, "invalid config file version[%s].", strIniFileVersion);
        break;
    }
    
    // 离开临界区保护
    LeaveCriticalSection(&m_csSettingFile); 

    return (dwIniFileVersion == m_dwVersion);
}

void CRelaxReminderDlg::SaveSettingToIniFile()
{
    // 进入临界区保护
    EnterCriticalSection(&m_csSettingFile); 

    CreateIniFileHeader(m_strConfigFile);

    CIni Ini(m_strConfigFile);
    
    // 先保存版本信息
    Ini.Write("Version", "CurrentVersion", VersionNum2String(m_dwVersion));

    // 保存时间参数
    Ini.Write("Time", "WorkDuration",       m_tm.GetWD());
    Ini.Write("Time", "ShortRelaxDuration", m_tm.GetSRD());
    Ini.Write("Time", "EnableLongRelax",    m_tm.GetEnableLongRelax());
    Ini.Write("Time", "LongRelaxFrequency", m_tm.GetLRF());
    Ini.Write("Time", "LongRelaxDuration",  m_tm.GetLRD());
    
    // 保存提示参数
    Ini.Write("Notify", "PreNotify",            m_bPreNotify);
    Ini.Write("Notify", "LockInput",            m_bLockInput);
    Ini.Write("Notify", "LockType",             m_iLockType);
    Ini.Write("Notify", "GraceTimeBeforeLockInput", m_iGraceTimeBeforeLockInput);
    Ini.Write("Notify", "DarkerScreen",         m_bDarkerScreen);
    Ini.Write("Notify", "DarkerScreenAlpha",    m_iDarkerScreenAlpha);
    Ini.Write("Notify", "DarkerScreenAnimate",  m_eDarkerScreenAnimateType);
    Ini.Write("Notify", "DarkerScreenColor",    m_colorDarkerScreen);
    Ini.Write("Notify", "DarkerScreenType",     m_eDarkerScreenType);
    Ini.Write("Notify", "NotifyWindowType",     m_eNotifyWindowType);

    // 保存自动状态转换参数
    Ini.Write("AutoAway", "EnableAutoPause",    m_tm.GetEnableAutoPause());
    Ini.Write("AutoAway", "AutoPauseThreshold", m_tm.GetAPT());
    Ini.Write("AutoAway", "FullscreenPause",    m_tm.GetEnableFullScreenPause());
    Ini.Write("AutoAway", "EnableAutoReset",    m_tm.GetEnableAutoReset());
    Ini.Write("AutoAway", "AutoResetThreshold", m_tm.GetART());

    // 保存语言参数
    Ini.Write("Language", "LanguageId",         m_strLanguageId);

    // 保存杂项参数
    Ini.Write("Misc", "LockComputer",           m_bLockComputer);
    Ini.Write("Misc", "CloseMonitor",           m_bCloseMonitor);
    Ini.Write("Misc", "ShowFloatingWindow",     m_bShowFloatingWindowAtStartup);
    Ini.Write("Misc", "ShowTrayIcon",           m_bShowTrayIconAtStartup);
    Ini.Write("Misc", "EnableLog",              GetEnableLog());
    Ini.Write("Misc", "LogLevel",               GetLogLevel());
    Ini.Write("Misc", "LogFileSize",            GetLogFileSize());
    Ini.Write("Misc", "AutoStartWithSystem",    GetAppAutoStartWithSystem());

    // 离开临界区保护
    LeaveCriticalSection(&m_csSettingFile); 
}

void CRelaxReminderDlg::CreateIniFileHeader(const char* pchFile)
{
    // 创建INI文件，并写入文件头
    FILE *fp = NULL;

    if (fp = fopen(pchFile, "wt"))
    {
        fprintf(fp, "#####################################################\n");
        fprintf(fp, "## IMPORTANT!!                                     ##\n");
        fprintf(fp, "##   This is \"ReRe\" setting file.                  ##\n");
        fprintf(fp, "##   Do NOT edit this file manually, please.       ##\n");
        fprintf(fp, "##   Any inconsistency may lead to crashing!       ##\n");
        fprintf(fp, "#####################################################\n");
        fclose(fp);
    }
}

void CRelaxReminderDlg::RunSetupWizard(void)
{
    CDialogSetupWizard dlg;

    dlg.m_pdlgMain = this;
    dlg.DoModal();
}

void CRelaxReminderDlg::ProcessStatistics()
{
    // 如果About窗口正在显示，则更新时间和休息的统计数据
    if (m_pdlgAbout)
    {
        CDialogAbout *pdlgAbout = (CDialogAbout*)m_pdlgAbout;
        (pdlgAbout->m_dlgStatistics).UpdateTimeStatistic();
        (pdlgAbout->m_dlgStatistics).UpdateRelaxStatistic();
    }
}

void CRelaxReminderDlg::LoadStatisticsFromDefault()
{
    m_tm.StatSet_TotalSeconds(0);
    m_tm.StatSet_WorkSeconds(0);
    m_tm.StatSet_SRelaxSeconds(0);
    m_tm.StatSet_LRelaxSeconds(0);
    m_tm.StatSet_PauseSeconds(0);
    m_tm.StatSet_ResetSeconds(0);
    m_tm.StatSet_SRelaxTimes(0);
    m_tm.StatSet_LRelaxTimes(0);
    m_tm.StatSet_DelayedTimes(0);
    m_tm.StatSet_SkippedTimes(0);
}

BOOL CRelaxReminderDlg::LoadStatisticsFromIniFile()
{
    // 进入临界区保护
    EnterCriticalSection(&m_csStatisticFile); 

    CIni Ini(m_strStatisticFile);

    // 设置统计变量
    m_tm.StatSet_TotalSeconds(Ini.ReadInt("Time", "TotalSeconds"));
    m_tm.StatSet_WorkSeconds(Ini.ReadInt("Time", "WorkSeconds"));
    m_tm.StatSet_SRelaxSeconds(Ini.ReadInt("Time", "SRelaxSeconds"));
    m_tm.StatSet_LRelaxSeconds(Ini.ReadInt("Time", "LRelaxSeconds"));
    m_tm.StatSet_PauseSeconds(Ini.ReadInt("Time", "PauseSeconds"));
    m_tm.StatSet_ResetSeconds(Ini.ReadInt("Time", "ResetSeconds"));

    m_tm.StatSet_SRelaxTimes(Ini.ReadInt("Relax", "SRelaxTimes"));
    m_tm.StatSet_LRelaxTimes(Ini.ReadInt("Relax", "LRelaxTimes"));
    m_tm.StatSet_DelayedTimes(Ini.ReadInt("Relax", "DelayedTimes"));
    m_tm.StatSet_SkippedTimes(Ini.ReadInt("Relax", "SkippedTimes"));

    // 离开临界区保护
    LeaveCriticalSection(&m_csStatisticFile); 
    return TRUE;
}

void CRelaxReminderDlg::AutoSaveStatistics()
{
    // 每10分钟自动保存统计量到ini文件中
    CTime timeAutoSave = CTime::GetCurrentTime();
    if (timeAutoSave.GetMinute() % 10 == 0 && timeAutoSave.GetSecond() == 0)
    {
        SaveStatisticsToIniFile();
    }
}

void CRelaxReminderDlg::SaveStatisticsToIniFile()
{
    // 进入临界区保护
    EnterCriticalSection(&m_csStatisticFile); 

    CreateIniFileHeader(m_strStatisticFile);

    CIni Ini(m_strStatisticFile);
    
    Ini.Write("Time", "TotalSeconds",       m_tm.StatGet_TotalSeconds());
    Ini.Write("Time", "WorkSeconds",        m_tm.StatGet_WorkSeconds());
    Ini.Write("Time", "SRelaxSeconds",      m_tm.StatGet_SRelaxSeconds());
    Ini.Write("Time", "LRelaxSeconds",      m_tm.StatGet_LRelaxSeconds());
    Ini.Write("Time", "PauseSeconds",       m_tm.StatGet_PauseSeconds());
    Ini.Write("Time", "ResetSeconds",       m_tm.StatGet_ResetSeconds());

    Ini.Write("Relax", "SRelaxTimes",       m_tm.StatGet_SRelaxTimes());
    Ini.Write("Relax", "LRelaxTimes",       m_tm.StatGet_LRelaxTimes());
    Ini.Write("Relax", "DelayedTimes",      m_tm.StatGet_DelayedTimes());
    Ini.Write("Relax", "SkippedTimes",      m_tm.StatGet_SkippedTimes());

    // 离开临界区保护
    LeaveCriticalSection(&m_csStatisticFile); 
}

// 设置窗口透明度
void CRelaxReminderDlg::SetWindowTransparent(BYTE byAlpha)
{
    SetWindowLong(this->GetSafeHwnd(), GWL_EXSTYLE,
        GetWindowLong(this->GetSafeHwnd(), GWL_EXSTYLE)|0x80000);
    m_pfnTransparentWindow(this->GetSafeHwnd(), 0, byAlpha, 2);
}

void CRelaxReminderDlg::UpdateAll()
{
    ProcessCountDownTimer();
    ProcessFloatingWindow();
    ProcessRelaxNotify();
    ProcessIconStatus();
    ProcessStatistics();
}

void CRelaxReminderDlg::ProcessCountDownTimer()
{
    switch (m_tm.GetStatus())
    {
    case STATUS_INIT:
        m_iCountDown = 0; break;
    case STATUS_WORK:
        m_iCountDown = m_tm.GetWD() - m_tm.GetLS(); break;
    case STATUS_SHORT_RELAX:
        m_iCountDown = m_tm.GetSRD() - m_tm.GetLS(); break;
    case STATUS_LONG_RELAX:
        m_iCountDown = m_tm.GetLRD() - m_tm.GetLS(); break;
    case STATUS_PAUSE:
        m_iCountDown = m_tm.GetWD() - m_tm.GetLS(); break;
    case STATUS_RESET:
        m_iCountDown = 0; break;
    case STATUS_AUTO_PAUSE:
        m_iCountDown = m_tm.GetWD() - m_tm.GetLS(); break;
    case STATUS_AUTO_RESET:
        m_iCountDown = 0; break;
    default:
        break;
    }

    MakeTimeString();
}

void CRelaxReminderDlg::MakeTimeString()
{
    Seconds2Time(m_iCountDown, m_achTime, FIXED_COLON);
    Seconds2Time(m_iCountDown, m_achTwinklingTime, TWINKLING_COLON);
}

char* CRelaxReminderDlg::GetFixedColonTime()
{
    return m_achTime;
}

char* CRelaxReminderDlg::GetTwinklingTime()
{
    return m_achTwinklingTime;
}

void CRelaxReminderDlg::InitShowFloatingWindow()
{
    // 初始化窗口尺寸
    InitFloatingWindowPos();
    MoveWindow(m_rectFloatingWindow);
    
    // 初始化显示设置
    GetDlgItem(IDC_STATIC_TIMETIPS)->MoveWindow(0, 0,
        m_rectFloatingWindow.Width() - 1,
        m_rectFloatingWindow.Height());
    GetDlgItem(IDC_STATIC_TIMETIPS)->SetWindowText("00:00");
    
    // 初始化悬浮窗口字体大小
    InitFloatingWindowFontSize();
    
    // 初始化全屏时隐藏悬浮窗口变量
    m_bFloatingWindowHidebyFullscr = FALSE;
    
    // 不在任务栏显示
    ModifyStyleEx(WS_EX_APPWINDOW, WS_EX_TOOLWINDOW, SWP_DRAWFRAME);
    
    // 设置窗口置顶
    SetWindowPos(&wndTopMost,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE|SWP_NOACTIVATE);
    
    if (m_bShowFloatingWindowAtStartup)
    {
        MakeFloatingWindowFixed();
    }
}

// 计算悬浮窗口位置
void CRelaxReminderDlg::InitFloatingWindowPos(void)
{
    CRect   rectMonitor;
    int     iCaptionHeight;
    
    iCaptionHeight = min(max(15, GetSystemMetrics(SM_CYCAPTION)), FONT_SIZE_ARRAY_NUM - 1);
    SystemParametersInfo(SPI_GETWORKAREA, 0, &rectMonitor, 0);
    
    m_rectFloatingWindow.left = rectMonitor.right * 4 /5;
    m_rectFloatingWindow.top = 0;
    m_rectFloatingWindow.right = m_rectFloatingWindow.left + iCaptionHeight * 40 / 11;
    m_rectFloatingWindow.bottom = m_rectFloatingWindow.top + iCaptionHeight - 1;
}

void CRelaxReminderDlg::InitFloatingWindowFontSize()
{
    int iFloatingWindowHeight = m_rectFloatingWindow.Height();
    
    memset(m_fs, 0, sizeof(m_fs));
    m_fs[15] = 18;
    m_fs[16] = 20;
    m_fs[17] = 22;
    m_fs[18] = 23;
    m_fs[19] = 24;
    m_fs[20] = 25;
    m_fs[21] = 27;
    m_fs[22] = 28;
    m_fs[23] = 29;
    m_fs[24] = 30;
    m_fs[25] = 31;
    m_fs[26] = 33;
    m_fs[27] = 34;
    m_fs[28] = 35;
    m_fs[29] = 36;
    m_fs[30] = 37;
    m_fs[31] = 39;
    m_fs[32] = 41;
    m_fs[33] = 42;
    m_fs[34] = 43;
   
    m_fontTime.CreateFont(
        m_fs[iFloatingWindowHeight],0,0,0,FW_BOLD,FALSE,FALSE,FALSE,  
        ANSI_CHARSET,OUT_TT_ONLY_PRECIS,CLIP_DEFAULT_PRECIS,  
        DEFAULT_QUALITY,FIXED_PITCH|FF_SWISS,"Courier New");
    GetDlgItem(IDC_STATIC_TIMETIPS)->SetFont(&m_fontTime);
}

void CRelaxReminderDlg::InitShowTrayIcon()
{
    // 初始化通知栏图标变量
    m_bTrayIconVisible = FALSE;
    m_uIconID = IDR_MAINFRAME;
    
    if (m_bShowTrayIconAtStartup)
    {
        ShowTrayIcon();
    }
}

void CRelaxReminderDlg::ProcessFloatingWindow()
{
    if (FALSE == IsWindowVisible() &&   // 悬浮窗口不显示时，不用更新
        FALSE == m_bFloatingWindowHidebyFullscr)    // 例外：因全屏程序时
                                                    //       隐藏悬浮窗口
    {
        return;
    }

    switch (m_tm.GetStatus())
    {
    case STATUS_INIT:
        FloatingWindowInitStatus(); break;
    case STATUS_WORK:
        FloatingWindowWorkStatus(); break;
    case STATUS_SHORT_RELAX:
        FloatingWindowShortRelaxStatus(); break;
    case STATUS_LONG_RELAX:
        FloatingWindowLongRelaxStatus(); break;
    case STATUS_PAUSE:
        FloatingWindowPauseStatus(); break;
    case STATUS_RESET:
        FloatingWindowResetStatus(); break;
    case STATUS_AUTO_PAUSE:
        FloatingWindowAutoPauseStatus(); break;
    case STATUS_AUTO_RESET:
        FloatingWindowAutoResetStatus(); break;
    default:
        break;
    }
}

void CRelaxReminderDlg::MakeFloatingWindowMovable()
{
    // 设置窗口透明度
    SetWindowTransparent(POSITION_ADJUST_TRANSPARENCY);
    // 取消窗口点击穿透属性
    SetWindowLong(this->GetSafeHwnd(), GWL_EXSTYLE,
        GetWindowLong(this->GetSafeHwnd(), GWL_EXSTYLE)&(~WS_EX_TRANSPARENT));

    ShowWindow(SW_SHOW);
}

void CRelaxReminderDlg::MakeFloatingWindowFixed()
{
    // 设置窗口透明度
    SetWindowTransparent(FLOATING_WINDOW_TRANSPARENCY);
    // 设置窗口点击穿透属性
    SetWindowLong(this->GetSafeHwnd(), GWL_EXSTYLE,
        GetWindowLong(this->GetSafeHwnd(), GWL_EXSTYLE)|WS_EX_TRANSPARENT);
    // 记录当前窗口位置
    GetWindowRect(&m_rectFloatingWindow);

    // 开始检测鼠标悬停
    SetTimer(TIMER_MOUSE_HOVER_DETECT, MOUSE_HOVER_DETECT_LENGTH, NULL);
    
    ShowWindow(SW_SHOW);
}

void CRelaxReminderDlg::MakeFloatingWindowInvisible()
{
    // 停止检测鼠标悬停
    KillTimer(TIMER_MOUSE_HOVER_DETECT);

    ShowWindow(SW_HIDE);
}

void CRelaxReminderDlg::FloatingWindowMouseHoverDetect()
{
    static int  iMouseHoverCount = 0;
    CPoint      point;
    
    GetCursorPos(&point);
    GetWindowRect(&m_rectFloatingWindow);
    
    if (m_rectFloatingWindow.PtInRect(point))
    {
        if (++iMouseHoverCount > 0)
        {
            MakeFloatingWindowMovable();
            iMouseHoverCount = 0;
        }
    }
    else
    {
        MakeFloatingWindowFixed();
        iMouseHoverCount = 0;
    }
}

void CRelaxReminderDlg::FloatingWindowInitStatus()
{
    // 无需处理
}

void CRelaxReminderDlg::FloatingWindowWorkStatus()
{
    GetDlgItem(IDC_STATIC_TIMETIPS)->SetWindowText(GetTwinklingTime());
    GetDlgItem(IDC_STATIC_TIMETIPS)->EnableWindow(TRUE);

    if (m_bFloatingWindowHidebyFullscr)
    {
        MakeFloatingWindowFixed();
        m_bFloatingWindowHidebyFullscr = FALSE;
    }
}

void CRelaxReminderDlg::FloatingWindowShortRelaxStatus()
{
    GetDlgItem(IDC_STATIC_TIMETIPS)->SetWindowText(GetTwinklingTime());
    GetDlgItem(IDC_STATIC_TIMETIPS)->EnableWindow(TRUE);
}

void CRelaxReminderDlg::FloatingWindowLongRelaxStatus()
{
    GetDlgItem(IDC_STATIC_TIMETIPS)->SetWindowText(GetTwinklingTime());
    GetDlgItem(IDC_STATIC_TIMETIPS)->EnableWindow(TRUE);
}

void CRelaxReminderDlg::FloatingWindowPauseStatus()
{
    GetDlgItem(IDC_STATIC_TIMETIPS)->SetWindowText(GetFixedColonTime());
    GetDlgItem(IDC_STATIC_TIMETIPS)->EnableWindow(FALSE);
}

void CRelaxReminderDlg::FloatingWindowResetStatus()
{
    GetDlgItem(IDC_STATIC_TIMETIPS)->SetWindowText("00:00");
    GetDlgItem(IDC_STATIC_TIMETIPS)->EnableWindow(FALSE);
}

void CRelaxReminderDlg::FloatingWindowAutoPauseStatus()
{
    GetDlgItem(IDC_STATIC_TIMETIPS)->SetWindowText(GetFixedColonTime());
    GetDlgItem(IDC_STATIC_TIMETIPS)->EnableWindow(FALSE);

    if (IsWindowVisible() &&
        AUTO_PAUSE_FULLSCREEN == m_tm.GetAutoPauseType())
    {
        m_bFloatingWindowHidebyFullscr = TRUE;
        MakeFloatingWindowInvisible();
    }
}

void CRelaxReminderDlg::FloatingWindowAutoResetStatus()
{
    GetDlgItem(IDC_STATIC_TIMETIPS)->SetWindowText("00:00");
    GetDlgItem(IDC_STATIC_TIMETIPS)->EnableWindow(FALSE);
}

void CRelaxReminderDlg::ProcessRelaxNotify()
{
    switch (m_tm.GetStatus())
    {
    case STATUS_WORK:
        if (m_tm.GetLS() == 0)
        {
            RelaxNotifyEnd();
        }
        PreRelaxNotify();
        break;
    case STATUS_PAUSE:
        RelaxNotifyEnd();
        break;
    case STATUS_SHORT_RELAX:
    case STATUS_LONG_RELAX:
        RelaxNotify();
        break;
    case STATUS_RESET:
        if (m_tm.GetLS() == 0)
        {
            RelaxNotifyEnd();
        }
        break;
    default:
        break;
    }
}

void CRelaxReminderDlg::PreRelaxNotify()
{
    if (m_bPreNotify)
    {
        if (m_tm.GetStatus() == STATUS_WORK)
        {
            UINT    nWorkTimeLeft = 0;
            nWorkTimeLeft = m_tm.GetWD() - m_tm.GetLS();
            // 休息前1分钟时，显示提示
            if (nWorkTimeLeft == 60)
            {
                // 显示任务栏提示窗口
                m_dlgRelaxNotify.ShowTrayWindow(
                    m_str.GetStr(TRAY_WINDOW_CAPTION_NEXT_RELAX), 
                    "01:00");
            }
            if (nWorkTimeLeft < 60 && nWorkTimeLeft >= 60 - PRE_NOTIFY_WINDOW_TTL)
            {
                m_dlgRelaxNotify.UpdateTrayWindow(NULL, GetTwinklingTime());
            }
            if (nWorkTimeLeft <= 60 - PRE_NOTIFY_WINDOW_TTL)
            {
                m_dlgRelaxNotify.DeleteTrayWindow();
            }
        }
    }
}

void CRelaxReminderDlg::RelaxNotify()
{
    UINT    nLS = 0;
    BOOL    bShortRelax = FALSE;

    nLS     = m_tm.GetLS();
    switch (m_tm.GetStatus())
    {
    case STATUS_SHORT_RELAX:
        bShortRelax = TRUE;
    	break;
    case STATUS_LONG_RELAX:
        bShortRelax = FALSE;
        break;
    default:
        return;
    }

    if (nLS == 0)
    {
        CalcNotifyWindowPos();
        if (m_bDarkerScreen)
        {
            // 先显示ScreenMask
            ShowDarkerScreen(m_iDarkerScreenAlpha,
                m_colorDarkerScreen,
                m_eDarkerScreenAnimateType);
        }
    }
    if ((!m_bDarkerScreen && (nLS == 0)) ||
        (m_bDarkerScreen && (nLS == TRAY_WINDOW_DELAY)))
    {
        // 再显示TrayWindow
        m_dlgRelaxNotify.ShowTrayWindow(
            m_str.GetStr(bShortRelax ? TRAY_WINDOW_CAPTION_SHORT_RELAX : TRAY_WINDOW_CAPTION_LONG_RELAX),
            GetFixedColonTime());
    }
    
    // 更新任务栏提示窗口显示的时间
    m_dlgRelaxNotify.UpdateTrayWindow(NULL, GetTwinklingTime());
    
    // 如果启用了休息时锁定鼠标键盘，则在休息开始后10秒钟时锁定
    if (m_bLockInput && nLS == (UINT)m_iGraceTimeBeforeLockInput)
    {
        switch (m_iLockType)
        {
        case RELAX_LOCK_KEYBOARD:
            LockKeyboard(TRUE);
            break;
        case RELAX_LOCK_MOUSE:
            LockMouse(TRUE);
            break;
        case RELAX_LOCK_BOTH:
            LockKeyBoardAndMouse(TRUE);
            break;
        default:
            LockMouse(TRUE);
            break;
        }
        m_dlgRelaxNotify.GetDlgItem(IDC_BUTTON_DELAY)->EnableWindow(FALSE);
        m_dlgRelaxNotify.GetDlgItem(IDC_BUTTON_SKIP)->EnableWindow(FALSE);
        m_dlgRelaxNotify.GetDlgItem(IDC_BUTTON_HIDE)->EnableWindow(FALSE);
    }
    
    // 如果启用了锁定计算机，则在休息开始后17秒钟时锁定
    if (m_bLockComputer && nLS == 17)
    {
        LockWorkStation();
    }
    
    // 如果启用了关闭显示器，则在休息开始后20秒钟时关闭
    if (m_bCloseMonitor && nLS == 20)
    {
        ::SendMessage(GetSafeHwnd(), WM_SYSCOMMAND, SC_MONITORPOWER, 1);
    }
}

void CRelaxReminderDlg::RelaxNotifyEnd()
{
    LockKeyBoardAndMouse(FALSE);
    HideDarkerScreen();
    m_dlgRelaxNotify.DeleteTrayWindow();
}

void CRelaxReminderDlg::ProcessIconStatus()
{
    CString strIconTips;

    if (FALSE == m_bTrayIconVisible)
    {// 通知栏图标不显示时，不用更新
        return;
    }
    
    char *pchTime = GetFixedColonTime();

    switch (m_tm.GetStatus())
    {
    case STATUS_INIT:
        strIconTips = "ReRe";
        m_uIconID = IDR_MAINFRAME;
        break;
    case STATUS_WORK:
        strIconTips.Format("%s(%d%%)  %s",
                           m_str.GetStr(TRAY_ICON_TIPS_WORK),
                           m_tm.GetLS() * 100 / m_tm.GetWD(),
                           pchTime);
        m_uIconID = IDI_ICON16 + m_tm.GetLS() * 15 / m_tm.GetWD();
        break;
    case STATUS_SHORT_RELAX:
        strIconTips.Format("%s(%d%%)  %s",
                           m_str.GetStr(TRAY_ICON_TIPS_SHORT_RELAX),
                           m_tm.GetLS() * 100 / m_tm.GetSRD(),
                           pchTime);
        m_uIconID = IDI_ICON1 + m_tm.GetLS() * 15 / m_tm.GetSRD();
        break;
    case STATUS_LONG_RELAX:
        strIconTips.Format("%s(%d%%)  %s",
                           m_str.GetStr(TRAY_ICON_TIPS_LONG_RELAX),
                           m_tm.GetLS() * 100 / m_tm.GetLRD(),
                           pchTime);
        m_uIconID = IDI_ICON1 + m_tm.GetLS() * 15 / m_tm.GetLRD();
        break;
    case STATUS_PAUSE:
    case STATUS_AUTO_PAUSE:
        strIconTips.Format("%s(%d%%)  %s",
                           m_str.GetStr(TRAY_ICON_TIPS_PAUSE),
                           m_tm.GetLS() * 100 / m_tm.GetWD(),
                           pchTime);
        m_uIconID = IDI_ICON31 + m_tm.GetLS() * 15 / m_tm.GetWD();
        break;
    case STATUS_RESET:
    case STATUS_AUTO_RESET:
        strIconTips = "ReRe";
        // 复位时，闪烁托盘图标
        m_uIconID = (m_uIconID == IDI_ICON_RESET_01) ? IDI_ICON_RESET_02 : IDI_ICON_RESET_01;
        break;
    default:
        break;
    }
    m_hIcon = AfxGetApp()->LoadIcon(m_uIconID);

    UpdateTrayIcon(strIconTips);
}

void CRelaxReminderDlg::ShowTrayIcon() 
{
    m_nd.cbSize = sizeof (NOTIFYICONDATA);
    m_nd.hWnd = m_hWnd;
    m_nd.uID = 0;
    m_nd.uFlags = NIF_ICON|NIF_MESSAGE|NIF_TIP;
    m_nd.uCallbackMessage = WM_NOTIFYICON;
    m_nd.hIcon = m_hIcon;
    strcpy(m_nd.szTip, "ReRe");
    Shell_NotifyIcon(NIM_ADD, &m_nd);

    m_bTrayIconVisible = TRUE;
}

void CRelaxReminderDlg::UpdateTrayIcon(const char* szTip)
{
    if (NULL == szTip)
    {
        return;
    }

    strcpy(m_nd.szTip, szTip);
    m_nd.hIcon = m_hIcon;
    Shell_NotifyIcon(NIM_MODIFY, &m_nd);
}

void CRelaxReminderDlg::DeleteTrayIcon()
{
    Shell_NotifyIcon(NIM_DELETE, &m_nd);

    m_bTrayIconVisible = FALSE;
}

LONG CRelaxReminderDlg::OnNotifyIcon(WPARAM wParam, LPARAM lParam)
{
    // 响应在托盘图标上的单击，wParam中是响应消息的图标ID，lParam中则是Windows的消息

    switch ( lParam )
    {
    case WM_RBUTTONDOWN:
        ShowRightClickMenu();
        break;
    case WM_LBUTTONDBLCLK:
    case WM_LBUTTONDOWN:
        OnMenuMainWindow();
        break;
    }
    return 0;
}

void CRelaxReminderDlg::ShowRightClickMenu()
{
    // 在托盘图标上单击鼠标右键，弹出菜单    
    CMenu    oMenu;
    if (FALSE == oMenu.LoadMenu(IDR_MENU_TRAYMENU))
    {
        return;
    }
    CMenu* pPopup = oMenu.GetSubMenu(0);
    ASSERT(pPopup != NULL);

    LoadMenuLanguageString(&oMenu);

    // 设置默认菜单项为“显示悬浮窗”
    pPopup->SetDefaultItem(ID_MENU_MAIN_WINDOW, FALSE);

    // “显示悬浮窗”菜单是否选中
    oMenu.CheckMenuItem(ID_MENU_MAIN_WINDOW, IsWindowVisible() ? MF_CHECKED : MF_UNCHECKED);
    // “显示通知栏图标”菜单是否选中
    oMenu.CheckMenuItem(ID_MENU_TRAY_ICON, m_bTrayIconVisible ? MF_CHECKED : MF_UNCHECKED);
    // “暂停”菜单默认为不选中
    oMenu.CheckMenuItem(ID_MENU_PAUSE, MF_UNCHECKED);
    
    // 处理其它菜单项的显示状态，默认为可用，只需要设置不可用的项
    switch (m_tm.GetStatus())
    {
    case STATUS_INIT:
        oMenu.EnableMenuItem(ID_MENU_SHORT_RELAX, MF_DISABLED | MF_GRAYED);
        oMenu.EnableMenuItem(ID_MENU_LONG_RELAX, MF_DISABLED | MF_GRAYED);
        oMenu.EnableMenuItem(ID_MENU_PAUSE, MF_DISABLED | MF_GRAYED);
        oMenu.EnableMenuItem(ID_MENU_RESET, MF_DISABLED | MF_GRAYED);
        break;
    case STATUS_WORK:
    case STATUS_AUTO_PAUSE:    // 有可能在1秒心跳还没到，状态还是AutoPause或AutoReset,
    case STATUS_AUTO_RESET:    // 但在操作菜单时实际可能已经处于工作态了，故这里与工作态使用相同的设置
        oMenu.EnableMenuItem(ID_MENU_START_WORK, MF_DISABLED | MF_GRAYED);
        break;
    case STATUS_SHORT_RELAX:
        oMenu.EnableMenuItem(ID_MENU_SHORT_RELAX, MF_DISABLED | MF_GRAYED);
        oMenu.EnableMenuItem(ID_MENU_LONG_RELAX, MF_DISABLED | MF_GRAYED);
        oMenu.EnableMenuItem(ID_MENU_PAUSE, MF_DISABLED | MF_GRAYED);
        break;
    case STATUS_LONG_RELAX:
        oMenu.EnableMenuItem(ID_MENU_SHORT_RELAX, MF_DISABLED | MF_GRAYED);
        oMenu.EnableMenuItem(ID_MENU_LONG_RELAX, MF_DISABLED | MF_GRAYED);
        oMenu.EnableMenuItem(ID_MENU_PAUSE, MF_DISABLED | MF_GRAYED);
        break;
    case STATUS_PAUSE:
        oMenu.CheckMenuItem(ID_MENU_PAUSE, MF_CHECKED);
        oMenu.EnableMenuItem(ID_MENU_START_WORK, MF_DISABLED | MF_GRAYED);
        oMenu.EnableMenuItem(ID_MENU_SHORT_RELAX, MF_DISABLED | MF_GRAYED);
        oMenu.EnableMenuItem(ID_MENU_LONG_RELAX, MF_DISABLED | MF_GRAYED);
        break;
    case STATUS_RESET:
        oMenu.EnableMenuItem(ID_MENU_PAUSE, MF_DISABLED | MF_GRAYED);
        oMenu.EnableMenuItem(ID_MENU_RESET, MF_DISABLED | MF_GRAYED);
        break;
    default:
        break;
    }
    
    // 确定鼠标位置以便在该位置附近显示菜单
    CPoint Point;
    GetCursorPos(&Point);
    SetForegroundWindow();
    pPopup->TrackPopupMenu(
        TPM_LEFTALIGN | TPM_RIGHTBUTTON,
        Point.x, Point.y, this);
}

void CRelaxReminderDlg::LoadMenuLanguageString(CMenu *pMenu)
{
    LoadMenuString(ID_MENU_MAIN_WINDOW, MENU_FLOATING_WINDOW);
    LoadMenuString(ID_MENU_TRAY_ICON, MENU_TRAY_ICON);
    LoadMenuString(ID_MENU_START_WORK, MENU_START_WORK);
    LoadMenuString(ID_MENU_SHORT_RELAX, MENU_SHORT_RELAX);
    LoadMenuString(ID_MENU_LONG_RELAX, MENU_LONG_RELAX);
    LoadMenuString(ID_MENU_PAUSE, MENU_PAUSE);
    LoadMenuString(ID_MENU_RESET, MENU_RESET);
    LoadMenuString(ID_MENU_OPTION, MENU_OPTION);
    LoadMenuString(ID_MENU_ABOUT, MENU_ABOUT);
    LoadMenuString(ID_MENU_EXIT, MENU_EXIT);
}

void CRelaxReminderDlg::QuitProcess() 
{
    SaveStatisticsToIniFile();
    DeleteTrayIcon();
    DllExport_UninstallKeyboardHook();
    DllExport_UninstallMouseHook();
}

void CRelaxReminderDlg::OnDisplayChange(WPARAM wParam, LPARAM lParam)
{
    CalcNotifyWindowPos();
}

void CRelaxReminderDlg::CalcNotifyWindowPos()
{
    GetAllMonitorInfo();
    m_dlgRelaxNotify.DisplayChange();
    for (int i = 0; i < MULTI_MONITOR_NUM; i++)
    {
        if (i < m_iUsedDarkerScreen)
        {
            m_adlgDarkerScreen[i].DisplayChange();
        }
        else
        {
            m_adlgDarkerScreen[i].DeleteDarkerScreen();
        }
    }
}

BOOL AddDarkerScreenPos(CRelaxReminderDlg *pdlg, LPRECT lprc)
{
    if (!pdlg || !lprc || pdlg->m_iUsedDarkerScreen >= MULTI_MONITOR_NUM)
    {
        return FALSE;
    }

    if (lprc->left == 0 && lprc->top == 0)
    {
        SystemParametersInfo(SPI_GETWORKAREA, 0,
            &(pdlg->m_adlgDarkerScreen[pdlg->m_iUsedDarkerScreen++].m_rectScreen),
            0);
    }
    else
    {
        pdlg->m_adlgDarkerScreen[pdlg->m_iUsedDarkerScreen++].m_rectScreen = lprc;
    }
    return TRUE;
}

BOOL SetNotifyWindowPos(CRelaxReminderDlg *pdlg, int iDarkerScreenIdx)
{
    if (!pdlg || pdlg->m_iUsedDarkerScreen >= MULTI_MONITOR_NUM)
    {
        return FALSE;
    }

    pdlg->m_dlgRelaxNotify.m_rectMonitor =
        pdlg->m_adlgDarkerScreen[iDarkerScreenIdx].m_rectScreen;
    pdlg->m_dlgRelaxNotify.MoveToBottomRight();

    return TRUE;
}

BOOL CALLBACK MonitorEnumProc(HMONITOR hMonitor, HDC hdcMonitor,
                              LPRECT lprcMonitor, LPARAM dwData)
{
    CRect   rect;
    POINT   posCursor;
    BOOL    bMasterMonitor;
    BOOL    bCursorMonitor;

    rect = lprcMonitor;
    GetCursorPos(&posCursor);
    bMasterMonitor = (lprcMonitor->left == 0) && (lprcMonitor->top == 0);
    bCursorMonitor = rect.PtInRect(posCursor);

    CRelaxReminderDlg *pdlgMain = (CRelaxReminderDlg*)dwData;
    if (NULL == pdlgMain)
    {
        return FALSE;
    }

    if ((bMasterMonitor &&
        pdlgMain->m_eDarkerScreenType != CURSOR_MONITOR &&
        pdlgMain->m_eNotifyWindowType == MASTER_MONITOR)
        ||
        (bCursorMonitor &&
        pdlgMain->m_eDarkerScreenType != MASTER_MONITOR &&
        pdlgMain->m_eNotifyWindowType == CURSOR_MONITOR))
    {
        AddDarkerScreenPos(pdlgMain, lprcMonitor);
        SetNotifyWindowPos(pdlgMain, pdlgMain->m_iUsedDarkerScreen - 1);
    }
    else if (pdlgMain->m_eDarkerScreenType == ALL_MONITOR)
    {
        AddDarkerScreenPos(pdlgMain, lprcMonitor);
    }

    pdlgMain->m_iMonitorCount++;
    return TRUE;
}

void CRelaxReminderDlg::GetAllMonitorInfo()
{
    m_iMonitorCount = 0;
    m_iUsedDarkerScreen = 0;
    EnumDisplayMonitors(NULL, NULL, MonitorEnumProc, (DWORD)this);
}

void CRelaxReminderDlg::PutDarkerScreenUnderTrayWindow()
{
    for (int i = 0; i < m_iUsedDarkerScreen; i++)
    {
        if (m_adlgDarkerScreen[i].IsWindowVisible() == FALSE)
        {
            continue;
        }
        m_adlgDarkerScreen[i].SetWindowPos(&m_dlgRelaxNotify,0,0,0,0,
            SWP_NOMOVE|SWP_NOSIZE|SWP_NOACTIVATE);
    }
}

void CRelaxReminderDlg::ShowDarkerScreen(int iAlpha,
                                         COLORREF color,
                                         EAnimateType eAnimateType)
{
    for (int i = 0; i < m_iUsedDarkerScreen; i++)
    {
        m_adlgDarkerScreen[i].ShowDarkerScreen(iAlpha, color, eAnimateType);
    }
}

void CRelaxReminderDlg::HideDarkerScreen()
{
    for (int i = 0; i < m_iUsedDarkerScreen; i++)
    {
        m_adlgDarkerScreen[i].DeleteDarkerScreen();
    }
}

void CRelaxReminderDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
    // TODO: Add your message handler code here and/or call default
    CDialog::OnLButtonDown(nFlags, point);
    PostMessage(WM_SYSCOMMAND, SC_MOVE | HTCAPTION, 0);
}

void CRelaxReminderDlg::OnRButtonUp(UINT nFlags, CPoint point) 
{
    // TODO: Add your message handler code here and/or call default
    ShowRightClickMenu();

    CDialog::OnRButtonUp(nFlags, point);
}

void CRelaxReminderDlg::OnNcLButtonUp(UINT nHitTest, CPoint point)
{
    MakeFloatingWindowFixed();
}

void CRelaxReminderDlg::OnMenuMainWindow() 
{
    // TODO: Add your command handler code here
    if (IsWindowVisible())
    {
        MakeFloatingWindowInvisible();
    }
    else
    {
        MakeFloatingWindowFixed();
    }
}

void CRelaxReminderDlg::OnMenuTrayIcon() 
{
    // TODO: Add your command handler code here
    if (m_bTrayIconVisible)
    {
        DeleteTrayIcon();
    }
    else
    {
        ShowTrayIcon();
    }
}

void CRelaxReminderDlg::OnMenuStartWork() 
{
    // TODO: Add your command handler code here
    AppLog(L_MSG, " --> start work.");
    m_tm.StartWork();
    UpdateAll();
    
    // 如果还有任务栏提示窗口，则关闭它
    m_dlgRelaxNotify.DeleteTrayWindow();
}

void CRelaxReminderDlg::OnMenuShortRelax() 
{
    // TODO: Add your command handler code here
    AppLog(L_MSG, " --> start short relax.");
    m_tm.StartShortRelax();
    UpdateAll();
}

void CRelaxReminderDlg::OnMenuLongRelax() 
{
    // TODO: Add your command handler code here
    AppLog(L_MSG, " --> start long relax.");
    m_tm.StartLongRelax();
    UpdateAll();
}

void CRelaxReminderDlg::OnMenuPause() 
{
    // TODO: Add your command handler code here
    if (m_tm.GetStatus() == STATUS_WORK)
    {
        AppLog(L_MSG, " --> pause timer.");
        m_tm.TimerPause();
        UpdateAll();
        return;
    }
    if (m_tm.GetStatus() == STATUS_PAUSE)
    {
        AppLog(L_MSG, " --> resume timer.");
        m_tm.TimerResume();
        UpdateAll();
        return;
    }
}

void CRelaxReminderDlg::OnMenuReset() 
{
    // TODO: Add your command handler code here
    AppLog(L_MSG, " --> reset timer.");
    m_tm.TimerReset();
    UpdateAll();
    
    // 如果还有任务栏提示窗口，则关闭它
    m_dlgRelaxNotify.DeleteTrayWindow();
}

void CRelaxReminderDlg::OnMenuOption() 
{
    // TODO: Add your command handler code here
    AppLog(L_MSG, "open option dialog.");

    if (NULL == m_pdlgOption)
    {
        CDialogOption dlg;
        dlg.m_pdlgMain = this;
        m_pdlgOption = &dlg;
        dlg.DoModal();
        m_pdlgOption = NULL;
    } 
    else
    {
        m_pdlgOption->ShowWindow(SW_SHOW);
        m_pdlgOption->BringWindowToTop();
    }
}

void CRelaxReminderDlg::OnMenuAbout() 
{
    // TODO: Add your command handler code here
    AppLog(L_MSG, "open about dialog.");

    if (NULL == m_pdlgAbout)
    {
        CDialogAbout dlg;
        dlg.m_pdlgMain = this;
        m_pdlgAbout = &dlg;
        dlg.DoModal();
        m_pdlgAbout = NULL;
    }
    else
    {
        m_pdlgAbout->ShowWindow(SW_SHOW);
        m_pdlgAbout->BringWindowToTop();
    }
}

void CRelaxReminderDlg::OnMenuExit() 
{
    // TODO: Add your command handler code here
    QuitProcess();
    AppLog(L_MSG, "exit... goodbye.");
    exit(0);
}

void CRelaxReminderDlg::OnDestroy() 
{
    CDialog::OnDestroy();
    
    // TODO: Add your message handler code here
    QuitProcess();
}
