#include "stdafx.h"
#include "LibFunc.h"
#include "Log.h"
#include "RelaxTimer.h"


// 延迟休息的秒数(必须小于工作的最短时长)
#define RELAX_DELAY_SECOND                  5 * 60


//////////////////////////////////////////////////////////////////////////
// 构造函数和析构函数
//////////////////////////////////////////////////////////////////////////
RelaxTimer::RelaxTimer()
{
    // 当前状态
    m_nStatus               = STATUS_INIT;
    m_nLapsedSeconds        = 0;
    m_nShortRelaxedTimes    = 0;
    // 时间设置
    m_nWorkDuration         = 0;
    m_nShortRelaxDuration   = 0;
    m_bEnableLongRelax      = FALSE;
    m_nLongRelaxFrequency   = 0;
    m_nLongRelaxDuration    = 0;
    // 自动状态转换
    m_bEnableAutoPause      = FALSE;
    m_nAutoPauseThreshold   = 0;
    m_eAutoPauseType        = AUTO_PAUSE_NO;
    m_bEnableAutoReset      = FALSE;
    m_nAutoResetThreshold   = 0;
    memset(&m_statTime, 0, sizeof(m_statTime));
    memset(&m_statRelax, 0, sizeof(m_statRelax));
}

RelaxTimer::~RelaxTimer()
{
    // 暂时没有要释放的资源，函数留空
}

//////////////////////////////////////////////////////////////////////////
//     读/写成员变量的函数 (对外接口)
//         读成功返回正确值，失败返回ACCESS_ERROR(0x12345678)
//         写成功返回TRUE，失败返回FALSE
//////////////////////////////////////////////////////////////////////////

// 当前状态
TimerStatus RelaxTimer::GetStatus()     // 读m_nStatus
{
    return m_nStatus;
}

char* RelaxTimer::GetStatusString()     // 获取nStatus对应的状态字符串
{
    return StatusToString(m_nStatus);
}

char* RelaxTimer::StatusToString(TimerStatus nStatus)   // 获取nStatus对应的状态字符串
{
    switch (nStatus)
    {
    case STATUS_INIT:
        return "init";
    case STATUS_WORK:
        return "work";
    case STATUS_SHORT_RELAX:
        return "short relax";
    case STATUS_LONG_RELAX:
        return "long relax";
    case STATUS_PAUSE:
        return "pause";
    case STATUS_RESET:
        return "reset";
    case STATUS_AUTO_PAUSE:
        return "auto pause";
    case STATUS_AUTO_RESET:
        return "auto reset";
    default:
        return "ERROR";
    }
}

BOOL RelaxTimer::SetStatus(TimerStatus nStatus)     // 写m_nStatus
{
    CString strOldStatus, strNewStatus;

    // 获取跃迁前的状态
    strOldStatus = GetStatusString();

    // 状态跃迁
    m_nStatus = nStatus;

    // 获取跃迁后的状态
    strNewStatus = GetStatusString();

    AppLog(L_MSG, "timer status[%s] change to status[%s].",
           strOldStatus, strNewStatus);
    return TRUE;
}

UINT RelaxTimer::GetLS()                        // 读m_nLapsedSeconds
{
    return m_nLapsedSeconds;
}

BOOL RelaxTimer::IncLS()                        // m_nLapsedSeconds增1
{
    m_nLapsedSeconds++;
    return TRUE;
}

BOOL RelaxTimer::SetLS(UINT nValue)             // 写m_nLapsedSeconds
{
    m_nLapsedSeconds = nValue;
    return TRUE;
}

UINT RelaxTimer::GetSRT()                       // 读m_nShortRelaxedTimes
{
    return m_nShortRelaxedTimes;
}

BOOL RelaxTimer::IncSRT()                       // m_nShortRelaxedTimes增1
{
    m_nShortRelaxedTimes++;
    return TRUE;
}

BOOL RelaxTimer::DecSRT()                       // m_nShortRelaxedTimes减1
{
    m_nShortRelaxedTimes--;
    return TRUE;
}

BOOL RelaxTimer::SetSRT(UINT nValue)            // 写m_nShortRelaxedTimes
{
    m_nShortRelaxedTimes = nValue;
    return TRUE;
}

