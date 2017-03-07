# Microsoft Developer Studio Project File - Name="CHManager" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=CHManager - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "CHManager.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "CHManager.mak" CFG="CHManager - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CHManager - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "CHManager - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/Deportes/CH/CHManager", TGSCAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "CHManager - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "_UNICODE" /D "NOMINMAX" /D "_RWCONFIG_4d" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 GraphicsDll.lib tls4d.lib dbt4d.lib flags.lib gMngtModel.lib GManagerInterface.lib CHMngtModel.lib CHVMngtModel.lib thspmngtmodel.lib gthmngtmodel.lib guisports.lib guithsports.lib VMngtModel.lib THVMngtModel.lib Persistence.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "CHManager - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "_UNICODE" /D "NOMINMAX" /D "_RWCONFIG_7d" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 GraphicsDlld.lib tls7d.lib dbt7d.lib flags.lib gMngtModeld.lib GManagerInterfaced.lib CHMngtModeld.lib CHVMngtModeld.lib thspmngtmodeld.lib gthmngtmodeld.lib guisportsd.lib guithsportsd.lib VMngtModeld.lib THVMngtModeld.lib Persistenced.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /debug /machine:I386 /out:"Debug/CHManagerd.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "CHManager - Win32 Release"
# Name "CHManager - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CHCnfgDisciplineFormView.cpp
# End Source File
# Begin Source File

SOURCE=.\CHCnfgEventsFormView.cpp
# End Source File
# Begin Source File

SOURCE=.\CHCnfgMatchJudgeDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CHCnfgTeamMembersDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CHCnfgTeamSchedule.cpp
# End Source File
# Begin Source File

SOURCE=.\CHEvenControlOperations.cpp
# End Source File
# Begin Source File

SOURCE=.\CHEventCnfgGUIExtPhases.cpp
# End Source File
# Begin Source File

SOURCE=.\CHEventCnfgGUIExtRank.cpp
# End Source File
# Begin Source File

SOURCE=.\CHEventCnfgGUIExtRating.cpp
# End Source File
# Begin Source File

SOURCE=.\CHEventControlFormView.cpp
# End Source File
# Begin Source File

SOURCE=.\CHEventControlMoveManager.cpp
# End Source File
# Begin Source File

SOURCE=.\CHEventControlMultiScrollBar.cpp
# End Source File
# Begin Source File

SOURCE=.\CHEventControlSquare.cpp
# End Source File
# Begin Source File

SOURCE=.\CHEventControlTable.cpp
# End Source File
# Begin Source File

SOURCE=.\CHFideInformationDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CHFinalStandingsDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CHInscriptionFormView.cpp
# End Source File
# Begin Source File

SOURCE=.\CHJudgesDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CHManager.cpp
# End Source File
# Begin Source File

SOURCE=.\CHManager.rc
# End Source File
# Begin Source File

SOURCE=.\CHManualEventControl.cpp
# End Source File
# Begin Source File

SOURCE=.\CHMasterTypeDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CHMatchVisorFormView.cpp
# End Source File
# Begin Source File

SOURCE=.\CHNARegisterFormView.cpp
# End Source File
# Begin Source File

SOURCE=.\CHPasswordDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CHPgnMatchesDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CHPhasesDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CHProgression.cpp
# End Source File
# Begin Source File

SOURCE=.\CHProgressionFormView.cpp
# End Source File
# Begin Source File

SOURCE=.\CHRanking.cpp
# End Source File
# Begin Source File

SOURCE=.\CHReadFile.cpp
# End Source File
# Begin Source File

SOURCE=.\CHScheduleFormView.cpp
# End Source File
# Begin Source File

SOURCE=.\CHStatusDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CHStatusManager.cpp
# End Source File
# Begin Source File

SOURCE=.\CHTeamCompCnfg.cpp
# End Source File
# Begin Source File

SOURCE=.\CHTeamResults.cpp
# End Source File
# Begin Source File

SOURCE=.\CHTreatPhases.cpp
# End Source File
# Begin Source File

SOURCE=.\CHTreatPools.cpp
# End Source File
# Begin Source File

SOURCE=.\CHTreatSession.cpp
# End Source File
# Begin Source File

SOURCE=.\stdafx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CHCnfgDisciplineFormView.h
# End Source File
# Begin Source File

SOURCE=.\CHCnfgEventsFormView.h
# End Source File
# Begin Source File

SOURCE=.\CHCnfgMatchJudgeDlg.h
# End Source File
# Begin Source File

SOURCE=.\CHCnfgTeamMembersDlg.h
# End Source File
# Begin Source File

SOURCE=.\CHCnfgTeamSchedule.h
# End Source File
# Begin Source File

SOURCE=.\CHDefines.h
# End Source File
# Begin Source File

SOURCE=.\CHEvenControlOperations.h
# End Source File
# Begin Source File

SOURCE=.\CHEventCnfgGUIExtPhases.h
# End Source File
# Begin Source File

SOURCE=.\CHEventCnfgGUIExtRank.h
# End Source File
# Begin Source File

SOURCE=.\CHEventCnfgGUIExtRating.h
# End Source File
# Begin Source File

SOURCE=.\CHEventControlFormView.h
# End Source File
# Begin Source File

SOURCE=.\CHEventControlMoveManager.h
# End Source File
# Begin Source File

SOURCE=.\CHEventControlMultiScrollBar.h
# End Source File
# Begin Source File

SOURCE=.\CHEventControlSquare.h
# End Source File
# Begin Source File

