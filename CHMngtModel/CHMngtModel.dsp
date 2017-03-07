# Microsoft Developer Studio Project File - Name="CHMngtModel" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=CHMngtModel - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "CHMngtModel.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "CHMngtModel.mak" CFG="CHMngtModel - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CHMngtModel - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "CHMngtModel - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/Deportes/CH/CHMngtModel", AASCAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "CHMngtModel - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "CHMNGTMODEL_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "_RWCONFIG_4d" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_CHMNGT_DLL" /D "_WINDLL" /D "_AFXDLL" /D "NOMINMAX" /D "_UNICODE" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 tls4d.lib dbt4d.lib GMngtModel.lib GthmngtModel.lib thspmngtmodel.lib /nologo /dll /machine:I386
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy .\Release\*.dll D:\WorkingDll\Lib	copy .\Release\*.lib D:\WorkingDll\Lib
# End Special Build Tool

!ELSEIF  "$(CFG)" == "CHMngtModel - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "CHMNGTMODEL_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MD /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_CHMNGT_DLL" /D "_RWCONFIG_7d" /D "_UNICODE" /D "NOMINMAX" /D "_WINDLL" /D "_AFXDLL" /FR /Yu"stdCHMngt.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 tls7d.lib dbt7d.lib GMngtModeld.lib gthmngtmodeld.lib thspmngtmodeld.lib /nologo /dll /debug /machine:I386 /out:"Debug/CHMngtModeld.dll" /pdbtype:sept
# SUBTRACT LINK32 /nodefaultlib
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy .\Debug\*.dll D:\WorkingDll\Lib /Y	copy .\Debug\*.lib D:\WorkingDll\Lib /Y
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "CHMngtModel - Win32 Release"
# Name "CHMngtModel - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CHCourt.cpp
# End Source File
# Begin Source File

SOURCE=.\CHDiscipline.cpp
# End Source File
# Begin Source File

SOURCE=.\CHEvent.cpp
# End Source File
# Begin Source File

SOURCE=.\CHEventResult.cpp
# End Source File
# Begin Source File

SOURCE=.\CHInscription.cpp
# End Source File
# Begin Source File

SOURCE=.\CHJudge.cpp
# End Source File
# Begin Source File

SOURCE=.\CHMasterType.cpp
# End Source File
# Begin Source File

SOURCE=.\CHMatch.cpp
# End Source File
# Begin Source File

SOURCE=.\CHMatchJudge.cpp
# End Source File
# Begin Source File

SOURCE=.\CHMatchMember.cpp
# End Source File
# Begin Source File

SOURCE=.\CHMatchResult.cpp
# End Source File
# Begin Source File

SOURCE=.\CHMember.cpp
# End Source File
# Begin Source File

SOURCE=.\CHMemoryDataBase.cpp
# End Source File
# Begin Source File

SOURCE=.\CHPhase.cpp
# End Source File
# Begin Source File

SOURCE=.\CHPhaseBase.cpp
# End Source File
# Begin Source File

SOURCE=.\CHPool.cpp
# End Source File
# Begin Source File

SOURCE=.\CHPoolResult.cpp
# End Source File
# Begin Source File

SOURCE=.\CHRatingDif.cpp
# End Source File
# Begin Source File

SOURCE=.\CHRegister.cpp
# End Source File
# Begin Source File

SOURCE=.\CHSession.cpp
# End Source File
# Begin Source File

SOURCE=.\CHSplitMatch.cpp
# End Source File
# Begin Source File

SOURCE=.\CHSplitMatchResult.cpp
# End Source File
# Begin Source File

SOURCE=.\CHTeamMatchsCnfg.cpp
# End Source File
# Begin Source File

SOURCE=.\QCHCourt.cpp
# End Source File
# Begin Source File

SOURCE=.\QCHDiscipline.cpp
# End Source File
# Begin Source File

SOURCE=.\QCHEvent.cpp
# End Source File
# Begin Source File

SOURCE=.\QCHEventResult.cpp
# End Source File
# Begin Source File

SOURCE=.\QCHInscription.cpp
# End Source File
# Begin Source File

SOURCE=.\QCHJudge.cpp
# End Source File
# Begin Source File

SOURCE=.\QCHMasterType.cpp
# End Source File
# Begin Source File

SOURCE=.\QCHMatch.cpp
# End Source File
# Begin Source File

SOURCE=.\QCHMatchJudge.cpp
# End Source File
# Begin Source File

SOURCE=.\QCHMatchMember.cpp
# End Source File
# Begin Source File