// 时间设置
UINT RelaxTimer::GetWD()                        // 读m_nWorkDuration
{
    return m_nWorkDuration;
}

BOOL RelaxTimer::SetWD(UINT nValue)             // 写m_nWorkDuration
{
    m_nWorkDuration = nValue;
    return TRUE;
}

UINT RelaxTimer::GetSRD()                       // 读m_nShortRelaxDuration
{
    return m_nShortRelaxDuration;
}

BOOL RelaxTimer::SetSRD(UINT nValue)            // 写m_nShortRelaxDuration
{
    m_nShortRelaxDuration = nValue;
    return TRUE;
}

UINT RelaxTimer::GetEnableLongRelax()           // 读m_bEnableLongRelax
{
    return m_bEnableLongRelax;
}

BOOL RelaxTimer::SetEnableLongRelax(BOOL bValue)    // 写m_bEnableLongRelax
{
    m_bEnableLongRelax = bValue;
    return TRUE;
}

UINT RelaxTimer::GetLRF()                       // 读m_nLongRelaxFrequency
{
    return m_nLongRelaxFrequency;
}

BOOL RelaxTimer::SetLRF(UINT nValue)            // 写m_nLongRelaxFrequency
{
    m_nLongRelaxFrequency = nValue;
    return TRUE;
}

UINT RelaxTimer::GetLRD()                       // 读m_nLongRelaxDuration
{
    return m_nLongRelaxDuration;
}

BOOL RelaxTimer::SetLRD(UINT nValue)            // 写m_nLongRelaxDuration
{
    m_nLongRelaxDuration = nValue;
    return TRUE;
}

// 自动状态转换
UINT RelaxTimer::GetEnableAutoPause()           // 读m_bEnableAutoPause
{
    return m_bEnableAutoPause;
}

BOOL RelaxTimer::SetEnableAutoPause(UINT bValue)    // 写m_bEnableAutoPause
{
    m_bEnableAutoPause = bValue;
    return TRUE;
}

UINT RelaxTimer::GetAPT()                       // 读m_nAutoPauseThreshold
{
    return m_nAutoPauseThreshold;
}

BOOL RelaxTimer::SetAPT(UINT nValue)            // 写m_nAutoPauseThreshold
{
    m_nAutoPauseThreshold = nValue;
    return TRUE;
}

UINT RelaxTimer::GetEnableFullScreenPause()     // 读m_bEnableFullScreenPause
{
    return m_bEnableFullScreenPause;
}

BOOL RelaxTimer::SetEnableFullScreenPause(UINT bValue)  // 写m_bEnableFullScreenPause
{
    m_bEnableFullScreenPause = bValue;
    return TRUE;
}

UINT RelaxTimer::GetAutoPauseType()             // 读m_eAutoPauseType
{
    return m_eAutoPauseType;
}

UINT RelaxTimer::GetEnableAutoReset()           // 读m_bEnableAutoReset
{
    return m_bEnableAutoReset;
}

BOOL RelaxTimer::SetEnableAutoReset(UINT bValue)    // 写m_bEnableAutoReset
{
    m_bEnableAutoReset = bValue;
    return TRUE;
}

UINT RelaxTimer::GetART()                       // 读m_nAutoResetThreshold
{
    return m_nAutoResetThreshold;
}

BOOL RelaxTimer::SetART(UINT nValue)            // 写m_nAutoResetThreshold
{
    m_nAutoResetThreshold = nValue;
    return TRUE;
}

//////////////////////////////////////////////////////////////////////////
// 状态处理函数 (内部调用)
//////////////////////////////////////////////////////////////////////////
void RelaxTimer::ProcessStatistics()
{
    // 时间统计
    m_statTime.nTotalSeconds++;
    switch (m_nStatus)
    {
    case STATUS_INIT:
        break;
    case STATUS_WORK:
        m_statTime.nWorkSeconds++; break;
    case STATUS_SHORT_RELAX:
        m_statTime.nSRelaxSeconds++; break;
    case STATUS_LONG_RELAX:
        m_statTime.nLRelaxSeconds++; break;
    case STATUS_PAUSE:
        m_statTime.nPauseSeconds++; break;
    case STATUS_RESET:
        m_statTime.nResetSeconds++; break;
    case STATUS_AUTO_PAUSE:
        m_statTime.nPauseSeconds++; break;
    case STATUS_AUTO_RESET:
        m_statTime.nResetSeconds++; break;
    default:
        break;
    }
}

