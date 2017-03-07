# Microsoft Developer Studio Project File - Name="CHVMngtModel" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=CHVMngtModel - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "CHVMngtModel.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "CHVMngtModel.mak" CFG="CHVMngtModel - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CHVMngtModel - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "CHVMngtModel - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/Deportes/CH/CHVMngtModel", LJSCAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "CHVMngtModel - Win32 Release"

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
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "CHVMNGTMODEL_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "_RWCONFIG_4d" /D "_AFXEXT" /D "_UNICODE" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "NOMINMAX" /D "_CHVMNGT_DLL" /D "_WINDLL" /D "_AFXDLL" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 tls4d.lib dbt4d.lib gMngtModel.lib VMngtModel.lib GTHMngtModel.lib THVMngtModel.lib CHMngtModel.lib thspmngtmodel.lib /nologo /dll /machine:I386
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy .\Release\*.dll D:\WorkingDll\Lib	copy .\Release\*.lib D:\WorkingDll\Lib
# End Special Build Tool

!ELSEIF  "$(CFG)" == "CHVMngtModel - Win32 Debug"

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
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "CHVMNGTMODEL_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MD /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "_USRDLL" /D "_RWCONFIG_7d" /D "_UNICODE" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "NOMINMAX" /D "_CHVMNGT_DLL" /D "_WINDLL" /D "_AFXDLL" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 tls7d.lib dbt7d.lib gMngtModeld.lib VMngtModeld.lib GTHMngtModeld.lib THVMngtModeld.lib CHMngtModeld.lib thspmngtmodeld.lib /nologo /dll /debug /machine:I386 /out:"Debug/CHVMngtModeld.dll" /pdbtype:sept
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy .\Debug\*.dll D:\WorkingDll\Lib /Y	copy .\Debug\*.lib D:\WorkingDll\Lib /Y
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "CHVMngtModel - Win32 Release"
# Name "CHVMngtModel - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CHChange.cpp
# End Source File
# Begin Source File

SOURCE=.\CHCheckList.cpp
# End Source File
# Begin Source File

SOURCE=.\CHCompetitorDraw.cpp
# End Source File
# Begin Source File

SOURCE=.\CHGroupDraw.cpp
# End Source File
# Begin Source File

SOURCE=.\CHPairDraw.cpp
# End Source File
# Begin Source File

SOURCE=.\CHPermutationNumber.cpp
# End Source File
# Begin Source File

SOURCE=.\CHPgnMatch.cpp
# End Source File
# Begin Source File

SOURCE=.\CHRC08.cpp
# End Source File
# Begin Source File

SOURCE=.\CHRC30.cpp
# End Source File
# Begin Source File

SOURCE=.\CHRC32A.cpp
# End Source File
# Begin Source File

SOURCE=.\CHRC32C.cpp
# End Source File
# Begin Source File

SOURCE=.\CHRC35.cpp
# End Source File
# Begin Source File

SOURCE=.\CHRC38.cpp
# End Source File
# Begin Source File

SOURCE=.\CHRC51.cpp
# End Source File
# Begin Source File

SOURCE=.\CHRC51G.cpp
# End Source File
# Begin Source File

SOURCE=.\CHRC58.cpp
# End Source File
# Begin Source File

SOURCE=.\CHRC74.cpp
# End Source File
# Begin Source File

SOURCE=.\CHRC75.cpp
# End Source File
# Begin Source File

SOURCE=.\CHRC76.cpp
# End Source File
# Begin Source File

SOURCE=.\CHRC76A.cpp
# End Source File
# Begin Source File

SOURCE=.\CHRC76B.cpp
# End Source File
# Begin Source File

SOURCE=.\CHRC93.cpp
# End Source File
# Begin Source File

SOURCE=.\CHRC95.cpp
# End Source File
# Begin Source File

SOURCE=.\CHRC96.cpp
# End Source File
# Begin Source File

SOURCE=.\CHReportTemplate.cpp
# End Source File
# Begin Source File

SOURCE=.\CHRLegends.cpp
# End Source File
# Begin Source File

SOURCE=.\CHROfficialsRole.cpp
# End Source File
# Begin Source File

SOURCE=.\CHRoundDraw.cpp
# End Source File
# Begin Source File

SOURCE=.\CHRPool.cpp
# End Source File
# Begin Source File

SOURCE=.\CHSessionPoolround.cpp
# End Source File
# Begin Source File

SOURCE=.\CHVEntriesByNoc.cpp
# End Source File
# Begin Source File

SOURCE=.\RCHSchedule.cpp
# End Source File
# Begin Source File

SOURCE=.\stdVCH.cpp
# End Source File
# Begin Source File

SOURCE=.\VCHCheckList.cpp
# End Source File
# Begin Source File

SOURCE=.\VCHSchedule.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CHChange.h
# End Source File
# Begin Source File

SOURCE=.\CHCheckList.h
# End Source File
# Begin Source File

