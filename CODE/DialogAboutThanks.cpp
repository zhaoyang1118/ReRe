// DialogAboutThanks.cpp : implementation file
//

#include "stdafx.h"
#include "RelaxReminder.h"
#include "PubFunc.h"
#include "CreditsCtrl.h"
#include "StringTable.h"
#include "RelaxTimer.h"
#include "DialogTrayWindow.h"
#include "DialogDarkerScreen.h"
#include "RelaxReminderDlg.h"
#include "DialogAboutThanks.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define ADD_CTBTER(NAME, DESC)                      \
{                                                   \
    strCtbter += FmtName + NAME;                    \
    strCtbter += FmtDesc + "        " + DESC        \
                 + FmtLineEnd + FmtEnd + FmtEnd;    \
}

#define ADD_EXTCTBTER(NAME, AUTHOR, LINK)                           \
{                                                                   \
    strExtCtbter += FmtName + NAME + FmtLineEnd + FmtEnd;           \
    strExtCtbter += FmtAuthor + "  " + AUTHOR + "    ";             \
    strExtCtbter += "<font color='0,0,255'><a href='";              \
    strExtCtbter += LINK;                                           \
    strExtCtbter += "' color='0,0,255' style='u'>";                 \
    strExtCtbter += LINK;                                           \
    strExtCtbter += "</a><br></font></font>";                       \
}


/////////////////////////////////////////////////////////////////////////////
// CDialogAboutThanks dialog


CDialogAboutThanks::CDialogAboutThanks(CWnd* pParent /*=NULL*/)
    : CDialog(CDialogAboutThanks::IDD, pParent)
{
    //{{AFX_DATA_INIT(CDialogAboutThanks)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
}


void CDialogAboutThanks::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDialogAboutThanks)
        // NOTE: the ClassWizard will add DDX and DDV calls here
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogAboutThanks, CDialog)
    //{{AFX_MSG_MAP(CDialogAboutThanks)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogAboutThanks message handlers

BOOL CDialogAboutThanks::OnInitDialog() 
{
    CDialog::OnInitDialog();
    
    // TODO: Add extra initialization here
    // 设置致谢人员文字
    CString FmtName     = "<font align='left' size='12' style='b'>";
    CString FmtDesc     = "<font size='11' style='-b'>";
    CString FmtAuthor   = "<font align='left' size='11'>";
    CString FmtEnd      = "</font>";
    CString FmtLineEnd  = "<br>";
    CString strCtbter, strExtCtbter;

    strCtbter.Empty();
    ADD_CTBTER("ZHU Shutian (朱书恬)", "main tester, features proposal");
    ADD_CTBTER("Honey Sophie (张江曼)", "features proposal");
    ADD_CTBTER("FANG Li (方丽)", "features proposal");
    strCtbter += FmtLineEnd + FmtLineEnd + FmtLineEnd + FmtLineEnd + FmtLineEnd;    // padding

    m_wndCtbter.FormatDataString(strCtbter);
    m_wndCtbter.m_crInternalTransparentColor = GetSysColor(COLOR_3DFACE);
    m_wndCtbter.m_nTimerSpeed = 60;
    m_wndCtbter.Create(0, WS_VISIBLE | WS_CHILD, IDC_STATIC_CONTRIBUTERS,
                       this, 0, 0, 0);

    // 设置致谢外部引用
    strExtCtbter.Empty();
    ADD_EXTCTBTER("CButtonST - A fully featured button",
                  "Davide Calabro'",
                  "http://www.softechsoftware.it");
    ADD_EXTCTBTER("CCreditsCtrl - An advanced About Box",
                  "Marc Richarme",
                  "http://www.codeproject.com/KB/dialog/ccreditsctrl.aspx");
    strExtCtbter += FmtLineEnd + FmtLineEnd + FmtLineEnd;   // padding

    m_wndExtCtbter.FormatDataString(strExtCtbter);
    m_wndExtCtbter.m_crInternalTransparentColor = GetSysColor(COLOR_3DFACE);
    m_wndExtCtbter.m_nTimerSpeed = 80;
    m_wndExtCtbter.Create(0, WS_VISIBLE | WS_CHILD,
                          IDC_STATIC_EXTERNAL_CONTRIBUTERS,
                          this, 0, 0, 0);

    LoadLanguageStrings();

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialogAboutThanks::LoadLanguageStrings()
{
    CStringTable *pst;
    
    pst = &(m_pdlgMain->m_str);
    SetDlgItemText(IDC_STATIC_CONTAINER_CONTRIBUTERS, pst->GetStr(ABOUT_THANKS_CONTRIBUTERS));
    SetDlgItemText(IDC_STATIC_CONTAINER_EXTERNALS, pst->GetStr(ABOUT_THANKS_EXTERNALS));
    Invalidate(TRUE);
}