TimerStatus RelaxTimer::ProcessTimerStatus()
{
    switch (m_nStatus)
    {
    case STATUS_INIT:
        ProcessInitStatus(); break;
    case STATUS_WORK:
        ProcessWorkStatus(); break;
    case STATUS_SHORT_RELAX:
        ProcessShortRelaxStatus(); break;
    case STATUS_LONG_RELAX:
        ProcessLongRelaxStatus(); break;
    case STATUS_PAUSE:
        ProcessPauseStatus(); break;
    case STATUS_RESET:
        ProcessResetStatus(); break;
    case STATUS_AUTO_PAUSE:
        ProcessAutoPauseStatus(); break;
    case STATUS_AUTO_RESET:
        ProcessAutoResetStatus(); break;
    default:
        break;
    }
    return m_nStatus;
}

void RelaxTimer::ProcessInitStatus()
{
    // INIT 状态不变化，暂不处理
}

void RelaxTimer::ProcessWorkStatus()
{
    LASTINPUTINFO lpi;
    lpi.cbSize = sizeof(lpi);
    GetLastInputInfo(&lpi);

    // 如果使用了全屏自动暂停，每10秒钟检查是否在全屏模式
    if (m_bEnableFullScreenPause == TRUE)
    {
        CTime timeAutoSave = CTime::GetCurrentTime();
        if (timeAutoSave.GetSecond() % 10 == 0)
        {
            if (FullscreenModeDectect())
            {
                Work2AutoPause(AUTO_PAUSE_FULLSCREEN);
                return;
            }
        }
    }

    // 如果使用了自动暂停状态转换，则处理鼠标键盘未输入的自动状态转换
    if (m_bEnableAutoPause == TRUE)
    {
        if (::GetTickCount()-lpi.dwTime >= m_nAutoPauseThreshold * 1000)
        {
            Work2AutoPause(AUTO_PAUSE_IDLE);
            return;
        }
    }
    // 如果使用了自动复位状态转换，则处理鼠标键盘未输入的自动状态转换
    if (m_bEnableAutoReset == TRUE)
    {
        // 如果长时间没有输入，则转入自动复位态
        if (::GetTickCount() - lpi.dwTime >= m_nAutoResetThreshold * 1000)
        {
            Work2AutoReset();
            return;
        }
    }

    IncLS();
    if (m_nLapsedSeconds >= m_nWorkDuration)    
    {// 工作状态结束，准备进入休息状态
        if (m_bEnableLongRelax && m_nShortRelaxedTimes >= m_nLongRelaxFrequency)
        {// 如果启用了长休息，且短休息次数大于设定值，则开始长休息
            Work2LongRelax();
        }
        else
        {// 否则直接开始短休息
            Work2ShortRelax();
        }
    }
}

void RelaxTimer::ProcessShortRelaxStatus()
{
    IncLS();
    if (m_nLapsedSeconds >= m_nShortRelaxDuration)
    {// 短休息状态结束，准备进入工作状态
        ShortRelax2Work();
    }
}

void RelaxTimer::ProcessLongRelaxStatus()
{
    IncLS();
    if (m_bEnableLongRelax && m_nLapsedSeconds >= m_nLongRelaxDuration)
    {// 长休息状态结束，准备进入工作状态
        LongRelax2Work();
    }
}

void RelaxTimer::ProcessPauseStatus()
{
    // PAUSE 状态不变化，暂不处理
}

void RelaxTimer::ProcessResetStatus()
{
    // RESET 状态不变化，暂不处理
}