SOURCE=.\CHCompetitorDraw.h
# End Source File
# Begin Source File

SOURCE=.\CHGroupDraw.h
# End Source File
# Begin Source File

SOURCE=.\CHPairDraw.h
# End Source File
# Begin Source File

SOURCE=.\CHPermutationNumber.h
# End Source File
# Begin Source File

SOURCE=.\CHPgnMatch.h
# End Source File
# Begin Source File

SOURCE=.\CHRC08.h
# End Source File
# Begin Source File

SOURCE=.\CHRC30.h
# End Source File
# Begin Source File

SOURCE=.\CHRC32A.h
# End Source File
# Begin Source File

SOURCE=.\CHRC32C.h
# End Source File
# Begin Source File

SOURCE=.\CHRC35.h
# End Source File
# Begin Source File

SOURCE=.\CHRC38.h
# End Source File
# Begin Source File

SOURCE=.\CHRC51.h
# End Source File
# Begin Source File

SOURCE=.\CHRC51G.h
# End Source File
# Begin Source File

SOURCE=.\CHRC58.h
# End Source File
# Begin Source File

SOURCE=.\CHRC74.h
# End Source File
# Begin Source File

SOURCE=.\CHRC75.h
# End Source File
# Begin Source File

SOURCE=.\CHRC76.h
# End Source File
# Begin Source File

SOURCE=.\CHRC76A.h
# End Source File
# Begin Source File

SOURCE=.\CHRC76B.h
# End Source File
# Begin Source File

SOURCE=.\CHRC93.h
# End Source File
# Begin Source File

SOURCE=.\CHRC95.h
# End Source File
# Begin Source File

SOURCE=.\CHRC96.h
# End Source File
# Begin Source File

SOURCE=.\CHReportDefines.h
# End Source File
# Begin Source File

SOURCE=.\CHReportTemplate.h
# End Source File
# Begin Source File

SOURCE=.\CHRLegends.h
# End Source File
# Begin Source File

SOURCE=.\CHROfficialsRole.h
# End Source File
# Begin Source File

SOURCE=.\CHRoundDraw.h
# End Source File
# Begin Source File

SOURCE=.\CHRPool.h
# End Source File
# Begin Source File

SOURCE=.\CHSessionPoolround.h
# End Source File
# Begin Source File

SOURCE=.\CHVEntriesByNoc.h
# End Source File
# Begin Source File

SOURCE=.\CHViewsIDs.h
# End Source File
# Begin Source File

SOURCE=.\CHVMngtModelDll.h
# End Source File
# Begin Source File

SOURCE=.\RCHSchedule.h
# End Source File
# Begin Source File

SOURCE=.\stdVCH.h
# End Source File
# Begin Source File

SOURCE=.\VCHCheckList.h
# End Source File
# Begin Source File

SOURCE=.\VCHSchedule.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "ReportsFiles"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\CHManager\ReportsFiles\CH.C08.ENG.lis
# End Source File
# Begin Source File

SOURCE=..\CHManager\ReportsFiles\CH.C30.ENG.lis
# End Source File
# Begin Source File

SOURCE=..\CHManager\ReportsFiles\CH.C32A.ENG.lis
# End Source File
# Begin Source File

SOURCE=..\CHManager\ReportsFiles\CH.C32C.ENG.lis
# End Source File
# Begin Source File

SOURCE=..\CHManager\ReportsFiles\CH.C35.eng.lis
# End Source File
# Begin Source File

SOURCE=..\CHManager\ReportsFiles\CH.C51.ENG.lis
# End Source File
# Begin Source File

SOURCE=..\CHManager\ReportsFiles\CH.C58.ENG.lis
# End Source File
# Begin Source File

SOURCE=..\CHManager\ReportsFiles\CH.C74.ENG.lis
# End Source File
# Begin Source File

SOURCE=..\CHManager\ReportsFiles\CH.C75.ENG.lis
# End Source File
# Begin Source File

SOURCE=..\CHManager\ReportsFiles\CH.C76.ENG.lis
# End Source File
# Begin Source File

SOURCE=..\CHManager\ReportsFiles\CH.C93.ENG.lis
# End Source File
# Begin Source File

SOURCE=..\CHManager\ReportsFiles\CH.C96.ENG.lis
# End Source File
# Begin Source File

SOURCE=..\CHManager\ReportsFiles\CH.OfficialsRole.eng.lis
# End Source File
# Begin Source File

SOURCE=..\CHManager\ReportsFiles\CHAsOfInHeader.ENG.lis
# End Source File
# Begin Source File

SOURCE=..\CHManager\ReportsFiles\CHLegends.ENG.lis
# End Source File
# Begin Source File

SOURCE=..\CHManager\ReportsFiles\CHLegendsDescription.ENG.lis
# End Source File
# Begin Source File

SOURCE=..\CHManager\ReportsFiles\Doha.header.lis
# End Source File
# End Group
# End Target
# End Project
