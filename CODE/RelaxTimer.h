#ifndef _RELAX_TIMER_H
#define _RELAX_TIMER_H


// RelaxTimer所有的状态列表
typedef enum _TimerStatus{
    STATUS_INIT = 0,
    STATUS_WORK,
    STATUS_SHORT_RELAX,
    STATUS_LONG_RELAX,
    STATUS_PAUSE,
    STATUS_RESET,
    STATUS_AUTO_PAUSE,
    STATUS_AUTO_RESET
} TimerStatus;

// AutoPause的几种状态
typedef enum {
    AUTO_PAUSE_NO = 0,
    AUTO_PAUSE_IDLE,
    AUTO_PAUSE_FULLSCREEN,
} EAutoPauseType;

// 时间统计结构体
typedef struct _TimeStatistics
{
    UINT    nTotalSeconds;      // 程序总的运行时间
    UINT    nWorkSeconds;       // 工作状态下的时间
    UINT    nSRelaxSeconds;     // 短休息状态下的时间
    UINT    nLRelaxSeconds;     // 长休息状态下的时间
    UINT    nPauseSeconds;      // 暂停状态下的时间
    UINT    nResetSeconds;      // 复位状态下的时间
} TimeStatistics;

// 休息统计结构体
typedef struct _RelaxStatistics
{
    UINT    nSRelaxTimes;       // 短休息次数
    UINT    nLRelaxTimes;       // 长休息次数
    UINT    nDelayedTimes;      // 使用延迟的次数
    UINT    nSkippedTimes;      // 使用跳过的次数
} RelaxStatistics;


// RelaxTimer类定义
class RelaxTimer
{
public:
    //////////////////////////////////////////////////////////////////////////
    // 构造函数和析构函数
    //////////////////////////////////////////////////////////////////////////
    RelaxTimer();
    ~RelaxTimer();

    //////////////////////////////////////////////////////////////////////////
    //  读/写成员变量的函数 (对外接口)
    //      读成功返回正确值，失败返回ACCESS_ERROR(0x12345678)
    //      写成功返回TRUE，失败返回FALSE
    //////////////////////////////////////////////////////////////////////////

    // 当前状态
    TimerStatus     GetStatus();                            // 读m_nStatus
    char*           GetStatusString();                      // 获取m_nStatus对应的状态字符串
    char*           StatusToString(TimerStatus nStatus);    // 获取nStatus对应的状态字符串
    BOOL            SetStatus(TimerStatus nStatus);         // 写m_nStatus
    UINT            GetLS();                                // 读m_nLapsedSeconds
    BOOL            IncLS();                                // m_nLapsedSeconds增1
    BOOL            SetLS(UINT nValue);                     // 写m_nLapsedSeconds
    UINT            GetSRT();                               // 读m_nShortRelaxedTimes
    BOOL            IncSRT();                               // m_nShortRelaxedTimes增1
    BOOL            DecSRT();                               // m_nShortRelaxedTimes减1
    BOOL            SetSRT(UINT nValue);                    // 写m_nShortRelaxedTimes
    // 时间设置
    UINT            GetWD();                                // 读m_nWorkDuration
    BOOL            SetWD(UINT nValue);                     // 写m_nWorkDuration
    UINT            GetSRD();                               // 读m_nShortRelaxDuration
    BOOL            SetSRD(UINT nValue);                    // 写m_nShortRelaxDuration
    UINT            GetEnableLongRelax();                   // 读m_bEnableLongRelax
    BOOL            SetEnableLongRelax(BOOL bValue);        // 写m_bEnableLongRelax
    UINT            GetLRF();                               // 读m_nLongRelaxFrequency
    BOOL            SetLRF(UINT nValue);                    // 写m_nLongRelaxFrequency
    UINT            GetLRD();                               // 读m_nLongRelaxDuration
    BOOL            SetLRD(UINT nValue);                    // 写m_nLongRelaxDuration
    // 自动状态转换
    UINT            GetEnableAutoPause();                   // 读m_bEnableAutoPause
    BOOL            SetEnableAutoPause(UINT bValue);        // 写m_bEnableAutoPause
    UINT            GetAPT();                               // 读m_nAutoPauseThreshold
    BOOL            SetAPT(UINT nValue);                    // 写m_nAutoPauseThreshold
    UINT            GetEnableFullScreenPause();             // 读m_bEnableFullScreenPause
    BOOL            SetEnableFullScreenPause(UINT bValue);  // 写m_bEnableFullScreenPause
    UINT            GetAutoPauseType();                     // 读m_eAutoPauseType
    UINT            GetEnableAutoReset();                   // 读m_bEnableAutoReset
    BOOL            SetEnableAutoReset(UINT bValue);        // 写m_bEnableAutoReset
    UINT            GetART();                               // 读m_nAutoResetThreshold
    BOOL            SetART(UINT nValue);                    // 写m_nAutoResetThreshold

private:
    //////////////////////////////////////////////////////////////////////////
    // 状态处理函数 (内部调用)
    //////////////////////////////////////////////////////////////////////////
    void            ProcessStatistics();
    TimerStatus     ProcessTimerStatus();