void RelaxTimer::ProcessAutoPauseStatus()
{
    LASTINPUTINFO lpi;
    lpi.cbSize = sizeof(lpi);
    GetLastInputInfo(&lpi);

    if (m_eAutoPauseType == AUTO_PAUSE_FULLSCREEN)
    {
        if (FullscreenModeDectect() == FALSE)
        {// 如果不在全屏模式，则允许进入工作状态，且继续进行idle状态检测
            AutoPause2Work();
        }
        else
        {// 如果仍然处于是全屏状态，则不允许进行后续的idle状态检测
            return;
        }
    }
    
    if (m_bEnableAutoPause == TRUE)
    {
        // 如果发现有输入，则转入工作态
        if (::GetTickCount() - lpi.dwTime < m_nAutoPauseThreshold * 1000)
        {
            AutoPause2Work();
            return;
        }
    }
    if (m_bEnableAutoReset == TRUE)
    {
        // 如果长时间没有输入，则转入自动复位态
        if (::GetTickCount() - lpi.dwTime >= m_nAutoResetThreshold * 1000)
        {
            AutoPause2AutoReset();
            return;
        }
    }
}

void RelaxTimer::ProcessAutoResetStatus()
{
    LASTINPUTINFO lpi;
    lpi.cbSize = sizeof(lpi);
    GetLastInputInfo(&lpi);

    if (m_bEnableAutoReset == TRUE)
    {
        // 如果发现有输入，则转入工作态
        if (::GetTickCount() - lpi.dwTime < m_nAutoResetThreshold * 1000)
        {
            AutoReset2Work();
            return;
        }
    }
}

// 状态转换处理函数
void RelaxTimer::Init2Work()
{
    SetStatus(STATUS_WORK);             // 状态变为工作态
    SetLS(0);                           // 计秒归0
}

void RelaxTimer::Work2ShortRelax()
{
    SetStatus(STATUS_SHORT_RELAX);      // 状态变为短休息态
    SetLS(0);                           // 计秒归0
    IncSRT();                           // 短休息次数增1
    m_statRelax.nSRelaxTimes++;         // 更新统计量
}

void RelaxTimer::Work2LongRelax()
{
    SetStatus(STATUS_LONG_RELAX);       // 状态变为长休息态
    SetLS(0);                           // 计秒归0
    SetSRT(0);                          // 短休息次数归0
    m_statRelax.nLRelaxTimes++;         // 更新统计量
}

void RelaxTimer::Work2Pause()
{
    SetStatus(STATUS_PAUSE);            // 状态变为暂停态
}

void RelaxTimer::Work2Reset()
{
    SetStatus(STATUS_RESET);            // 状态变为复位态
    SetLS(0);                           // 计秒归0
    SetSRT(0);                          // 短休息次数归0
}

void RelaxTimer::Work2AutoPause(EAutoPauseType eAutoPauseType)
{
    SetStatus(STATUS_AUTO_PAUSE);       // 状态变为自动暂停态
    m_eAutoPauseType = eAutoPauseType;  // 记录状态改变的原因
}

void RelaxTimer::Work2AutoReset()
{
    SetStatus(STATUS_AUTO_RESET);       // 状态变为自动复位态
    SetLS(0);                           // 计秒归0
    SetSRT(0);                          // 短休息次数归0
}

void RelaxTimer::ShortRelax2Work()
{
    SetStatus(STATUS_WORK);             // 状态变为工作态
    SetLS(0);                           // 计秒归0
}

void RelaxTimer::ShortRelax2Reset()
{
    SetStatus(STATUS_RESET);            // 状态变为复位态
    SetLS(0);                           // 计秒归0
    SetSRT(0);                          // 短休息次数归0
}

void RelaxTimer::LongRelax2Work()
{
    SetStatus(STATUS_WORK);             // 状态变为工作态
    SetLS(0);                           // 计秒归0
}

void RelaxTimer::LongRelax2Reset()
{
    SetStatus(STATUS_RESET);            // 状态变为复位态
    SetLS(0);                           // 计秒归0
    SetSRT(0);                          // 短休息次数归0
}

void RelaxTimer::Pause2Work()
{
    SetStatus(STATUS_WORK);             // 状态变为工作态
}

void RelaxTimer::Pause2Reset()
{
    SetStatus(STATUS_RESET);            // 状态变为复位态
    SetLS(0);                           // 计秒归0
    SetSRT(0);                          // 短休息次数归0
}

