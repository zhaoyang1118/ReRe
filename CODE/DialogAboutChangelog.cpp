// DialogAboutChangelog.cpp : implementation file
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
#include "DialogAboutChangelog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define ADD_HEADLINE(VERSION, DESC)                 \
{                                                   \
    strChangelog += FmtVersion + VERSION;           \
    strChangelog += FmtDesc + "        " + DESC +   \
                    FmtLineEnd + FmtEnd + FmtEnd;   \
}

#define ADD_ITEM(DESC)                                                  \
{                                                                       \
    strChangelog += FmtItem + "   - " + DESC + FmtLineEnd + FmtEnd;   \
}


/////////////////////////////////////////////////////////////////////////////
// CDialogAboutChangelog dialog


CDialogAboutChangelog::CDialogAboutChangelog(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogAboutChangelog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogAboutChangelog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDialogAboutChangelog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogAboutChangelog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogAboutChangelog, CDialog)
	//{{AFX_MSG_MAP(CDialogAboutChangelog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogAboutChangelog message handlers

BOOL CDialogAboutChangelog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    CString FmtVersion  = "<font align='left' size='12' style='b'>";
    CString FmtDesc     = "<font size='11' style='-b'>";
    CString FmtItem     = "<font align='left' size='11'>";
    CString FmtEnd      = "</font>";
    CString FmtLineEnd  = "<br>";
    CString strChangelog;
    
    strChangelog.Empty();
    ADD_HEADLINE("ReRe 0.8.4", "2013-6-15");
    ADD_ITEM("[ADD] Add multi-monitor support.");
    ADD_ITEM("[ADD] Add configurable grace time before locking input.");
    ADD_ITEM("[DEL] Remove plugins support.");

    ADD_HEADLINE("ReRe 0.8.3", "2012-8-26");
    ADD_ITEM("[ADD] Add welcome page as the first page of setup wizard.");
    ADD_ITEM("[FIX] Fix program crashing caused by unclosed plugins exiting.");

    ADD_HEADLINE("ReRe 0.8.2", "2012-2-02");
    ADD_ITEM("[ADD] Show setup wizard for first execution.");
    ADD_ITEM("[ADD] Add official website link.");

    ADD_HEADLINE("ReRe 0.8.1", "2012-1-02");
    ADD_ITEM("[FIX] Fix some minor bugs.");

    ADD_HEADLINE("ReRe 0.8", "2011-12-23");
    ADD_ITEM("[FIX] Fix minor bug of language display.");
    ADD_ITEM("[ADD] Support donate && free license.");
    ADD_ITEM("[MOD] Change tab style of \"About\" window.");
    ADD_ITEM("[MOD] Change tab style of \"Option\" window.");
    ADD_ITEM("[MOD] Optimize plugins manager.");
    ADD_ITEM("[ADD] Tray window position auto fit.");

    ADD_HEADLINE("ReRe 0.7.14", "2011-12-05");
    ADD_ITEM("[ADD] Add multiply-language support.");
    ADD_ITEM("[ADD] Add tooltips for Option window && Plugin Manager window.");
    ADD_ITEM("[ADD] Floating window auto size.");
    ADD_ITEM("[ADD] Extend tray window mouse approaching time.");
    ADD_ITEM("[FIX] Fix screen mask close fail.");
    ADD_ITEM("[ADD] Add changelog in the about dialog.");
    ADD_ITEM("[MOD] Official website links change to e-mail address.");
    ADD_ITEM("[FIX] Modify tray window transparency when cursor approaching.");
    ADD_ITEM("[FIX] Fix unnecessary update when floating window invisible.");
    ADD_ITEM("[ADD] Auto hide floating window when fullscreen mode detected.");

    ADD_HEADLINE("ReRe 0.7.13", "2011-11-11");
    ADD_ITEM("[ADD] Add options for floating window && system tray icon.");
    ADD_ITEM("[ADD] Add show/hide system tray icon in the right menu.");
    ADD_ITEM("[FIX] Show stop message when another ReRe instance started.");
    ADD_ITEM("[FIX] Fix the missing colon in the tooltips of system tray icon.");
    ADD_ITEM("[ADD] add right click menu on floating window && tray window.");
    ADD_ITEM("[ADD] Enable choosing screen mask color in the color dialog.");
    ADD_ITEM("[ADD] Make floating window movable when detect cursor hover.");
    ADD_ITEM("[FIX] Fix control status error in the screen mask option dialog.");
    ADD_ITEM("[FIX] Modify the font color of floating window.");
   
    ADD_HEADLINE("ReRe 0.7.12", "2011-11-08");
    ADD_ITEM("[ADD] Enable auto pause when fullscreen mode detected.");
    ADD_ITEM("[FIX] Modify main window to floating window.");
    ADD_ITEM("[FIX] Modify the acknowledge with CCreditsCtrl.");
    ADD_ITEM("[FIX] Add acknowledge to zlib library && zlib.net.");
    ADD_ITEM("[ADD] Make tray window more transparent when cursor approaching.");
    ADD_ITEM("[FIX] Fix cursor hover detecting time invalid.");
    ADD_ITEM("[FIX] Fix program crash caused by null pointer.");

    ADD_HEADLINE("ReRe 0.7.11", "2011-10-30");
    ADD_ITEM("[ADD] Make tray window more transparent when cursor hover.");
    ADD_ITEM("[ADD] Add tooltips for the buttons on the tray window.");
    ADD_ITEM("[FIX] Child dialog(eg: option, about) multiple instance forbid.");
    ADD_ITEM("[FIX] Reduce the size of tray window.");
    ADD_ITEM("[FIX] Update the registration code after loading license file.");
    ADD_ITEM("[FIX] Fix the file operation error when reading a 0xff.");
    
    ADD_HEADLINE("ReRe 0.7.10", "2011-10-01");
    ADD_ITEM("[ADD] Add color choice for screen mask.");
    ADD_ITEM("[ADD] Add animation for screen mask.");
    ADD_ITEM("[FIX] Fix path error when license file copy.");
    
    ADD_HEADLINE("ReRe 0.7.9", "2011-09-23");
    ADD_ITEM("[FIX] Fix license file codec error.");
    ADD_ITEM("[FIX] Replace MoveFile with MoveFileEx function call.");
    ADD_ITEM("[ADD] Add license file codec.");
    ADD_ITEM("[FIX] Show tray window && screen mask without activation.");
    ADD_ITEM("[ADD] Plugins get version info from the dll file directly.");
    ADD_ITEM("[FIX] Fix log print error.");
    ADD_ITEM("[FIX] Modify registration level control.");
    ADD_ITEM("[FIX] Fix log file size control error.");

    ADD_HEADLINE("ReRe 0.7.8", "2011-07-17");
    ADD_ITEM("[ADD] Auto fit for screen resolution change.");
    ADD_ITEM("[FIX] Fix evaluation error.");
    ADD_ITEM("[FIX] Copy license file when loading license success.");
    ADD_ITEM("[ADD] Add operation log print.");
    
    ADD_HEADLINE("ReRe 0.7.7", "2011-07-10");
    ADD_ITEM("[ADD] Add option of startup with window.");
    ADD_ITEM("[FIX] Enable startup log cache.");
    ADD_ITEM("[ADD] Add option of logging.");
    ADD_ITEM("[FIX] Fix dialog crash when close option dialog.");

    ADD_HEADLINE("ReRe 0.7.6", "2011-06-28");
    ADD_ITEM("[FIX] Fix close tray window && screen mask imcompletely.");
    ADD_ITEM("[ADD] Enable log print.");
    ADD_ITEM("[FIX] Fix registration info error.");
    ADD_ITEM("[FIX] Fix screen mask.");
    ADD_ITEM("[FIX] Optimize plugin manager dialog.");

    ADD_HEADLINE("ReRe 0.7.5", "2010-06-14");
    ADD_ITEM("[FIX] Ini file version auto fit.");
    ADD_ITEM("[FIX] Enable ini file read/write mutex.");
    ADD_ITEM("[ADD] Add screen mask.");
    ADD_ITEM("[FIX] Statistic info auto save every 10 minutes.");
    
    ADD_HEADLINE("ReRe 0.7.4", "2010-01-29");
    ADD_ITEM("[FIX] Fix timer display error.");
    ADD_ITEM("[FIX] Fix timer status changing error.");
    ADD_ITEM("[FIX] Fix auto reset process error.");
    
    ADD_HEADLINE("ReRe 0.7.3", "2009-12-27");
    ADD_ITEM("[ADD] Add input lock type option when relaxation.");
    
    ADD_HEADLINE("ReRe 0.7.2", "2009-10-24");
    ADD_ITEM("[ADD] Add ReRe.exe file path and http link in about dialog.");
    ADD_ITEM("[FIX] Optimize plugin manager dialog.");

    ADD_HEADLINE("ReRe 0.7.1", "2009-10-19");
    ADD_ITEM("[FIX] Fix null pointer of about dialog.");
    
    ADD_HEADLINE("ReRe 0.7", "2009-10-16");
    ADD_ITEM("[ADD] Add tabs in about dialog.");
    ADD_ITEM("[ADD] Add plugin platform support.");
    ADD_ITEM("[ADD] Add registration control.");
    ADD_ITEM("[FIX] Fix statistic error when relax delayed.");
    
    ADD_HEADLINE("ReRe 0.6", "2009-08-07");
    ADD_ITEM("[FIX] Fix loading ini file error.");
    ADD_ITEM("[FIX] Release input lock when reset.");
    ADD_ITEM("[FIX] Uninstall keyboard && mouse hook when program exit.");

    ADD_HEADLINE("ReRe 0.5", "refactor, 2009-06-29");
    ADD_ITEM("[ADD] Add option dialog.");
    ADD_ITEM("[ADD] Enable main window color scheme.");
    ADD_ITEM("[FIX] Code refactor.");
    
    ADD_HEADLINE("ReRe 0.4", "2009-05-24");
    ADD_ITEM("[ADD] Modify font of acknowledge && http link.");
    ADD_ITEM("[FIX] Modify ini file structure.");
    
    ADD_HEADLINE("ReRe 0.3", "2009-05-18");
    ADD_ITEM("[ADD] Add option of close monitor after relaxation start.");
    ADD_ITEM("[FIX] Modify some option tips.");
    
    ADD_HEADLINE("ReRe 0.2", "2009-05-10");
    ADD_ITEM("[ADD] Add option of pre-notify.");
    ADD_ITEM("[ADD] Add option of auto pause && auto reset.");
    ADD_ITEM("[ADD] Add some right click menu items.");
    
    ADD_HEADLINE("ReRe 0.1", "first edition, 2009-04-25");
    ADD_ITEM("[ADD] Add basic countdown timer.");
    ADD_ITEM("[ADD] Add options of input lock.");
    ADD_ITEM("[ADD] Add system tray icon.");
    ADD_ITEM("[ADD] Add ini setting file support.");

    // padding
    strChangelog += FmtLineEnd + FmtLineEnd + FmtLineEnd + FmtLineEnd +
                    FmtLineEnd + FmtLineEnd + FmtLineEnd + FmtLineEnd +
                    FmtLineEnd + FmtLineEnd + FmtLineEnd + FmtLineEnd;

    m_wndChangelog.FormatDataString(strChangelog);
    m_wndChangelog.m_crInternalTransparentColor = GetSysColor(COLOR_3DFACE);
    m_wndChangelog.m_nTimerSpeed = 25;
    m_wndChangelog.Create(0, WS_VISIBLE | WS_CHILD, IDC_STATIC_CHANGELOG,
        this, 0, 0, 0);

    LoadLanguageStrings();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialogAboutChangelog::LoadLanguageStrings()
{
    CStringTable *pst = &(m_pdlgMain->m_str);
    
    SetDlgItemText(IDC_STATIC_HISTORY, pst->GetStr(ABOUT_CHANGELOG_HISTORY));

    Invalidate(TRUE);
}
