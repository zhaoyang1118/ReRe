#include "StdAfx.h"
#include "PubFunc.h"
#include "Ini.h"
#include "StringTable.h"


#define LoadStringFromIniFile(STRIDX)                           \
{                                                               \
    strncpy(aachStringTable[(STRIDX)],                          \
        (Ini.ReadText(pchLanguage, #STRIDX)),                   \
        STRING_LENGTH);                                         \
}

#define LoadStringDefault(STRIDX, STR)                          \
{                                                               \
    strncpy(aachStringTable[(STRIDX)], (STR), STRING_LENGTH);   \
}


BOOL CStringTable::LoadStringTable(const char *pchLangFile,
                                   const char *pchLanguage)
{
    if (NULL == pchLangFile || NULL == pchLanguage)
    {
        return FALSE;
    }

    if(FileExists(pchLangFile) == -1)
    {// 指定的语言配置文件不存在
        return FALSE;
    }

    // 打开配置文件
    CIni Ini(pchLangFile);
    
    // 先判断指定的语言是否使用
    BOOL bVersionExist = Ini.CheckExist(pchLanguage, "Available");
    if (bVersionExist == FALSE)
    {
        return FALSE;
    }
    if (1 != Ini.ReadInt(pchLanguage, "Available"))
    {
        return FALSE;
    }
    
    memset(aachStringTable, 0x0, sizeof(aachStringTable));

    // 菜单
    LoadStringFromIniFile(MENU_FLOATING_WINDOW);
    LoadStringFromIniFile(MENU_TRAY_ICON);
    LoadStringFromIniFile(MENU_START_WORK);
    LoadStringFromIniFile(MENU_SHORT_RELAX);
    LoadStringFromIniFile(MENU_LONG_RELAX);
    LoadStringFromIniFile(MENU_PAUSE);
    LoadStringFromIniFile(MENU_RESET);
    LoadStringFromIniFile(MENU_OPTION);
    LoadStringFromIniFile(MENU_ABOUT);
    LoadStringFromIniFile(MENU_EXIT);
    
    // 通知栏图标提示
    LoadStringFromIniFile(TRAY_ICON_TIPS_WORK);
    LoadStringFromIniFile(TRAY_ICON_TIPS_SHORT_RELAX);
    LoadStringFromIniFile(TRAY_ICON_TIPS_LONG_RELAX);
    LoadStringFromIniFile(TRAY_ICON_TIPS_PAUSE);

    // OPTION对话框
    LoadStringFromIniFile(OPTION_CAPTION);
    LoadStringFromIniFile(OPTION_BUTTON_RESET);
    LoadStringFromIniFile(OPTION_BUTTON_RESET_TIP);
    LoadStringFromIniFile(OPTION_BUTTON_APPLY);
    LoadStringFromIniFile(OPTION_BUTTON_APPLY_TIP);
    LoadStringFromIniFile(OPTION_BUTTON_SAVE);
    LoadStringFromIniFile(OPTION_BUTTON_SAVE_TIP);
    LoadStringFromIniFile(OPTION_CHECK_FAIL_CAPTION);

    LoadStringFromIniFile(OPTION_PAGE_TIME);
    LoadStringFromIniFile(OPTION_PAGE_NOTIFY);
    LoadStringFromIniFile(OPTION_PAGE_AUTO_AWAY);
    LoadStringFromIniFile(OPTION_PAGE_LANGUAGE);
    LoadStringFromIniFile(OPTION_PAGE_MISC);

    LoadStringFromIniFile(OPTION_TIME_SHORT_RELAX);
    LoadStringFromIniFile(OPTION_TIME_SHORT_RELAX_WD);
    LoadStringFromIniFile(OPTION_TIME_SHORT_RELAX_WD_UNIT);
    LoadStringFromIniFile(OPTION_TIME_SHORT_RELAX_SRD);
    LoadStringFromIniFile(OPTION_TIME_SHORT_RELAX_SRD_UNIT);
    LoadStringFromIniFile(OPTION_TIME_LONG_RELAX);
    LoadStringFromIniFile(OPTION_TIME_LONG_RELAX_LRF);
    LoadStringFromIniFile(OPTION_TIME_LONG_RELAX_LRF_UNIT);
    LoadStringFromIniFile(OPTION_TIME_LONG_RELAX_LRD);
    LoadStringFromIniFile(OPTION_TIME_LONG_RELAX_LRD_UNIT);
    LoadStringFromIniFile(OPTION_TIME_TIPS);
    LoadStringFromIniFile(OPTION_TIME_SETTING_REFERENCE);
    LoadStringFromIniFile(OPTION_TIME_CHECK_FAIL_WORK_DURATION);
    LoadStringFromIniFile(OPTION_TIME_CHECK_FAIL_SHORT_RELAX_DURATION);
    LoadStringFromIniFile(OPTION_TIME_CHECK_FAIL_LONG_RELAX_DURATION);

    LoadStringFromIniFile(OPTION_NOTIFY_PRENOTIFY);
    LoadStringFromIniFile(OPTION_NOTIFY_LOCK_INPUT);
    LoadStringFromIniFile(OPTION_NOTIFY_LOCK_INPUT_KEYBOARD);
    LoadStringFromIniFile(OPTION_NOTIFY_LOCK_INPUT_MOUSE);
    LoadStringFromIniFile(OPTION_NOTIFY_LOCK_INPUT_BOTH);
    LoadStringFromIniFile(OPTION_NOTIFY_SCREEN_MASK);
    LoadStringFromIniFile(OPTION_NOTIFY_SCREEN_MASK_TRANSPARENCY);
    LoadStringFromIniFile(OPTION_NOTIFY_SCREEN_MASK_TRANSPARENCY_TRANSPARENT);
    LoadStringFromIniFile(OPTION_NOTIFY_SCREEN_MASK_TRANSPARENCY_OPAQUE);
    LoadStringFromIniFile(OPTION_NOTIFY_SCREEN_MASK_COLOR);
    LoadStringFromIniFile(OPTION_NOTIFY_SCREEN_MASK_COLOR_BLACK);
    LoadStringFromIniFile(OPTION_NOTIFY_SCREEN_MASK_COLOR_CUSTOM);
    LoadStringFromIniFile(OPTION_NOTIFY_SCREEN_MASK_ANIMATION);
    LoadStringFromIniFile(OPTION_NOTIFY_SCREEN_MASK_ANIMATION_OFF);
    LoadStringFromIniFile(OPTION_NOTIFY_SCREEN_MASK_ANIMATION_FAST);
    LoadStringFromIniFile(OPTION_NOTIFY_SCREEN_MASK_ANIMATION_MEDIUM);
    LoadStringFromIniFile(OPTION_NOTIFY_SCREEN_MASK_ANIMATION_SLOW);
    LoadStringFromIniFile(OPTION_NOTIFY_MULTIMON);
    LoadStringFromIniFile(OPTION_NOTIFY_MULTIMON_DARKER_SCREEN);
    LoadStringFromIniFile(OPTION_NOTIFY_MULTIMON_DARKER_SCREEN_MASTER);
    LoadStringFromIniFile(OPTION_NOTIFY_MULTIMON_DARKER_SCREEN_CURSOR);
    LoadStringFromIniFile(OPTION_NOTIFY_MULTIMON_DARKER_SCREEN_ALL);
    LoadStringFromIniFile(OPTION_NOTIFY_MULTIMON_NOTIFY_WINDOW);
    LoadStringFromIniFile(OPTION_NOTIFY_MULTIMON_NOTIFY_WINDOW_MASTER);
    LoadStringFromIniFile(OPTION_NOTIFY_MULTIMON_NOTIFY_WINDOW_CURSOR);

    LoadStringFromIniFile(OPTION_AUTOAWAY_AUTO_PAUSE);
    LoadStringFromIniFile(OPTION_AUTOAWAY_AUTO_PAUSE_AFTER);
    LoadStringFromIniFile(OPTION_AUTOAWAY_AUTO_PAUSE_IDLE);
    LoadStringFromIniFile(OPTION_AUTOAWAY_AUTO_PAUSE_FULLSCREEN);
    LoadStringFromIniFile(OPTION_AUTOAWAY_AUTO_RESET);
    LoadStringFromIniFile(OPTION_AUTOAWAY_AUTO_RESET_AFTER);
    LoadStringFromIniFile(OPTION_AUTOAWAY_AUTO_RESET_IDLE);
    LoadStringFromIniFile(OPTION_AUTOAWAY_CHECK_FAIL_AUTO_RESET_INTERVAL);

    LoadStringFromIniFile(OPTION_LANGUAGE_SELECT);
    LoadStringFromIniFile(OPTION_LANGUAGE_CHECK_FAIL_UNAVAILABLE);
    LoadStringFromIniFile(OPTION_LANGUAGE_TIPS);

    LoadStringFromIniFile(OPTION_MISC_LOCK_COMPUTER);
    LoadStringFromIniFile(OPTION_MISC_CLOSE_MONITOR);
    LoadStringFromIniFile(OPTION_MISC_SHOW_FLOATING_WINDOW);
    LoadStringFromIniFile(OPTION_MISC_SHOW_TRAY_ICON);
    LoadStringFromIniFile(OPTION_MISC_LOG);
    LoadStringFromIniFile(OPTION_MISC_LOG_LEVEL);
    LoadStringFromIniFile(OPTION_MISC_LOG_FILE_SIZE);
    LoadStringFromIniFile(OPTION_MISC_STARTUP_WITH_WINDOWS);
    LoadStringFromIniFile(OPTION_MISC_CHECK_FAIL_STARTUP_WITH_WINDOWS);

    // ABOUT对话框
    LoadStringFromIniFile(ABOUT_CAPTION);
    LoadStringFromIniFile(ABOUT_PAGE_ABOUT);
    LoadStringFromIniFile(ABOUT_PAGE_THANKS);
    LoadStringFromIniFile(ABOUT_PAGE_CHANGELOG);
    LoadStringFromIniFile(ABOUT_PAGE_STATISTICS);
    LoadStringFromIniFile(ABOUT_PAGE_DONATE);

    LoadStringFromIniFile(ABOUT_ABOUT_DEDICATE);
    LoadStringFromIniFile(ABOUT_ABOUT_APPINFO);
    LoadStringFromIniFile(ABOUT_ABOUT_APPINFO_APPNAME);
    LoadStringFromIniFile(ABOUT_ABOUT_APPINFO_VERSION);

    LoadStringFromIniFile(ABOUT_THANKS_CONTRIBUTERS);
    LoadStringFromIniFile(ABOUT_THANKS_EXTERNALS);

    LoadStringFromIniFile(ABOUT_CHANGELOG_HISTORY);

    LoadStringFromIniFile(ABOUT_STATISTICS_ITEM);
    LoadStringFromIniFile(ABOUT_STATISTICS_COUNTER);
    LoadStringFromIniFile(ABOUT_STATISTICS_RATIO);
    LoadStringFromIniFile(ABOUT_STATISTICS_TIME_HEADLINE);
    LoadStringFromIniFile(ABOUT_STATISTICS_TIME_TOTAL);
    LoadStringFromIniFile(ABOUT_STATISTICS_TIME_WORK);
    LoadStringFromIniFile(ABOUT_STATISTICS_TIME_SRELAX);
    LoadStringFromIniFile(ABOUT_STATISTICS_TIME_LRELAX);
    LoadStringFromIniFile(ABOUT_STATISTICS_TIME_PAUSE);
    LoadStringFromIniFile(ABOUT_STATISTICS_TIME_RESET);
    LoadStringFromIniFile(ABOUT_STATISTICS_RELAX_HEADLINE);
    LoadStringFromIniFile(ABOUT_STATISTICS_RELAX_SRELAX);
    LoadStringFromIniFile(ABOUT_STATISTICS_RELAX_LRELAX);
    LoadStringFromIniFile(ABOUT_STATISTICS_RELAX_DELAYED);
    LoadStringFromIniFile(ABOUT_STATISTICS_RELAX_SKIPPED);

    LoadStringFromIniFile(ABOUT_DONATE_DONATION_APPEAL);
    LoadStringFromIniFile(ABOUT_DONATE_DONATION_LIST_HEADER);
    LoadStringFromIniFile(ABOUT_DONATE_DONATION_TIPS);

    // TrayWindow
    LoadStringFromIniFile(TRAY_WINDOW_CAPTION_NEXT_RELAX);
    LoadStringFromIniFile(TRAY_WINDOW_CAPTION_SHORT_RELAX);
    LoadStringFromIniFile(TRAY_WINDOW_CAPTION_LONG_RELAX);
    LoadStringFromIniFile(TRAY_WINDOW_DELAY);
    LoadStringFromIniFile(TRAY_WINDOW_DELAY_TIPS);
    LoadStringFromIniFile(TRAY_WINDOW_SKIP);
    LoadStringFromIniFile(TRAY_WINDOW_SKIP_TIPS);
    LoadStringFromIniFile(TRAY_WINDOW_HIDE);
    LoadStringFromIniFile(TRAY_WINDOW_HIDE_TIPS);

    StringTableReformat();

    return TRUE;
}

void CStringTable::LoadDefaultString()
{
    memset(aachStringTable, 0x0, sizeof(aachStringTable));
    
    // 菜单
    LoadStringDefault(MENU_FLOATING_WINDOW, "&Floating Window");
    LoadStringDefault(MENU_TRAY_ICON, "System &Tray Icon");
    LoadStringDefault(MENU_START_WORK, "Start &Work");
    LoadStringDefault(MENU_SHORT_RELAX, "&Short Relax");
    LoadStringDefault(MENU_LONG_RELAX, "&Long Relax");
    LoadStringDefault(MENU_PAUSE, "&Pause");
    LoadStringDefault(MENU_RESET, "&Reset");
    LoadStringDefault(MENU_OPTION, "&Option...");
    LoadStringDefault(MENU_ABOUT, "&About...");
    LoadStringDefault(MENU_EXIT, "&Exit");
    
    // 通知栏图标提示
    LoadStringDefault(TRAY_ICON_TIPS_WORK, "Work");
    LoadStringDefault(TRAY_ICON_TIPS_SHORT_RELAX, "Short Relax");
    LoadStringDefault(TRAY_ICON_TIPS_LONG_RELAX, "Long Relax");
    LoadStringDefault(TRAY_ICON_TIPS_PAUSE, "Pause");

    // OPTION对话框
    LoadStringDefault(OPTION_CAPTION, "ReRe (Option)");
    LoadStringDefault(OPTION_BUTTON_RESET, "Reset");
    LoadStringDefault(OPTION_BUTTON_RESET_TIP, "Reset this page to default, settings on other pages are not affected.");
    LoadStringDefault(OPTION_BUTTON_APPLY, "Apply");
    LoadStringDefault(OPTION_BUTTON_APPLY_TIP, "Apply current setting to program, but not save into setting file.");
    LoadStringDefault(OPTION_BUTTON_SAVE, "Save");
    LoadStringDefault(OPTION_BUTTON_SAVE_TIP, "Save current setting into setting file, so that ReRe will load the saved setting at next start.");
    LoadStringDefault(OPTION_CHECK_FAIL_CAPTION, "ReRe Option");

    LoadStringDefault(OPTION_PAGE_TIME, "Time");
    LoadStringDefault(OPTION_PAGE_NOTIFY, "Notify");
    LoadStringDefault(OPTION_PAGE_AUTO_AWAY, "Auto Away");
    LoadStringDefault(OPTION_PAGE_LANGUAGE, "Language");
    LoadStringDefault(OPTION_PAGE_MISC, "Misc");

    LoadStringDefault(OPTION_TIME_SHORT_RELAX, "Short Relax");
    LoadStringDefault(OPTION_TIME_SHORT_RELAX_WD, "Work Duration:");
    LoadStringDefault(OPTION_TIME_SHORT_RELAX_WD_UNIT, "minutes");
    LoadStringDefault(OPTION_TIME_SHORT_RELAX_SRD, "Relax Duration:");
    LoadStringDefault(OPTION_TIME_SHORT_RELAX_SRD_UNIT, "minutes");
    LoadStringDefault(OPTION_TIME_LONG_RELAX, "Long Relax");
    LoadStringDefault(OPTION_TIME_LONG_RELAX_LRF, "Every Short Relax:");
    LoadStringDefault(OPTION_TIME_LONG_RELAX_LRF_UNIT, "times");
    LoadStringDefault(OPTION_TIME_LONG_RELAX_LRD, "Relax Duration:");
    LoadStringDefault(OPTION_TIME_LONG_RELAX_LRD_UNIT, "minutes");
    LoadStringDefault(OPTION_TIME_TIPS, "Tips: Proper setting protects you from Repetitive Strain Injury (RSI).");
    LoadStringDefault(OPTION_TIME_SETTING_REFERENCE, "Setting Reference\n------------------------\n Recommand:\n  Work: 45 minutes\n  Relax: 5 minutes\n------------------------\n Forbid:\n  Work < 5 minutes\n  Relax < 1 minutes\n------------------------");
    LoadStringDefault(OPTION_TIME_CHECK_FAIL_WORK_DURATION, "Work duration should NOT less than 5 minutes.");
    LoadStringDefault(OPTION_TIME_CHECK_FAIL_SHORT_RELAX_DURATION, "Short-relax duration should NOT less than 1 minute.");
    LoadStringDefault(OPTION_TIME_CHECK_FAIL_LONG_RELAX_DURATION, "Long-relax duration should NOT less than short-relax duration.");

    LoadStringDefault(OPTION_NOTIFY_PRENOTIFY, "Pre-Notify    (nofity me 1 minute before relax)");
    LoadStringDefault(OPTION_NOTIFY_LOCK_INPUT, "Lock Input    (disable keyboard or mouse during relax)");
    LoadStringDefault(OPTION_NOTIFY_LOCK_INPUT_KEYBOARD, "Keyboard");
    LoadStringDefault(OPTION_NOTIFY_LOCK_INPUT_MOUSE, "Mouse");
    LoadStringDefault(OPTION_NOTIFY_LOCK_INPUT_BOTH, "Both (Recommand)");
    LoadStringDefault(OPTION_NOTIFY_SCREEN_MASK, "Screen Mask     (show screen mask during relax)");
    LoadStringDefault(OPTION_NOTIFY_SCREEN_MASK_TRANSPARENCY, "Transparency");
    LoadStringDefault(OPTION_NOTIFY_SCREEN_MASK_TRANSPARENCY_TRANSPARENT, "transparent");
    LoadStringDefault(OPTION_NOTIFY_SCREEN_MASK_TRANSPARENCY_OPAQUE, "opaque");
    LoadStringDefault(OPTION_NOTIFY_SCREEN_MASK_COLOR, "Color");
    LoadStringDefault(OPTION_NOTIFY_SCREEN_MASK_COLOR_BLACK, "Black");
    LoadStringDefault(OPTION_NOTIFY_SCREEN_MASK_COLOR_CUSTOM, "Custom");
    LoadStringDefault(OPTION_NOTIFY_SCREEN_MASK_ANIMATION, "Animation");
    LoadStringDefault(OPTION_NOTIFY_SCREEN_MASK_ANIMATION_OFF, "Off");
    LoadStringDefault(OPTION_NOTIFY_SCREEN_MASK_ANIMATION_FAST, "Fast");
    LoadStringDefault(OPTION_NOTIFY_SCREEN_MASK_ANIMATION_MEDIUM, "Medium");
    LoadStringDefault(OPTION_NOTIFY_SCREEN_MASK_ANIMATION_SLOW, "Slow");
    LoadStringDefault(OPTION_NOTIFY_MULTIMON, "Multi-Monitor");
    LoadStringDefault(OPTION_NOTIFY_MULTIMON_DARKER_SCREEN, "Screen Mask");
    LoadStringDefault(OPTION_NOTIFY_MULTIMON_DARKER_SCREEN_MASTER, "Master monitor only");
    LoadStringDefault(OPTION_NOTIFY_MULTIMON_DARKER_SCREEN_CURSOR, "Cursor monitor only");
    LoadStringDefault(OPTION_NOTIFY_MULTIMON_DARKER_SCREEN_ALL, "All monitors");
    LoadStringDefault(OPTION_NOTIFY_MULTIMON_NOTIFY_WINDOW, "Notify Window");
    LoadStringDefault(OPTION_NOTIFY_MULTIMON_NOTIFY_WINDOW_MASTER, "Master monitor only");
    LoadStringDefault(OPTION_NOTIFY_MULTIMON_NOTIFY_WINDOW_CURSOR, "Cursor monitor only");

    LoadStringDefault(OPTION_AUTOAWAY_AUTO_PAUSE, "Auto-Pause");
    LoadStringDefault(OPTION_AUTOAWAY_AUTO_PAUSE_AFTER, "After");
    LoadStringDefault(OPTION_AUTOAWAY_AUTO_PAUSE_IDLE, "minutes idle");
    LoadStringDefault(OPTION_AUTOAWAY_AUTO_PAUSE_FULLSCREEN, "When fullscreen mode (eg: movie, game)");
    LoadStringDefault(OPTION_AUTOAWAY_AUTO_RESET, "Auto-Reset");
    LoadStringDefault(OPTION_AUTOAWAY_AUTO_RESET_AFTER, "After");
    LoadStringDefault(OPTION_AUTOAWAY_AUTO_RESET_IDLE, "minutes idle");
    LoadStringDefault(OPTION_AUTOAWAY_CHECK_FAIL_AUTO_RESET_INTERVAL, "Auto-Reset timer should NOT less than Auto-Pause timer.");

    LoadStringDefault(OPTION_LANGUAGE_SELECT, "Select Language for ReRe");
    LoadStringDefault(OPTION_LANGUAGE_CHECK_FAIL_UNAVAILABLE, "Selected language unavailable!\n\nPlease select another language with available flag(*).");
    LoadStringDefault(OPTION_LANGUAGE_TIPS, "New languages can be added by modifying the <language.ini> file.");

    LoadStringDefault(OPTION_MISC_LOCK_COMPUTER, "Lock computer after 17-second relax");
    LoadStringDefault(OPTION_MISC_CLOSE_MONITOR, "Close monitor after 20-second relax");
    LoadStringDefault(OPTION_MISC_SHOW_FLOATING_WINDOW, "Show floating window at program startup");
    LoadStringDefault(OPTION_MISC_SHOW_TRAY_ICON, "Show system tray icon at program startup");
    LoadStringDefault(OPTION_MISC_LOG, "Enable event logging");
    LoadStringDefault(OPTION_MISC_LOG_LEVEL, "Log level");
    LoadStringDefault(OPTION_MISC_LOG_FILE_SIZE, "Split file size");
    LoadStringDefault(OPTION_MISC_STARTUP_WITH_WINDOWS, "Startup with Windows  (Note: add an item in registry!)");
    LoadStringDefault(OPTION_MISC_CHECK_FAIL_STARTUP_WITH_WINDOWS, "Registry Access Denied!\n\n\"Startup with Windows\" try to add an item in Registry.\nThis operation may be denied by some anti-virus software.\nMake sure that the anti-virus software allows the Registry operation!");

    // ABOUT对话框
    LoadStringDefault(ABOUT_CAPTION, "ReRe (About)");
    LoadStringDefault(ABOUT_PAGE_ABOUT, "About");
    LoadStringDefault(ABOUT_PAGE_THANKS, "Thanks");
    LoadStringDefault(ABOUT_PAGE_CHANGELOG, "Changelog");
    LoadStringDefault(ABOUT_PAGE_STATISTICS, "Statistics");
    LoadStringDefault(ABOUT_PAGE_DONATE, "Donate");

    LoadStringDefault(ABOUT_ABOUT_DEDICATE, "Dedicated to");
    LoadStringDefault(ABOUT_ABOUT_APPINFO, "[ Application Info ]");
    LoadStringDefault(ABOUT_ABOUT_APPINFO_APPNAME, "ReRe (Relax Reminder)");
    LoadStringDefault(ABOUT_ABOUT_APPINFO_VERSION, "version");

    LoadStringDefault(ABOUT_THANKS_CONTRIBUTERS, "[ Many thanks to the contributers ]");
    LoadStringDefault(ABOUT_THANKS_EXTERNALS, "[ Special thanks to the external codes and libraries ]");

    LoadStringDefault(ABOUT_CHANGELOG_HISTORY, "[ A brief history of ReRe ]");

    LoadStringDefault(ABOUT_STATISTICS_ITEM, "ITEM");
    LoadStringDefault(ABOUT_STATISTICS_COUNTER, "COUNTER");
    LoadStringDefault(ABOUT_STATISTICS_RATIO, "RATIO");
    LoadStringDefault(ABOUT_STATISTICS_TIME_HEADLINE, "[ Time Statistic ]");
    LoadStringDefault(ABOUT_STATISTICS_TIME_TOTAL, "Total");
    LoadStringDefault(ABOUT_STATISTICS_TIME_WORK, "Work");
    LoadStringDefault(ABOUT_STATISTICS_TIME_SRELAX, "Short Relax");
    LoadStringDefault(ABOUT_STATISTICS_TIME_LRELAX, "Long Relax");
    LoadStringDefault(ABOUT_STATISTICS_TIME_PAUSE, "Pause");
    LoadStringDefault(ABOUT_STATISTICS_TIME_RESET, "Reset");
    LoadStringDefault(ABOUT_STATISTICS_RELAX_HEADLINE, "[ Relax Statistic ]");
    LoadStringDefault(ABOUT_STATISTICS_RELAX_SRELAX, "Short Relax");
    LoadStringDefault(ABOUT_STATISTICS_RELAX_LRELAX, "Long Relax");
    LoadStringDefault(ABOUT_STATISTICS_RELAX_DELAYED, "Relax Delayed");
    LoadStringDefault(ABOUT_STATISTICS_RELAX_SKIPPED, "Relax Skipped");
    
    LoadStringDefault(ABOUT_DONATE_DONATION_APPEAL, "ReRe needs your donation for further development!");
    LoadStringDefault(ABOUT_DONATE_DONATION_LIST_HEADER, "Donation List");
    LoadStringDefault(ABOUT_DONATE_DONATION_TIPS, "You could send donation to the below account via the two online payment services on the right.");

    // TrayWindow
    LoadStringDefault(TRAY_WINDOW_CAPTION_NEXT_RELAX, "NEXT\nRELAX");
    LoadStringDefault(TRAY_WINDOW_CAPTION_SHORT_RELAX, "SHORT\nRELAX");
    LoadStringDefault(TRAY_WINDOW_CAPTION_LONG_RELAX, "LONG\nRELAX");
    LoadStringDefault(TRAY_WINDOW_DELAY, "Delay");
    LoadStringDefault(TRAY_WINDOW_DELAY_TIPS, "Delay relax, give me 5 more minutes.");
    LoadStringDefault(TRAY_WINDOW_SKIP, "Skip");
    LoadStringDefault(TRAY_WINDOW_SKIP_TIPS, "Skip relax this time, start next work duration.");
    LoadStringDefault(TRAY_WINDOW_HIDE, "Hide");
    LoadStringDefault(TRAY_WINDOW_HIDE_TIPS, "Hide this notification bar.");

    StringTableReformat();
}

void CStringTable::StringTableReformat()
{
    for (int idx = STRING_INDEX_FIRST; idx <= STRING_INDEX_LAST; idx++)
    {
        CString str;
        str = GetStr((StrIdx)idx);
        str.Replace("\\n", "\n");
        strncpy(aachStringTable[idx], str, STRING_LENGTH);
    }
}

char* CStringTable::GetStr(StrIdx eIndex)
{
    return aachStringTable[eIndex];
}