void RelaxTimer::Reset2Work()
{
    SetStatus(STATUS_WORK);             // 状态变为工作态
    SetLS(0);                           // 计秒归0
}

void RelaxTimer::Reset2ShortRelax()
{
    SetStatus(STATUS_SHORT_RELAX);      // 状态变为短休息态
    SetLS(0);                           // 计秒归0
    IncSRT();                           // 短休息次数增1
    m_statRelax.nSRelaxTimes++;         // 更新统计量
}

void RelaxTimer::Reset2LongRelax()
{
    SetStatus(STATUS_LONG_RELAX);       // 状态变为长休息态
    SetLS(0);                           // 计秒归0
    SetSRT(0);                          // 短休息次数归0
    m_statRelax.nLRelaxTimes++;         // 更新统计量
}

void RelaxTimer::AutoPause2Work()
{
    SetStatus(STATUS_WORK);             // 状态变为工作态
    m_eAutoPauseType = AUTO_PAUSE_NO;
}

void RelaxTimer::AutoPause2AutoReset()
{
    SetStatus(STATUS_AUTO_RESET);       // 状态变为自动复位态
    SetLS(0);                           // 计秒归0
    SetSRT(0);                          // 短休息次数归0
    m_eAutoPauseType = AUTO_PAUSE_NO;
}

void RelaxTimer::AutoReset2Work()
{
    SetStatus(STATUS_WORK);             // 状态变为工作态
    SetLS(0);                           // 计秒归0
}

// 状态转换出错函数
void RelaxTimer::StatusTransferNotSupport(TimerStatus statusFrom,
                                          TimerStatus statusTo)
{
    AppLog(L_WARN, "timer status transfer not support, from[%s] to[%s].",
        StatusToString(statusFrom), StatusToString(statusFrom));
}

//////////////////////////////////////////////////////////////////////////
// 状态控制函数 (对外接口)
//////////////////////////////////////////////////////////////////////////
TimerStatus RelaxTimer::HeartBeat1Second()
{
    ProcessStatistics();
    return ProcessTimerStatus();
}

void RelaxTimer::StartWork()
{
    switch (m_nStatus)
    {
    case STATUS_INIT:
        Init2Work(); break;
    case STATUS_SHORT_RELAX:
        ShortRelax2Work(); break;
    case STATUS_LONG_RELAX:
        LongRelax2Work(); break;
    case STATUS_PAUSE:
        Pause2Work(); break;
    case STATUS_RESET:
        Reset2Work(); break;
    default:
        StatusTransferNotSupport(m_nStatus, STATUS_WORK); break;
    }
}

void RelaxTimer::StartShortRelax()
{
    switch (m_nStatus)
    {
    case STATUS_WORK:
        Work2ShortRelax(); break;
    case STATUS_RESET:
        Reset2ShortRelax(); break;
    default:
        StatusTransferNotSupport(m_nStatus, STATUS_SHORT_RELAX); break;
    }
}

void RelaxTimer::StartLongRelax()
{
    switch (m_nStatus)
    {
    case STATUS_WORK:
        Work2LongRelax(); break;
    case STATUS_RESET:
        Reset2LongRelax(); break;
    default:
        StatusTransferNotSupport(m_nStatus, STATUS_LONG_RELAX); break;
    }
}

void RelaxTimer::RelaxDelay()
{
    switch (m_nStatus)
    {
    case STATUS_SHORT_RELAX:
        ShortRelax2Work();
        DecSRT();
        break;
    case STATUS_LONG_RELAX:
        LongRelax2Work();
        DecSRT();
        break;
    default:
        break;
    }
    SetLS((GetWD() >= RELAX_DELAY_SECOND) ?
        GetWD() - RELAX_DELAY_SECOND : 0);

    // 更新统计变量
    m_statRelax.nDelayedTimes++;
}

