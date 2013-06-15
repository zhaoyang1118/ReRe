# Microsoft Developer Studio Project File - Name="RelaxReminder" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=RelaxReminder - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "RelaxReminder.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "RelaxReminder.mak" CFG="RelaxReminder - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "RelaxReminder - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "RelaxReminder - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "RelaxReminder - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "./PUB" /I "." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 version.lib /nologo /subsystem:windows /machine:I386 /out:"Release/ReRe.exe"
# Begin Special Build Tool
OutDir=.\Release
TargetName=ReRe
SOURCE="$(InputPath)"
PostBuild_Desc=Copying file...
PostBuild_Cmds=mkdir ..\_Output\ReRe 2> nul	copy $(Outdir)\$(TargetName).exe ..\_Output\ReRe > nul	copy language.ini ..\_Output\ReRe > nul
# End Special Build Tool

!ELSEIF  "$(CFG)" == "RelaxReminder - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "./PUB" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 version.lib /nologo /subsystem:windows /debug /machine:I386 /out:"Debug/ReRe.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "RelaxReminder - Win32 Release"
# Name "RelaxReminder - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "DialogOption_CPP"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DialogOption.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogOptionAutoAway.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogOptionLanguage.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogOptionMisc.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogOptionNotify.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogOptionTime.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogSetupWizard.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogSetupWizardWelcome.cpp
# End Source File
# End Group
# Begin Group "Pub_CPP"

# PROP Default_Filter ""
# Begin Source File

SOURCE=PUB\BtnST.cpp
# End Source File
# Begin Source File

SOURCE=PUB\CreditsCtrl.cpp
# End Source File
# Begin Source File

SOURCE=Global.cpp
# End Source File
# Begin Source File

SOURCE=PUB\Ini.cpp
# End Source File
# Begin Source File

SOURCE=PUB\LibFunc.cpp
# End Source File
# Begin Source File

SOURCE=PUB\Log.cpp
# End Source File
# Begin Source File

SOURCE=PUB\PubFunc.cpp
# End Source File
# Begin Source File

SOURCE=.\RelaxTimer.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=PUB/StringTable.cpp
# End Source File
# Begin Source File

SOURCE=PUB\Version.cpp
# End Source File
# End Group
# Begin Group "DialogAbout_CPP"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DialogAbout.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogAboutAbout.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogAboutChangelog.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogAboutDonate.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogAboutStatistics.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogAboutThanks.cpp
# End Source File
# End Group
# Begin Group "Notify_CPP"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DialogDarkerScreen.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogTrayWindow.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\RelaxReminder.cpp
# End Source File
# Begin Source File

SOURCE=.\RelaxReminder.rc
# End Source File
# Begin Source File

SOURCE=.\RelaxReminderDlg.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "DialogOption_H"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DialogOption.h
# End Source File
# Begin Source File

SOURCE=.\DialogOptionAutoAway.h
# End Source File
# Begin Source File

SOURCE=.\DialogOptionLanguage.h
# End Source File
# Begin Source File

SOURCE=.\DialogOptionMisc.h
# End Source File
# Begin Source File

SOURCE=.\DialogOptionNotify.h
# End Source File
# Begin Source File

SOURCE=.\DialogOptionTime.h
# End Source File
# Begin Source File

SOURCE=.\DialogSetupWizard.h
# End Source File
# Begin Source File

SOURCE=.\DialogSetupWizardWelcome.h
# End Source File
# End Group
# Begin Group "Pub_H"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\PUB\BtnST.h
# End Source File
# Begin Source File

SOURCE=..\PUB\CreditsCtrl.h
# End Source File
# Begin Source File

SOURCE=.\DefaultValue.h
# End Source File
# Begin Source File

SOURCE=.\Global.h
# End Source File
# Begin Source File

SOURCE=..\PUB\Ini.h
# End Source File
# Begin Source File

SOURCE=.\LibFunc.h
# End Source File
# Begin Source File

SOURCE=..\PUB\Log.h
# End Source File
# Begin Source File

SOURCE=..\PUB\PubFunc.h
# End Source File
# Begin Source File

SOURCE=.\RelaxTimer.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\StringTable.h
# End Source File
# Begin Source File

SOURCE=..\PUB\Version.h
# End Source File
# End Group
# Begin Group "DialogAbout_H"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DialogAbout.h
# End Source File
# Begin Source File

SOURCE=.\DialogAboutAbout.h
# End Source File
# Begin Source File

SOURCE=.\DialogAboutChangelog.h
# End Source File
# Begin Source File

SOURCE=.\DialogAboutDonate.h
# End Source File
# Begin Source File

SOURCE=.\DialogAboutStatistics.h
# End Source File
# Begin Source File

SOURCE=.\DialogAboutThanks.h
# End Source File
# End Group
# Begin Group "Notify_H"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DialogDarkerScreen.h
# End Source File
# Begin Source File

SOURCE=.\DialogTrayWindow.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\RelaxReminder.h
# End Source File
# Begin Source File

SOURCE=.\RelaxReminderDlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\bmp\alipay.bmp
# End Source File
# Begin Source File

SOURCE=.\res\icon\Icon_Green_01.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon\Icon_Green_02.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon\Icon_Green_03.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon\Icon_Green_04.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon\Icon_Green_05.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon\Icon_Green_06.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon\Icon_Green_07.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon\Icon_Green_08.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon\Icon_Green_09.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon\Icon_Green_10.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon\Icon_Green_11.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon\Icon_Green_12.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon\Icon_Green_13.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon\Icon_Green_14.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon\Icon_Green_15.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon\Icon_Main.ico
# End Source File
# Begin Source File

SOURCE=.\res\bmp\Icon_Main_128x128.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp\Icon_Main_128x128_0.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp\Icon_Main_128x128_1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp\Icon_Main_64x64.bmp
# End Source File
# Begin Source File

SOURCE=.\res\icon\Icon_Pause_01.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon\Icon_Pause_02.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon\Icon_Pause_03.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon\Icon_Pause_04.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon\Icon_Pause_05.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon\Icon_Pause_06.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon\Icon_Pause_07.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon\Icon_Pause_08.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon\Icon_Pause_09.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon\Icon_Pause_10.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon\Icon_Pause_11.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon\Icon_Pause_12.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon\Icon_Pause_13.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon\Icon_Pause_14.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon\Icon_Pause_15.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon\Icon_Red_01.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon\Icon_Red_02.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon\Icon_Red_03.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon\Icon_Red_04.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon\Icon_Red_05.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon\Icon_Red_06.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon\Icon_Red_07.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon\Icon_Red_08.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon\Icon_Red_09.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon\Icon_Red_10.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon\Icon_Red_11.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon\Icon_Red_12.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon\Icon_Red_13.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon\Icon_Red_14.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon\Icon_Red_15.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon\Icon_Reset_01.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon\Icon_Reset_02.ico
# End Source File
# Begin Source File

SOURCE=.\res\bmp\paypal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\RelaxReminder.ico
# End Source File
# Begin Source File

SOURCE=.\res\RelaxReminder.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