SOURCE=.\CHEventControlTable.h
# End Source File
# Begin Source File

SOURCE=.\CHFideInformationDlg.h
# End Source File
# Begin Source File

SOURCE=.\CHFinalStandingsDlg.h
# End Source File
# Begin Source File

SOURCE=.\CHInscriptionFormView.h
# End Source File
# Begin Source File

SOURCE=.\CHJudgesDlg.h
# End Source File
# Begin Source File

SOURCE=.\CHManager.h
# End Source File
# Begin Source File

SOURCE=.\CHManualEventControl.h
# End Source File
# Begin Source File

SOURCE=.\CHMasterTypeDlg.h
# End Source File
# Begin Source File

SOURCE=.\CHMatchVisorFormView.h
# End Source File
# Begin Source File

SOURCE=.\CHMsgDefines.h
# End Source File
# Begin Source File

SOURCE=.\CHNARegisterFormView.h
# End Source File
# Begin Source File

SOURCE=.\CHPasswordDlg.h
# End Source File
# Begin Source File

SOURCE=.\CHPgnMatchesDlg.h
# End Source File
# Begin Source File

SOURCE=.\CHPhasesDlg.h
# End Source File
# Begin Source File

SOURCE=.\CHProgression.h
# End Source File
# Begin Source File

SOURCE=.\CHProgressionFormView.h
# End Source File
# Begin Source File

SOURCE=.\CHRanking.h
# End Source File
# Begin Source File

SOURCE=.\CHReadFile.h
# End Source File
# Begin Source File

SOURCE=.\CHScheduleFormView.h
# End Source File
# Begin Source File

SOURCE=.\CHStatusDlg.h
# End Source File
# Begin Source File

SOURCE=.\CHStatusManager.h
# End Source File
# Begin Source File

SOURCE=.\CHTeamCompCnfg.h
# End Source File
# Begin Source File

SOURCE=.\CHTeamResults.h
# End Source File
# Begin Source File

SOURCE=.\CHTreatPhases.h
# End Source File
# Begin Source File

SOURCE=.\CHTreatPools.h
# End Source File
# Begin Source File

SOURCE=.\CHTreatSession.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\stdafx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\b15o.bmp
# End Source File
# Begin Source File

SOURCE=.\res\b15s.bmp
# End Source File
# Begin Source File

SOURCE=.\res\b21o.bmp
# End Source File
# Begin Source File

SOURCE=.\res\b21s.bmp
# End Source File
# Begin Source File

SOURCE=.\res\backbrown2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\backBrown3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Black_Pawn.bmp
# End Source File
# Begin Source File

SOURCE=.\res\blue_line_black.bmp
# End Source File
# Begin Source File

SOURCE=.\res\blue_line_white.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp_back.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp_background.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BMP_BEFORE.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BMP_Black.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp_check.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BMP_NEXT.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BMP_POINT.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp_save.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BMP_Send_FIDE.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp_uncheck.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp_validate.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BMP_White.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bronze.bmp
# End Source File
# Begin Source File

SOURCE=.\res\chess_back.bmp
# End Source File
# Begin Source File

SOURCE=.\res\chess_logo.bmp
# End Source File
# Begin Source File

SOURCE=.\res\down.bmp
# End Source File
# Begin Source File

SOURCE=.\res\findMatch.bmp
# End Source File
# Begin Source File

SOURCE=.\res\green_select_black.bmp
# End Source File
# Begin Source File

SOURCE=.\res\green_select_white.bmp
# End Source File
# Begin Source File

SOURCE=.\idr_main.ico
# End Source File
# Begin Source File

SOURCE=.\res\k15o.bmp
# End Source File
# Begin Source File

SOURCE=.\res\k15s.bmp
# End Source File
# Begin Source File

SOURCE=.\res\k21o.bmp
# End Source File
# Begin Source File

SOURCE=.\res\k21s.bmp
# End Source File
# Begin Source File

SOURCE=.\res\MemberRight.bmp
# End Source File
# Begin Source File

SOURCE=.\res\n15o.bmp
# End Source File
# Begin Source File

SOURCE=.\res\n15s.bmp
# End Source File
# Begin Source File

SOURCE=.\res\n21o.bmp
# End Source File
# Begin Source File

SOURCE=.\res\n21s.bmp
# End Source File
# Begin Source File

SOURCE=.\res\p21o.bmp
# End Source File
# Begin Source File

SOURCE=.\res\p21s.bmp
# End Source File
# Begin Source File

SOURCE=.\res\q15o.bmp
# End Source File
# Begin Source File

SOURCE=.\res\q15s.bmp
# End Source File
# Begin Source File

SOURCE=.\res\q21o.bmp
# End Source File
# Begin Source File

SOURCE=.\res\q21s.bmp
# End Source File
# Begin Source File

SOURCE=.\res\r15o.bmp
# End Source File
# Begin Source File

SOURCE=.\res\r15s.bmp
# End Source File
# Begin Source File

SOURCE=.\res\r21o.bmp
# End Source File
# Begin Source File

SOURCE=.\res\r21s.bmp
# End Source File
# Begin Source File

SOURCE=.\res\undo.bmp
# End Source File
# Begin Source File

SOURCE=.\res\up.bmp
# End Source File
# Begin Source File

SOURCE=.\res\white_line_black.bmp
# End Source File
# Begin Source File

SOURCE=.\res\white_line_white.bmp
# End Source File
# Begin Source File

SOURCE=.\res\White_Pawn.bmp
# End Source File
# End Group
# End Target
# End Project