void RelaxTimer::RelaxSkip()
{
    switch (m_nStatus)
    {
    case STATUS_SHORT_RELAX:
        ShortRelax2Work();
        break;
    case STATUS_LONG_RELAX:
        LongRelax2Work();
        break;
    case STATUS_WORK:
        Work2AutoReset();
        AutoReset2Work();
        break;
    default:
        return;
    }

    // 更新统计变量
    m_statRelax.nSkippedTimes++;

}

void RelaxTimer::TimerPause()
{
    switch (m_nStatus)
    {
    case STATUS_WORK:
        Work2Pause(); break;
    default:
        StatusTransferNotSupport(m_nStatus, STATUS_PAUSE); break;
    }
}

void RelaxTimer::TimerResume()
{
    switch (m_nStatus)
    {
    case STATUS_PAUSE:
        Pause2Work(); break;
    default:
        StatusTransferNotSupport(m_nStatus, STATUS_WORK); break;
    }
}

void RelaxTimer::TimerReset()
{
    switch (m_nStatus)
    {
    case STATUS_WORK:
        Work2Reset(); break;
    case STATUS_SHORT_RELAX:
        ShortRelax2Reset(); break;
    case STATUS_LONG_RELAX:
        LongRelax2Reset(); break;
    case STATUS_PAUSE:
        Pause2Reset(); break;
    default:
        StatusTransferNotSupport(m_nStatus, STATUS_RESET); break;
    }
}

UINT RelaxTimer::StatGet_TotalSeconds()
{
    return m_statTime.nTotalSeconds;
}

UINT RelaxTimer::StatGet_WorkSeconds()
{
    return m_statTime.nWorkSeconds;
}

UINT RelaxTimer::StatGet_SRelaxSeconds()
{
    return m_statTime.nSRelaxSeconds;
}

UINT RelaxTimer::StatGet_LRelaxSeconds()
{
    return m_statTime.nLRelaxSeconds;
}

UINT RelaxTimer::StatGet_PauseSeconds()
{
    return m_statTime.nPauseSeconds;
}

UINT RelaxTimer::StatGet_ResetSeconds()
{
    return m_statTime.nResetSeconds;
}

UINT RelaxTimer::StatGet_SRelaxTimes()
{
    return m_statRelax.nSRelaxTimes;
}

UINT RelaxTimer::StatGet_LRelaxTimes()
{
    return m_statRelax.nLRelaxTimes;
}

UINT RelaxTimer::StatGet_DelayedTimes()
{
    return m_statRelax.nDelayedTimes;
}

UINT RelaxTimer::StatGet_SkippedTimes()
{
    return m_statRelax.nSkippedTimes;
}

BOOL RelaxTimer::StatSet_TotalSeconds(UINT nValue)
{
    m_statTime.nTotalSeconds = nValue;
    return TRUE;
}

BOOL RelaxTimer::StatSet_WorkSeconds(UINT nValue)
{
    m_statTime.nWorkSeconds = nValue;
    return TRUE;
}

BOOL RelaxTimer::StatSet_SRelaxSeconds(UINT nValue)
{
    m_statTime.nSRelaxSeconds = nValue;
    return TRUE;
}

BOOL RelaxTimer::StatSet_LRelaxSeconds(UINT nValue)
{
    m_statTime.nLRelaxSeconds = nValue;
    return TRUE;
}

BOOL RelaxTimer::StatSet_PauseSeconds(UINT nValue)
{
    m_statTime.nPauseSeconds = nValue;
    return TRUE;
}

BOOL RelaxTimer::StatSet_ResetSeconds(UINT nValue)
{
    m_statTime.nResetSeconds = nValue;
    return TRUE;
}

BOOL RelaxTimer::StatSet_SRelaxTimes(UINT nValue)
{
    m_statRelax.nSRelaxTimes = nValue;
    return TRUE;
}

BOOL RelaxTimer::StatSet_LRelaxTimes(UINT nValue)
{
    m_statRelax.nLRelaxTimes = nValue;
    return TRUE;
}

BOOL RelaxTimer::StatSet_DelayedTimes(UINT nValue)
{
    m_statRelax.nDelayedTimes = nValue;
    return TRUE;
}

BOOL RelaxTimer::StatSet_SkippedTimes(UINT nValue)
{
    m_statRelax.nSkippedTimes = nValue;
    return TRUE;
}