SOURCE=.\QCHMatchResult.cpp
# End Source File
# Begin Source File

SOURCE=.\QCHMember.cpp
# End Source File
# Begin Source File

SOURCE=.\QCHPhase.cpp
# End Source File
# Begin Source File

SOURCE=.\QCHPhaseBase.cpp
# End Source File
# Begin Source File

SOURCE=.\QCHPool.cpp
# End Source File
# Begin Source File

SOURCE=.\QCHPoolResult.cpp
# End Source File
# Begin Source File

SOURCE=.\QCHRatingDif.cpp
# End Source File
# Begin Source File

SOURCE=.\QCHRegister.cpp
# End Source File
# Begin Source File

SOURCE=.\QCHSession.cpp
# End Source File
# Begin Source File

SOURCE=.\QCHSplitMatch.cpp
# End Source File
# Begin Source File

SOURCE=.\QCHSplitMatchResult.cpp
# End Source File
# Begin Source File

SOURCE=.\QCHTeamMatchsCnfg.cpp
# End Source File
# Begin Source File

SOURCE=.\stdCHMngt.cpp

!IF  "$(CFG)" == "CHMngtModel - Win32 Release"

!ELSEIF  "$(CFG)" == "CHMngtModel - Win32 Debug"

# ADD CPP /Yc"stdCHMngt.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\UCHCourt.cpp
# End Source File
# Begin Source File

SOURCE=.\UCHDiscipline.cpp
# End Source File
# Begin Source File

SOURCE=.\UCHEvent.cpp
# End Source File
# Begin Source File

SOURCE=.\UCHEventResult.cpp
# End Source File
# Begin Source File

SOURCE=.\UCHInscription.cpp
# End Source File
# Begin Source File

SOURCE=.\UCHJudge.cpp
# End Source File
# Begin Source File

SOURCE=.\UCHMasterType.cpp
# End Source File
# Begin Source File

SOURCE=.\UCHMatch.cpp
# End Source File
# Begin Source File

SOURCE=.\UCHMatchJudge.cpp
# End Source File
# Begin Source File

SOURCE=.\UCHMatchMember.cpp
# End Source File
# Begin Source File

SOURCE=.\UCHMatchResult.cpp
# End Source File
# Begin Source File

SOURCE=.\UCHMember.cpp
# End Source File
# Begin Source File

SOURCE=.\UCHPhase.cpp
# End Source File
# Begin Source File

SOURCE=.\UCHPhaseBase.cpp
# End Source File
# Begin Source File

SOURCE=.\UCHPool.cpp
# End Source File
# Begin Source File

SOURCE=.\UCHPoolResult.cpp
# End Source File
# Begin Source File

SOURCE=.\UCHRatingDif.cpp
# End Source File
# Begin Source File

SOURCE=.\UCHRegister.cpp
# End Source File
# Begin Source File

SOURCE=.\UCHSession.cpp
# End Source File
# Begin Source File

SOURCE=.\UCHSplitMatch.cpp
# End Source File
# Begin Source File

SOURCE=.\UCHSplitMatchResult.cpp
# End Source File
# Begin Source File

SOURCE=.\UCHTeamMatchsCnfg.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CHClassIDs.h
# End Source File
# Begin Source File

SOURCE=.\CHCourt.h
# End Source File
# Begin Source File

SOURCE=.\CHDiscipline.h
# End Source File
# Begin Source File

SOURCE=.\CHEvent.h
# End Source File
# Begin Source File

SOURCE=.\CHEventResult.h
# End Source File
# Begin Source File

SOURCE=.\CHInscription.h
# End Source File
# Begin Source File

SOURCE=.\CHJudge.h
# End Source File
# Begin Source File

SOURCE=.\CHMasterType.h
# End Source File
# Begin Source File

SOURCE=.\CHMatch.h
# End Source File
# Begin Source File

SOURCE=.\CHMatchJudge.h
# End Source File
# Begin Source File

SOURCE=.\CHMatchMember.h
# End Source File
# Begin Source File

SOURCE=.\CHMatchResult.h
# End Source File
# Begin Source File

SOURCE=.\CHMember.h
# End Source File
# Begin Source File

SOURCE=.\CHMemoryDataBase.h
# End Source File
# Begin Source File

SOURCE=.\CHMsgDefines.h
# End Source File
# Begin Source File

SOURCE=.\CHPhase.h
# End Source File
# Begin Source File

SOURCE=.\CHPhaseBase.h
# End Source File
# Begin Source File