    // 状态机处理函数
    void            ProcessInitStatus();
    void            ProcessWorkStatus();
    void            ProcessShortRelaxStatus();
    void            ProcessLongRelaxStatus();
    void            ProcessPauseStatus();
    void            ProcessResetStatus();
    void            ProcessAutoPauseStatus();
    void            ProcessAutoResetStatus();

    // 状态转换处理函数
    void            Init2Work();
    void            Work2ShortRelax();
    void            Work2LongRelax();
    void            Work2Pause();
    void            Work2Reset();
    void            Work2AutoPause(EAutoPauseType eAutoPauseType);
    void            Work2AutoReset();
    void            ShortRelax2Work();
    void            ShortRelax2Reset();
    void            LongRelax2Work();
    void            LongRelax2Reset();
    void            Pause2Work();
    void            Pause2Reset();
    void            Reset2Work();
    void            Reset2ShortRelax();
    void            Reset2LongRelax();
    void            AutoPause2Work();
    void            AutoPause2AutoReset();
    void            AutoReset2Work();

    // 状态转换出错函数
    void            StatusTransferNotSupport(TimerStatus statusFrom, TimerStatus statusTo);

public:
    //////////////////////////////////////////////////////////////////////////
    // 状态控制函数 (对外接口)
    //////////////////////////////////////////////////////////////////////////
    TimerStatus     HeartBeat1Second();
    void            StartWork();
    void            StartShortRelax();
    void            StartLongRelax();
    void            RelaxDelay();
    void            RelaxSkip();
    void            TimerPause();
    void            TimerResume();
    void            TimerReset();

    //////////////////////////////////////////////////////////////////////////
    // 统计函数 (对外接口)
    //////////////////////////////////////////////////////////////////////////
    UINT            StatGet_TotalSeconds();     // 程序总的运行时间
    UINT            StatGet_WorkSeconds();      // 工作状态下的时间
    UINT            StatGet_SRelaxSeconds();    // 短休息状态下的时间
    UINT            StatGet_LRelaxSeconds();    // 长休息状态下的时间
    UINT            StatGet_PauseSeconds();     // 暂停状态下的时间
    UINT            StatGet_ResetSeconds();     // 复位状态下的时间
    UINT            StatGet_SRelaxTimes();      // 短休息次数
    UINT            StatGet_LRelaxTimes();      // 长休息次数
    UINT            StatGet_DelayedTimes();     // 使用延迟的次数
    UINT            StatGet_SkippedTimes();     // 使用跳过的次数

    BOOL            StatSet_TotalSeconds(UINT nValue);  // 程序总的运行时间
    BOOL            StatSet_WorkSeconds(UINT nValue);   // 工作状态下的时间
    BOOL            StatSet_SRelaxSeconds(UINT nValue); // 短休息状态下的时间
    BOOL            StatSet_LRelaxSeconds(UINT nValue); // 长休息状态下的时间
    BOOL            StatSet_PauseSeconds(UINT nValue);  // 暂停状态下的时间
    BOOL            StatSet_ResetSeconds(UINT nValue);  // 复位状态下的时间
    BOOL            StatSet_SRelaxTimes(UINT nValue);   // 短休息次数
    BOOL            StatSet_LRelaxTimes(UINT nValue);   // 长休息次数
    BOOL            StatSet_DelayedTimes(UINT nValue);  // 使用延迟的次数
    BOOL            StatSet_SkippedTimes(UINT nValue);  // 使用跳过的次数

private:
    // 当前状态
    TimerStatus     m_nStatus;                  // RelaxTimer当前的状态
    UINT            m_nLapsedSeconds;           // RelaxTimer在当前状态下的计秒
    UINT            m_nShortRelaxedTimes;       // RelaxTimer在已经短休息的次数
    // 时间设置 (单位:秒)
    UINT            m_nWorkDuration;            // RelaxTimer工作时长
    UINT            m_nShortRelaxDuration;      // RelaxTimer短休息时长
    BOOL            m_bEnableLongRelax;         // RelaxTimer是否启用长休息
    UINT            m_nLongRelaxFrequency;      // RelaxTimer几次短休息后开始长休息
    UINT            m_nLongRelaxDuration;       // RelaxTimer长休息时长
    // 自动状态转换 (单位:秒)
    BOOL            m_bEnableAutoPause;         // RelaxTimer是否启用自动暂停
    UINT            m_nAutoPauseThreshold;      // RelaxTimer几分钟后进入自动暂停状态
    BOOL            m_bEnableFullScreenPause;   // RelaxTimer是否启用全屏后自动暂停
    EAutoPauseType  m_eAutoPauseType;           // RelaxTimer的自动暂停状态
    BOOL            m_bEnableAutoReset;         // RelaxTimer是否启用自动复位
    UINT            m_nAutoResetThreshold;      // RelaxTimer几分钟后进入自动复位状态
    // 统计结构体变量
    TimeStatistics  m_statTime;                 // 时间统计量
    RelaxStatistics m_statRelax;                // 休息统计量
};

#endif
