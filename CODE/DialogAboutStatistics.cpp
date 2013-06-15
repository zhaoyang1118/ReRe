// DialogAboutStatistics.cpp : implementation file
//

#include "stdafx.h"
#include "RelaxReminder.h"
#include "PubFunc.h"
#include "StringTable.h"
#include "RelaxTimer.h"
#include "DialogTrayWindow.h"
#include "DialogDarkerScreen.h"
#include "RelaxReminderDlg.h"
#include "DialogAboutStatistics.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogAboutStatistics dialog


CDialogAboutStatistics::CDialogAboutStatistics(CWnd* pParent /*=NULL*/)
    : CDialog(CDialogAboutStatistics::IDD, pParent)
{
    //{{AFX_DATA_INIT(CDialogAboutStatistics)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
}


void CDialogAboutStatistics::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDialogAboutStatistics)
    DDX_Control(pDX, IDC_LIST_STATISTIC, m_listStatistic);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogAboutStatistics, CDialog)
    //{{AFX_MSG_MAP(CDialogAboutStatistics)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogAboutStatistics message handlers

BOOL CDialogAboutStatistics::OnInitDialog() 
{
    CDialog::OnInitDialog();
    
    // TODO: Add extra initialization here
    InitStatistic();

    LoadLanguageStrings();
    
    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialogAboutStatistics::InitStatistic()
{
    CStringTable *pst = &(m_pdlgMain->m_str);
    
    // 设置显示属性
    m_listStatistic.SetBkColor(GetSysColor(COLOR_3DFACE));
    m_listStatistic.SetTextBkColor(GetSysColor(COLOR_3DFACE));
    ListView_SetExtendedListViewStyle(m_listStatistic, LVS_EX_FULLROWSELECT);

    // 设置列名称
    m_listStatistic.InsertColumn(0, pst->GetStr(ABOUT_STATISTICS_ITEM));
    m_listStatistic.SetColumnWidth(0, 160);
    m_listStatistic.InsertColumn(1, pst->GetStr(ABOUT_STATISTICS_COUNTER));
    m_listStatistic.SetColumnWidth(1, 110);
    m_listStatistic.InsertColumn(2, pst->GetStr(ABOUT_STATISTICS_RATIO));
    m_listStatistic.SetColumnWidth(2, 80);

    // 计算、显示时间统计
    UINT total  = m_pdlgMain->m_tm.StatGet_TotalSeconds();
    UINT work   = m_pdlgMain->m_tm.StatGet_WorkSeconds();
    UINT srelax = m_pdlgMain->m_tm.StatGet_SRelaxSeconds();
    UINT lrelax = m_pdlgMain->m_tm.StatGet_LRelaxSeconds();
    UINT pause  = m_pdlgMain->m_tm.StatGet_PauseSeconds();
    UINT reset  = m_pdlgMain->m_tm.StatGet_ResetSeconds();
    InsertHeadline(TIME_HEADLINE, pst->GetStr(ABOUT_STATISTICS_TIME_HEADLINE));
    InsertItem(TIME_TOTAL,  pst->GetStr(ABOUT_STATISTICS_TIME_TOTAL),   total,  1.0);
    InsertItem(TIME_WORK,   pst->GetStr(ABOUT_STATISTICS_TIME_WORK),    work,   (float)work / total);
    InsertItem(TIME_SRELAX, pst->GetStr(ABOUT_STATISTICS_TIME_SRELAX),  srelax, (float)srelax / total);
    InsertItem(TIME_LRELAX, pst->GetStr(ABOUT_STATISTICS_TIME_LRELAX),  lrelax, (float)lrelax / total);
    InsertItem(TIME_PAUSE,  pst->GetStr(ABOUT_STATISTICS_TIME_PAUSE),   pause,  (float)pause / total);
    InsertItem(TIME_RESET,  pst->GetStr(ABOUT_STATISTICS_TIME_RESET),   reset,  (float)reset / total);
    InsertEndline(TIME_ENDLINE);

    // 计算、显示休息统计
    UINT srelax_times   = m_pdlgMain->m_tm.StatGet_SRelaxTimes();
    UINT lrelax_times   = m_pdlgMain->m_tm.StatGet_LRelaxTimes();
    UINT relaxed_times  = srelax_times + lrelax_times;
    UINT delayed_times  = m_pdlgMain->m_tm.StatGet_DelayedTimes();
    UINT skipped_times  = m_pdlgMain->m_tm.StatGet_SkippedTimes();
    InsertHeadline(RELAX_HEADLINE, pst->GetStr(ABOUT_STATISTICS_RELAX_HEADLINE));
    InsertItem(RELAX_SRELAX,    pst->GetStr(ABOUT_STATISTICS_RELAX_SRELAX),     srelax_times,   (float)srelax_times / (relaxed_times?relaxed_times:1));
    InsertItem(RELAX_LRELAX,    pst->GetStr(ABOUT_STATISTICS_RELAX_LRELAX),     lrelax_times,   (float)lrelax_times / (relaxed_times?relaxed_times:1));
    InsertItem(RELAX_DELAYED,   pst->GetStr(ABOUT_STATISTICS_RELAX_DELAYED),    delayed_times,  (float)delayed_times / (relaxed_times?relaxed_times:1));
    InsertItem(RELAX_SKIPPED,   pst->GetStr(ABOUT_STATISTICS_RELAX_SKIPPED),    skipped_times,  (float)skipped_times / (relaxed_times?relaxed_times:1));
}

void CDialogAboutStatistics::UpdateTimeStatistic()
{
    // 计算、更新时间统计
    UINT total  = m_pdlgMain->m_tm.StatGet_TotalSeconds();
    UINT work   = m_pdlgMain->m_tm.StatGet_WorkSeconds();
    UINT srelax = m_pdlgMain->m_tm.StatGet_SRelaxSeconds();
    UINT lrelax = m_pdlgMain->m_tm.StatGet_LRelaxSeconds();
    UINT pause  = m_pdlgMain->m_tm.StatGet_PauseSeconds();
    UINT reset  = m_pdlgMain->m_tm.StatGet_ResetSeconds();
    UpdateItem(TIME_TOTAL,  total,  1.0);
    UpdateItem(TIME_WORK,   work,   (float)work / total);
    UpdateItem(TIME_SRELAX, srelax, (float)srelax / total);
    UpdateItem(TIME_LRELAX, lrelax, (float)lrelax / total);
    UpdateItem(TIME_PAUSE,  pause,  (float)pause / total);
    UpdateItem(TIME_RESET,  reset,  (float)reset / total);
}

void CDialogAboutStatistics::UpdateRelaxStatistic()
{
    // 计算、更新休息统计
    UINT srelax_times = m_pdlgMain->m_tm.StatGet_SRelaxTimes();
    UINT lrelax_times = m_pdlgMain->m_tm.StatGet_LRelaxTimes();
    UINT relaxed_times = srelax_times + lrelax_times;
    UINT delayed_times = m_pdlgMain->m_tm.StatGet_DelayedTimes();
    UINT skipped_times = m_pdlgMain->m_tm.StatGet_SkippedTimes();
    UpdateItem(RELAX_SRELAX,    srelax_times,   (float)srelax_times / (relaxed_times?relaxed_times:1));
    UpdateItem(RELAX_LRELAX,    lrelax_times,   (float)lrelax_times / (relaxed_times?relaxed_times:1));
    UpdateItem(RELAX_DELAYED,   delayed_times,  (float)delayed_times / (relaxed_times?relaxed_times:1));
    UpdateItem(RELAX_SKIPPED,   skipped_times,  (float)skipped_times / (relaxed_times?relaxed_times:1));
}

BOOL CDialogAboutStatistics::InsertHeadline(UINT nIndex, char* pchHeadline)
{
    // nIndex不能超过当前的行数
    if ((signed int)nIndex > m_listStatistic.GetItemCount())
    {
        return FALSE;
    }
    
    // Item项不能为空
    if (pchHeadline == NULL)
    {
        return FALSE;
    }
    
    // 开始插入数据
    LVITEM lvItem;
    lvItem.mask = LVIF_TEXT;
    lvItem.iItem = nIndex;
    // 插入Headline
    lvItem.iSubItem = 0;
    lvItem.pszText = pchHeadline;
    m_listStatistic.InsertItem(&lvItem);
    
    return TRUE;
}

BOOL CDialogAboutStatistics::InsertItem(UINT nIndex, char* pchItem, UINT nValue /* = 0 */, float fRatio /* = 0.0 */)
{
    // nIndex不能超过当前的行数
    if ((signed int)nIndex > m_listStatistic.GetItemCount())
    {
        return FALSE;
    }

    // Item项不能为空
    if (pchItem == NULL)
    {
        return FALSE;
    }

    // 开始插入数据
    CString str;
    LVITEM lvItem;
    lvItem.mask = LVIF_TEXT;
    lvItem.iItem = nIndex;
    // 插入Item
    str.Format("     %s", pchItem);
    lvItem.iSubItem = 0;
    lvItem.pszText = str.GetBuffer(0);
    m_listStatistic.InsertItem(&lvItem);
    // 插入Value
    str.Format("%d", nValue);
    lvItem.iSubItem = 1;
    lvItem.pszText = str.GetBuffer(0);
    m_listStatistic.SetItem(&lvItem);
    // 插入Ratio
    str.Format("%.2f%%", fRatio * 100);
    lvItem.iSubItem = 2;
    lvItem.pszText = str.GetBuffer(0);
    m_listStatistic.SetItem(&lvItem);

    return TRUE;
}

BOOL CDialogAboutStatistics::InsertEndline(UINT nIndex)
{
    // nIndex不能超过当前的行数
    if ((signed int)nIndex > m_listStatistic.GetItemCount())
    {
        return FALSE;
    }
    
    // 开始插入数据
    LVITEM lvItem;
    lvItem.mask = LVIF_TEXT;
    lvItem.iItem = nIndex;
    // 插入Headline
    lvItem.iSubItem = 0;
    lvItem.pszText = NULL;
    m_listStatistic.InsertItem(&lvItem);
    
    return TRUE;
}

BOOL CDialogAboutStatistics::UpdateItem(UINT nIndex, UINT nValue, float fRatio)
{
    // nIndex不能超过当前的行数
    if ((signed int)nIndex > m_listStatistic.GetItemCount())
    {
        return FALSE;
    }
    
    // 更新nIndex处的数据
    CString str;
    LVITEM lvItem;
    lvItem.mask = LVIF_TEXT;
    lvItem.iItem = nIndex;
    // 更新Value
    str.Format("%d", nValue);
    lvItem.iSubItem = 1;
    lvItem.pszText = str.GetBuffer(0);
    m_listStatistic.SetItem(&lvItem);
    // 更新Ratio
    str.Format("%.2f%%", fRatio * 100);
    lvItem.iSubItem = 2;
    lvItem.pszText = str.GetBuffer(0);
    m_listStatistic.SetItem(&lvItem);
    
    return TRUE;
}

void CDialogAboutStatistics::LoadLanguageStrings()
{
    CStringTable *pst;
    
    pst = &(m_pdlgMain->m_str);

    // 加载表头语言
    LVCOLUMN lvColumn;
    lvColumn.mask=LVCF_TEXT;
    lvColumn.cchTextMax=256;
    lvColumn.pszText=pst->GetStr(ABOUT_STATISTICS_ITEM);
    m_listStatistic.SetColumn(0, &lvColumn);
    lvColumn.pszText=pst->GetStr(ABOUT_STATISTICS_COUNTER);
    m_listStatistic.SetColumn(1, &lvColumn);
    lvColumn.pszText=pst->GetStr(ABOUT_STATISTICS_RATIO);
    m_listStatistic.SetColumn(2, &lvColumn);

    // 加载第一列语言
    LVITEM lvItem;
    lvItem.mask = LVIF_TEXT;
    lvItem.iSubItem = 0;
    lvItem.iItem = TIME_HEADLINE;
    lvItem.pszText = pst->GetStr(ABOUT_STATISTICS_TIME_HEADLINE);
    m_listStatistic.SetItem(&lvItem);
    lvItem.iItem = TIME_TOTAL;
    lvItem.pszText = pst->GetStr(ABOUT_STATISTICS_TIME_TOTAL);
    m_listStatistic.SetItem(&lvItem);
    lvItem.iItem = TIME_WORK;
    lvItem.pszText = pst->GetStr(ABOUT_STATISTICS_TIME_WORK);
    m_listStatistic.SetItem(&lvItem);
    lvItem.iItem = TIME_SRELAX;
    lvItem.pszText = pst->GetStr(ABOUT_STATISTICS_TIME_SRELAX);
    m_listStatistic.SetItem(&lvItem);
    lvItem.iItem = TIME_LRELAX;
    lvItem.pszText = pst->GetStr(ABOUT_STATISTICS_TIME_LRELAX);
    m_listStatistic.SetItem(&lvItem);
    lvItem.iItem = TIME_PAUSE;
    lvItem.pszText = pst->GetStr(ABOUT_STATISTICS_TIME_PAUSE);
    m_listStatistic.SetItem(&lvItem);
    lvItem.iItem = TIME_RESET;
    lvItem.pszText = pst->GetStr(ABOUT_STATISTICS_TIME_RESET);
    m_listStatistic.SetItem(&lvItem);
    lvItem.iItem = RELAX_HEADLINE;
    lvItem.pszText = pst->GetStr(ABOUT_STATISTICS_RELAX_HEADLINE);
    m_listStatistic.SetItem(&lvItem);
    lvItem.iItem = RELAX_SRELAX;
    lvItem.pszText = pst->GetStr(ABOUT_STATISTICS_RELAX_SRELAX);
    m_listStatistic.SetItem(&lvItem);
    lvItem.iItem = RELAX_LRELAX;
    lvItem.pszText = pst->GetStr(ABOUT_STATISTICS_RELAX_LRELAX);
    m_listStatistic.SetItem(&lvItem);
    lvItem.iItem = RELAX_DELAYED;
    lvItem.pszText = pst->GetStr(ABOUT_STATISTICS_RELAX_DELAYED);
    m_listStatistic.SetItem(&lvItem);
    lvItem.iItem = RELAX_SKIPPED;
    lvItem.pszText = pst->GetStr(ABOUT_STATISTICS_RELAX_SKIPPED);
    m_listStatistic.SetItem(&lvItem);

    Invalidate(TRUE);
}