SOURCE=.\CHPool.h
# End Source File
# Begin Source File

SOURCE=.\CHPoolResult.h
# End Source File
# Begin Source File

SOURCE=.\CHRatingDif.h
# End Source File
# Begin Source File

SOURCE=.\CHRegister.h
# End Source File
# Begin Source File

SOURCE=.\CHSession.h
# End Source File
# Begin Source File

SOURCE=.\CHSplitMatch.h
# End Source File
# Begin Source File

SOURCE=.\CHSplitMatchResult.h
# End Source File
# Begin Source File

SOURCE=.\CHSportDefines.h
# End Source File
# Begin Source File

SOURCE=.\CHStatisticDefines.h
# End Source File
# Begin Source File

SOURCE=.\CHTeamMatchsCnfg.h
# End Source File
# Begin Source File

SOURCE=.\QCHCourt.h
# End Source File
# Begin Source File

SOURCE=.\QCHDiscipline.h
# End Source File
# Begin Source File

SOURCE=.\QCHEvent.h
# End Source File
# Begin Source File

SOURCE=.\QCHEventResult.h
# End Source File
# Begin Source File

SOURCE=.\QCHInscription.h
# End Source File
# Begin Source File

SOURCE=.\QCHJudge.h
# End Source File
# Begin Source File

SOURCE=.\QCHMasterType.h
# End Source File
# Begin Source File

SOURCE=.\QCHMatch.h
# End Source File
# Begin Source File

SOURCE=.\QCHMatchJudge.h
# End Source File
# Begin Source File

SOURCE=.\QCHMatchMember.h
# End Source File
# Begin Source File

SOURCE=.\QCHMatchResult.h
# End Source File
# Begin Source File

SOURCE=.\QCHMember.h
# End Source File
# Begin Source File

SOURCE=.\QCHPhase.h
# End Source File
# Begin Source File

SOURCE=.\QCHPhaseBase.h
# End Source File
# Begin Source File

SOURCE=.\QCHPool.h
# End Source File
# Begin Source File

SOURCE=.\QCHPoolResult.h
# End Source File
# Begin Source File

SOURCE=.\QCHRatingDif.h
# End Source File
# Begin Source File

SOURCE=.\QCHRegister.h
# End Source File
# Begin Source File

SOURCE=.\QCHSession.h
# End Source File
# Begin Source File

SOURCE=.\QCHSplitMatch.h
# End Source File
# Begin Source File

SOURCE=.\QCHSplitMatchResult.h
# End Source File
# Begin Source File

SOURCE=.\QCHTeamMatchsCnfg.h
# End Source File
# Begin Source File

SOURCE=.\stdCHMngt.h
# End Source File
# Begin Source File

SOURCE=.\UCHCourt.h
# End Source File
# Begin Source File

SOURCE=.\UCHDiscipline.h
# End Source File
# Begin Source File

SOURCE=.\UCHEvent.h
# End Source File
# Begin Source File

SOURCE=.\UCHEventResult.h
# End Source File
# Begin Source File

SOURCE=.\UCHInscription.h
# End Source File
# Begin Source File

SOURCE=.\UCHJudge.h
# End Source File
# Begin Source File

SOURCE=.\UCHMasterType.h
# End Source File
# Begin Source File

SOURCE=.\UCHMatch.h
# End Source File
# Begin Source File

SOURCE=.\UCHMatchJudge.h
# End Source File
# Begin Source File

SOURCE=.\UCHMatchMember.h
# End Source File
# Begin Source File

SOURCE=.\UCHMatchResult.h
# End Source File
# Begin Source File

SOURCE=.\UCHMember.h
# End Source File
# Begin Source File

SOURCE=.\UCHPhase.h
# End Source File
# Begin Source File

SOURCE=.\UCHPhaseBase.h
# End Source File
# Begin Source File

SOURCE=.\UCHPool.h
# End Source File
# Begin Source File

SOURCE=.\UCHPoolResult.h
# End Source File
# Begin Source File

SOURCE=.\UCHRatingDif.h
# End Source File
# Begin Source File

SOURCE=.\UCHRegister.h
# End Source File
# Begin Source File

SOURCE=.\UCHSession.h
# End Source File
# Begin Source File

SOURCE=.\UCHSplitMatch.h
# End Source File
# Begin Source File

SOURCE=.\UCHSplitMatchResult.h
# End Source File
# Begin Source File

SOURCE=.\UCHTeamMatchsCnfg.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
