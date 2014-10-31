# Microsoft Developer Studio Project File - Name="WinDE" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=WinDE - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "WinDE.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "WinDE.mak" CFG="WinDE - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "WinDE - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "WinDE - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "WinDE - Win32 Release"

# PROP BASE Use_MFC 6
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
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /out:"Release/Basternae Area Editor.exe"
# SUBTRACT LINK32 /incremental:yes /debug

!ELSEIF  "$(CFG)" == "WinDE - Win32 Debug"

# PROP BASE Use_MFC 6
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
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:"Debug/Basternae Area Editor.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "WinDE - Win32 Release"
# Name "WinDE - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\DlgCalcCoins.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgDirections.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgEditArea.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgEnterVnum.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgExtraDesc.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSave.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSelectAff.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSelectColor.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSettings.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVnumList.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\WinDE.cpp
# End Source File
# Begin Source File

SOURCE=.\WinDEDlg.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\DlgCalcCoins.h
# End Source File
# Begin Source File

SOURCE=.\DlgDirections.h
# End Source File
# Begin Source File

SOURCE=.\DlgEditArea.h
# End Source File
# Begin Source File

SOURCE=.\DlgEnterVnum.h
# End Source File
# Begin Source File

SOURCE=.\DlgExtraDesc.h
# End Source File
# Begin Source File

SOURCE=.\DlgSave.h
# End Source File
# Begin Source File

SOURCE=.\DlgSelectAff.h
# End Source File
# Begin Source File

SOURCE=.\DlgSelectColor.h
# End Source File
# Begin Source File

SOURCE=.\DlgSettings.h
# End Source File
# Begin Source File

SOURCE=.\DlgVnumList.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\WinDE.h
# End Source File
# Begin Source File

SOURCE=.\WinDEDlg.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap6.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap8.bmp
# End Source File
# Begin Source File

SOURCE=.\res\blacu.bmp
# End Source File
# Begin Source File

SOURCE=.\res\blueu.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00003.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00004.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00005.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00006.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00007.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00008.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00009.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00010.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00011.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00012.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00013.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00014.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00015.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00016.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00017.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00018.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00019.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00020.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00021.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00022.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00023.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00024.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00025.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00026.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00027.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Ctrpanel.ico
# End Source File
# Begin Source File

SOURCE=.\res\cyanu.bmp
# End Source File
# Begin Source File

SOURCE=.\res\eastu.bmp
# End Source File
# Begin Source File

SOURCE=.\res\exits_w.ico
# End Source File
# Begin Source File

SOURCE=.\res\Find.bmp
# End Source File
# Begin Source File

SOURCE=.\res\greenu.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ico00001.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00002.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00003.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00004.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00005.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00006.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00007.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00008.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00009.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00010.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00011.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00012.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00013.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00014.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00015.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00016.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00017.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00018.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00019.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00020.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00021.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00022.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00023.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00024.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00025.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00026.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00027.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00028.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00029.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00030.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00031.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon2.ico
# End Source File
# Begin Source File

SOURCE=.\res\Key.bmp
# End Source File
# Begin Source File

SOURCE=.\res\keydown.bmp
# End Source File
# Begin Source File

SOURCE=.\res\magentau.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Misc27.ico
# End Source File
# Begin Source File

SOURCE=.\res\northup.bmp
# End Source File
# Begin Source File

SOURCE=.\res\northwes.bmp
# End Source File
# Begin Source File

SOURCE=.\res\redu.bmp
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\res\room_bas.ico
# End Source File
# Begin Source File

SOURCE=.\res\southeas.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tree_mob.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tree_roo.bmp
# End Source File
# Begin Source File

SOURCE=.\res\west_exi.ico
# End Source File
# Begin Source File

SOURCE=.\res\westd.bmp
# End Source File
# Begin Source File

SOURCE=.\res\WinDE.ico
# End Source File
# Begin Source File

SOURCE=.\WinDE.rc
# End Source File
# Begin Source File

SOURCE=.\res\WinDE.rc2
# End Source File
# Begin Source File

SOURCE=.\res\yellowu.bmp
# End Source File
# End Group
# Begin Group "Colorizer"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ColorEditWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\ColorEditWnd.h
# End Source File
# Begin Source File

SOURCE=.\Colorizer.cpp
# End Source File
# Begin Source File

SOURCE=.\Colorizer.h
# End Source File
# Begin Source File

SOURCE=.\MemDC.h
# End Source File
# Begin Source File

SOURCE=.\SampleColorizer.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleColorizer.h
# End Source File
# Begin Source File

SOURCE=.\ScriptText.cpp
# End Source File
# Begin Source File

SOURCE=.\ScriptText.h
# End Source File
# Begin Source File

SOURCE=.\UndoFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\UndoFrame.h
# End Source File
# End Group
# Begin Group "MapEdit"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DlgMapEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgMapEdit.h
# End Source File
# End Group
# Begin Group "ZoneFiles"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ZoneFile.cpp
# End Source File
# Begin Source File

SOURCE=.\ZoneFile.h
# End Source File
# End Group
# Begin Group "Quests"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DlgEditQuest.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgEditQuest.h
# End Source File
# Begin Source File

SOURCE=.\DlgQuestClue.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgQuestClue.h
# End Source File
# Begin Source File

SOURCE=.\DlgQuestEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgQuestEdit.h
# End Source File
# Begin Source File

SOURCE=.\DlgQuestItem.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgQuestItem.h
# End Source File
# Begin Source File

SOURCE=.\Quests.cpp
# End Source File
# Begin Source File

SOURCE=.\Quests.h
# End Source File
# End Group
# Begin Group "Spells"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DlgSpells.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSpells.h
# End Source File
# Begin Source File

SOURCE=.\Spells.cpp
# End Source File
# Begin Source File

SOURCE=.\Spells.h
# End Source File
# End Group
# Begin Group "Objects"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DlgEditAntiFlags.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgEditAntiFlags.h
# End Source File
# Begin Source File

SOURCE=.\DlgEditContents.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgEditContents.h
# End Source File
# Begin Source File

SOURCE=.\DlgEditObject.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgEditObject.h
# End Source File
# Begin Source File

SOURCE=.\DlgExtraObjFlags.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgExtraObjFlags.h
# End Source File
# Begin Source File

SOURCE=.\Objects.cpp
# End Source File
# Begin Source File

SOURCE=.\Objects.h
# End Source File
# End Group
# Begin Group "Mobiles"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Classes.cpp
# End Source File
# Begin Source File

SOURCE=.\Classes.h
# End Source File
# Begin Source File

SOURCE=.\DlgActFlags.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgActFlags.h
# End Source File
# Begin Source File

SOURCE=.\DlgEditFriends.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgEditFriends.h
# End Source File
# Begin Source File

SOURCE=.\DlgEditMob.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgEditMob.h
# End Source File
# Begin Source File

SOURCE=.\DlgEditShop.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgEditShop.h
# End Source File
# Begin Source File

SOURCE=.\DlgEquipItem.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgEquipItem.h
# End Source File
# Begin Source File

SOURCE=.\DlgEquipMob.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgEquipMob.h
# End Source File
# Begin Source File

SOURCE=.\DlgMobAffFlags.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgMobAffFlags.h
# End Source File
# Begin Source File

SOURCE=.\Mobs.cpp
# End Source File
# Begin Source File

SOURCE=.\Mobs.h
# End Source File
# End Group
# Begin Group "Alias"

# PROP Default_Filter ".h .cpp .c .cc"
# Begin Source File

SOURCE=.\Alias.cpp
# End Source File
# Begin Source File

SOURCE=.\Alias.h
# End Source File
# End Group
# Begin Group "Rooms"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DlgCreateGrid.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCreateGrid.h
# End Source File
# Begin Source File

SOURCE=.\DlgEditExits.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgEditExits.h
# End Source File
# Begin Source File

SOURCE=.\DlgGuardFlags.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgGuardFlags.h
# End Source File
# Begin Source File

SOURCE=.\DlgRoomFlags.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRoomFlags.h
# End Source File
# Begin Source File

SOURCE=.\EditRoom.cpp
# End Source File
# Begin Source File

SOURCE=.\EditRoom.h
# End Source File
# Begin Source File

SOURCE=.\Rooms.cpp
# End Source File
# Begin Source File

SOURCE=.\Rooms.h
# End Source File
# End Group
# Begin Group "Progs"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ProgEditor.cpp
# End Source File
# Begin Source File

SOURCE=.\ProgEditor.h
# End Source File
# Begin Source File

SOURCE=.\ProgEditWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\ProgEditWnd.h
# End Source File
# Begin Source File

SOURCE=.\Progs.cpp
# End Source File
# Begin Source File

SOURCE=.\Progs.h
# End Source File
# Begin Source File

SOURCE=.\ProgText.cpp
# End Source File
# Begin Source File

SOURCE=.\ProgText.h
# End Source File
# End Group
# Begin Group "NumericEdit"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\NumericEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\NumericEdit.h
# End Source File
# End Group
# Begin Group "Traps"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DlgEditTrap.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgEditTrap.h
# End Source File
# Begin Source File

SOURCE=.\TrapData.cpp
# End Source File
# Begin Source File

SOURCE=.\TrapData.h
# End Source File
# End Group
# Begin Group "ShipBuilder"

# PROP Default_Filter ""
# Begin Group "Ammo"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\AmmoBuilder.cpp
# End Source File
# Begin Source File

SOURCE=.\AmmoBuilder.h
# End Source File
# Begin Source File

SOURCE=.\AmmoView.cpp
# End Source File
# Begin Source File

SOURCE=.\AmmoView.h
# End Source File
# End Group
# Begin Group "Crew"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CrewBuilder.cpp
# End Source File
# Begin Source File

SOURCE=.\CrewBuilder.h
# End Source File
# Begin Source File

SOURCE=.\CrewView.cpp
# End Source File
# Begin Source File

SOURCE=.\CrewView.h
# End Source File
# End Group
# Begin Group "Cannons"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CannonBuilder.cpp
# End Source File
# Begin Source File

SOURCE=.\CannonBuilder.h
# End Source File
# Begin Source File

SOURCE=.\CannonView.cpp
# End Source File
# Begin Source File

SOURCE=.\CannonView.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\ShipBuilder.cpp
# End Source File
# Begin Source File

SOURCE=.\ShipBuilder.h
# End Source File
# Begin Source File

SOURCE=.\ShipUpgrades.cpp
# End Source File
# Begin Source File

SOURCE=.\ShipUpgrades.h
# End Source File
# Begin Source File

SOURCE=.\ShipwrightList.cpp
# End Source File
# Begin Source File

SOURCE=.\ShipwrightList.h
# End Source File
# Begin Source File

SOURCE=.\TabCtrlSSL.cpp
# End Source File
# Begin Source File

SOURCE=.\TabCtrlSSL.h
# End Source File
# Begin Source File

SOURCE=.\TabPageSSL.cpp
# End Source File
# Begin Source File

SOURCE=.\TabPageSSL.h
# End Source File
# End Group
# Begin Group "Controls"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CmdHistory.cpp
# End Source File
# Begin Source File

SOURCE=.\CmdHistory.h
# End Source File
# Begin Source File

SOURCE=.\CtrlToolBar.cpp
# End Source File
# Begin Source File

SOURCE=.\CtrlToolBar.h
# End Source File
# Begin Source File

SOURCE=.\EasySize.h
# End Source File
# Begin Source File

SOURCE=.\SplitterControl.cpp
# End Source File
# Begin Source File

SOURCE=.\SplitterControl.h
# End Source File
# Begin Source File

SOURCE=.\ZoneTree.cpp
# End Source File
# Begin Source File

SOURCE=.\ZoneTree.h
# End Source File
# End Group
# Begin Group "Misc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Area.cpp
# End Source File
# Begin Source File

SOURCE=.\Area.h
# End Source File
# Begin Source File

SOURCE=.\Bits.cpp
# End Source File
# Begin Source File

SOURCE=.\Bits.h
# End Source File
# Begin Source File

SOURCE=.\Interp.cpp
# End Source File
# Begin Source File

SOURCE=.\Interp.h
# End Source File
# Begin Source File

SOURCE=.\Utils.cpp
# End Source File
# Begin Source File

SOURCE=.\Utils.h
# End Source File
# End Group
# Begin Group "Statistics"

# PROP Default_Filter ""
# Begin Group "Mobs"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ClassView.cpp
# End Source File
# Begin Source File

SOURCE=.\ClassView.h
# End Source File
# Begin Source File

SOURCE=.\DlgAggroStatistics.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAggroStatistics.h
# End Source File
# Begin Source File

SOURCE=.\MobView.cpp
# End Source File
# Begin Source File

SOURCE=.\MobView.h
# End Source File
# Begin Source File

SOURCE=.\RaceView.cpp
# End Source File
# Begin Source File

SOURCE=.\RaceView.h
# End Source File
# End Group
# Begin Group "Room"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\RoomView.cpp
# End Source File
# Begin Source File

SOURCE=.\RoomView.h
# End Source File
# End Group
# Begin Group "Objs"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CraftView.cpp
# End Source File
# Begin Source File

SOURCE=.\CraftView.h
# End Source File
# Begin Source File

SOURCE=.\MaterialVew.cpp
# End Source File
# Begin Source File

SOURCE=.\MaterialVew.h
# End Source File
# Begin Source File

SOURCE=.\ObjView.cpp
# End Source File
# Begin Source File

SOURCE=.\ObjView.h
# End Source File
# Begin Source File

SOURCE=.\StatsView.cpp
# End Source File
# Begin Source File

SOURCE=.\StatsView.h
# End Source File
# Begin Source File

SOURCE=.\StatView.cpp
# End Source File
# Begin Source File

SOURCE=.\StatView.h
# End Source File
# Begin Source File

SOURCE=.\TypeView.cpp
# End Source File
# Begin Source File

SOURCE=.\TypeView.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\DlgAreaStatistics.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAreaStatistics.h
# End Source File
# End Group
# Begin Group "ChartControl"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\font.cpp
# End Source File
# Begin Source File

SOURCE=.\font.h
# End Source File
# Begin Source File

SOURCE=.\mschart.cpp
# End Source File
# Begin Source File

SOURCE=.\mschart.h
# End Source File
# Begin Source File

SOURCE=.\vcaxis.cpp
# End Source File
# Begin Source File

SOURCE=.\vcaxis.h
# End Source File
# Begin Source File

SOURCE=.\vcaxisgrid.cpp
# End Source File
# Begin Source File

SOURCE=.\vcaxisgrid.h
# End Source File
# Begin Source File

SOURCE=.\vcaxisscale.cpp
# End Source File
# Begin Source File

SOURCE=.\vcaxisscale.h
# End Source File
# Begin Source File

SOURCE=.\vcaxistitle.cpp
# End Source File
# Begin Source File

SOURCE=.\vcaxistitle.h
# End Source File
# Begin Source File

SOURCE=.\vcbackdrop.cpp
# End Source File
# Begin Source File

SOURCE=.\vcbackdrop.h
# End Source File
# Begin Source File

SOURCE=.\vcbrush.cpp
# End Source File
# Begin Source File

SOURCE=.\vcbrush.h
# End Source File
# Begin Source File

SOURCE=.\vccategoryscale.cpp
# End Source File
# Begin Source File

SOURCE=.\vccategoryscale.h
# End Source File
# Begin Source File

SOURCE=.\vccolor.cpp
# End Source File
# Begin Source File

SOURCE=.\vccolor.h
# End Source File
# Begin Source File

SOURCE=.\vccoor.cpp
# End Source File
# Begin Source File

SOURCE=.\vccoor.h
# End Source File
# Begin Source File

SOURCE=.\vcdatagrid.cpp
# End Source File
# Begin Source File

SOURCE=.\vcdatagrid.h
# End Source File
# Begin Source File

SOURCE=.\vcdatapoint.cpp
# End Source File
# Begin Source File

SOURCE=.\vcdatapoint.h
# End Source File
# Begin Source File

SOURCE=.\vcdatapointlabel.cpp
# End Source File
# Begin Source File

SOURCE=.\vcdatapointlabel.h
# End Source File
# Begin Source File

SOURCE=.\vcdatapoints.cpp
# End Source File
# Begin Source File

SOURCE=.\vcdatapoints.h
# End Source File
# Begin Source File

SOURCE=.\vcfill.cpp
# End Source File
# Begin Source File

SOURCE=.\vcfill.h
# End Source File
# Begin Source File

SOURCE=.\vcfont.cpp
# End Source File
# Begin Source File

SOURCE=.\vcfont.h
# End Source File
# Begin Source File

SOURCE=.\vcfootnote.cpp
# End Source File
# Begin Source File

SOURCE=.\vcfootnote.h
# End Source File
# Begin Source File

SOURCE=.\vcframe.cpp
# End Source File
# Begin Source File

SOURCE=.\vcframe.h
# End Source File
# Begin Source File

SOURCE=.\vcintersection.cpp
# End Source File
# Begin Source File

SOURCE=.\vcintersection.h
# End Source File
# Begin Source File

SOURCE=.\vclabel.cpp
# End Source File
# Begin Source File

SOURCE=.\vclabel.h
# End Source File
# Begin Source File

SOURCE=.\vclabels.cpp
# End Source File
# Begin Source File

SOURCE=.\vclabels.h
# End Source File
# Begin Source File

SOURCE=.\vclcoor.cpp
# End Source File
# Begin Source File

SOURCE=.\vclcoor.h
# End Source File
# Begin Source File

SOURCE=.\vclegend.cpp
# End Source File
# Begin Source File

SOURCE=.\vclegend.h
# End Source File
# Begin Source File

SOURCE=.\vclight.cpp
# End Source File
# Begin Source File

SOURCE=.\vclight.h
# End Source File
# Begin Source File

SOURCE=.\vclightsource.cpp
# End Source File
# Begin Source File

SOURCE=.\vclightsource.h
# End Source File
# Begin Source File

SOURCE=.\vclightsources.cpp
# End Source File
# Begin Source File

SOURCE=.\vclightsources.h
# End Source File
# Begin Source File

SOURCE=.\vclocation.cpp
# End Source File
# Begin Source File

SOURCE=.\vclocation.h
# End Source File
# Begin Source File

SOURCE=.\vcmarker.cpp
# End Source File
# Begin Source File

SOURCE=.\vcmarker.h
# End Source File
# Begin Source File

SOURCE=.\vcpen.cpp
# End Source File
# Begin Source File

SOURCE=.\vcpen.h
# End Source File
# Begin Source File

SOURCE=.\vcplot.cpp
# End Source File
# Begin Source File

SOURCE=.\vcplot.h
# End Source File
# Begin Source File

SOURCE=.\vcplotbase.cpp
# End Source File
# Begin Source File

SOURCE=.\vcplotbase.h
# End Source File
# Begin Source File

SOURCE=.\vcrect.cpp
# End Source File
# Begin Source File

SOURCE=.\vcrect.h
# End Source File
# Begin Source File

SOURCE=.\vcseries.cpp
# End Source File
# Begin Source File

SOURCE=.\vcseries.h
# End Source File
# Begin Source File

SOURCE=.\vcseriescollection.cpp
# End Source File
# Begin Source File

SOURCE=.\vcseriescollection.h
# End Source File
# Begin Source File

SOURCE=.\vcseriesmarker.cpp
# End Source File
# Begin Source File

SOURCE=.\vcseriesmarker.h
# End Source File
# Begin Source File

SOURCE=.\vcseriesposition.cpp
# End Source File
# Begin Source File

SOURCE=.\vcseriesposition.h
# End Source File
# Begin Source File

SOURCE=.\vcshadow.cpp
# End Source File
# Begin Source File

SOURCE=.\vcshadow.h
# End Source File
# Begin Source File

SOURCE=.\vcstatline.cpp
# End Source File
# Begin Source File

SOURCE=.\vcstatline.h
# End Source File
# Begin Source File

SOURCE=.\vctextlayout.cpp
# End Source File
# Begin Source File

SOURCE=.\vctextlayout.h
# End Source File
# Begin Source File

SOURCE=.\vctick.cpp
# End Source File
# Begin Source File

SOURCE=.\vctick.h
# End Source File
# Begin Source File

SOURCE=.\vctitle.cpp
# End Source File
# Begin Source File

SOURCE=.\vctitle.h
# End Source File
# Begin Source File

SOURCE=.\vcvaluescale.cpp
# End Source File
# Begin Source File

SOURCE=.\vcvaluescale.h
# End Source File
# Begin Source File

SOURCE=.\vcview3d.cpp
# End Source File
# Begin Source File

SOURCE=.\vcview3d.h
# End Source File
# Begin Source File

SOURCE=.\vcwall.cpp
# End Source File
# Begin Source File

SOURCE=.\vcwall.h
# End Source File
# Begin Source File

SOURCE=.\vcweighting.cpp
# End Source File
# Begin Source File

SOURCE=.\vcweighting.h
# End Source File
# End Group
# Begin Group "About"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DlgAbout.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAbout.h
# End Source File
# Begin Source File

SOURCE=.\MyHyperLink.cpp
# End Source File
# Begin Source File

SOURCE=.\MyHyperLink.h
# End Source File
# End Group
# Begin Group "Bit Calculator"

# PROP Default_Filter ".h .ccp"
# Begin Source File

SOURCE=.\BvCalc.cpp
# End Source File
# Begin Source File

SOURCE=.\BvCalc.h
# End Source File
# Begin Source File

SOURCE=.\EditAffBits.cpp
# End Source File
# Begin Source File

SOURCE=.\EditAffBits.h
# End Source File
# End Group
# End Target
# End Project
# Section WinDE : {BEF6E003-A874-101A-8BBA-00AA00300CAB}
# 	2:5:Class:COleFont
# 	2:10:HeaderFile:font.h
# 	2:8:ImplFile:font.cpp
# End Section
# Section WinDE : {E9E074E2-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcBackdrop
# 	2:10:HeaderFile:vcbackdrop.h
# 	2:8:ImplFile:vcbackdrop.cpp
# End Section
# Section WinDE : {E9E074F2-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcView3d
# 	2:10:HeaderFile:vcview3d.h
# 	2:8:ImplFile:vcview3d.cpp
# End Section
# Section WinDE : {E9E07527-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcPlot
# 	2:10:HeaderFile:vcplot.h
# 	2:8:ImplFile:vcplot.cpp
# End Section
# Section WinDE : {E9E07517-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcCategoryScale
# 	2:10:HeaderFile:vccategoryscale.h
# 	2:8:ImplFile:vccategoryscale.cpp
# End Section
# Section WinDE : {E9E074CD-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcRect
# 	2:10:HeaderFile:vcrect.h
# 	2:8:ImplFile:vcrect.cpp
# End Section
# Section WinDE : {E9E074E6-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcFootnote
# 	2:10:HeaderFile:vcfootnote.h
# 	2:8:ImplFile:vcfootnote.cpp
# End Section
# Section WinDE : {E9E074D6-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcLocation
# 	2:10:HeaderFile:vclocation.h
# 	2:8:ImplFile:vclocation.cpp
# End Section
# Section WinDE : {E9E07502-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcSeriesPosition
# 	2:10:HeaderFile:vcseriesposition.h
# 	2:8:ImplFile:vcseriesposition.cpp
# End Section
# Section WinDE : {E9E0750E-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcDataPoint
# 	2:10:HeaderFile:vcdatapoint.h
# 	2:8:ImplFile:vcdatapoint.cpp
# End Section
# Section WinDE : {3A2B370A-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CMSChart
# 	2:10:HeaderFile:mschart.h
# 	2:8:ImplFile:mschart.cpp
# End Section
# Section WinDE : {E9E074D1-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcPen
# 	2:10:HeaderFile:vcpen.h
# 	2:8:ImplFile:vcpen.cpp
# End Section
# Section WinDE : {E9E0751D-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcIntersection
# 	2:10:HeaderFile:vcintersection.h
# 	2:8:ImplFile:vcintersection.cpp
# End Section
# Section WinDE : {E9E07506-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcStatLine
# 	2:10:HeaderFile:vcstatline.h
# 	2:8:ImplFile:vcstatline.cpp
# End Section
# Section WinDE : {E9E074EC-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcLightSource
# 	2:10:HeaderFile:vclightsource.h
# 	2:8:ImplFile:vclightsource.cpp
# End Section
# Section WinDE : {E9E074DC-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcShadow
# 	2:10:HeaderFile:vcshadow.h
# 	2:8:ImplFile:vcshadow.cpp
# End Section
# Section WinDE : {E9E07521-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcAxisScale
# 	2:10:HeaderFile:vcaxisscale.h
# 	2:8:ImplFile:vcaxisscale.cpp
# End Section
# Section WinDE : {E9E074D5-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcTextLayout
# 	2:10:HeaderFile:vctextlayout.h
# 	2:8:ImplFile:vctextlayout.cpp
# End Section
# Section WinDE : {E9E07511-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcSeries
# 	2:10:HeaderFile:vcseries.h
# 	2:8:ImplFile:vcseries.cpp
# End Section
# Section WinDE : {E9E074F0-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcLight
# 	2:10:HeaderFile:vclight.h
# 	2:8:ImplFile:vclight.cpp
# End Section
# Section WinDE : {E9E074FC-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcWall
# 	2:10:HeaderFile:vcwall.h
# 	2:8:ImplFile:vcwall.cpp
# End Section
# Section WinDE : {E9E074E0-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcFrame
# 	2:10:HeaderFile:vcframe.h
# 	2:8:ImplFile:vcframe.cpp
# End Section
# Section WinDE : {E9E07515-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcAxisTitle
# 	2:10:HeaderFile:vcaxistitle.h
# 	2:8:ImplFile:vcaxistitle.cpp
# End Section
# Section WinDE : {E9E074C9-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcCoor
# 	2:10:HeaderFile:vccoor.h
# 	2:8:ImplFile:vccoor.cpp
# End Section
# Section WinDE : {E9E074E4-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcTitle
# 	2:10:HeaderFile:vctitle.h
# 	2:8:ImplFile:vctitle.cpp
# End Section
# Section WinDE : {E9E07525-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcAxis
# 	2:10:HeaderFile:vcaxis.h
# 	2:8:ImplFile:vcaxis.cpp
# End Section
# Section WinDE : {E9E0750C-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcDataPointLabel
# 	2:10:HeaderFile:vcdatapointlabel.h
# 	2:8:ImplFile:vcdatapointlabel.cpp
# End Section
# Section WinDE : {E9E074F4-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcPlotBase
# 	2:10:HeaderFile:vcplotbase.h
# 	2:8:ImplFile:vcplotbase.cpp
# End Section
# Section WinDE : {E9E074CB-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcLCoor
# 	2:10:HeaderFile:vclcoor.h
# 	2:8:ImplFile:vclcoor.cpp
# End Section
# Section WinDE : {E9E074CF-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcColor
# 	2:10:HeaderFile:vccolor.h
# 	2:8:ImplFile:vccolor.cpp
# End Section
# Section WinDE : {E9E074E8-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcLegend
# 	2:10:HeaderFile:vclegend.h
# 	2:8:ImplFile:vclegend.cpp
# End Section
# Section WinDE : {E9E074D8-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcFont
# 	2:10:HeaderFile:vcfont.h
# 	2:8:ImplFile:vcfont.cpp
# End Section
# Section WinDE : {E9E07504-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcSeriesMarker
# 	2:10:HeaderFile:vcseriesmarker.h
# 	2:8:ImplFile:vcseriesmarker.cpp
# End Section
# Section WinDE : {3A2B370C-BA0A-11D1-B137-0000F8753F5D}
# 	2:21:DefaultSinkHeaderFile:mschart.h
# 	2:16:DefaultSinkClass:CMSChart
# End Section
# Section WinDE : {E9E074DA-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcBrush
# 	2:10:HeaderFile:vcbrush.h
# 	2:8:ImplFile:vcbrush.cpp
# End Section
# Section WinDE : {E9E0751B-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcAxisGrid
# 	2:10:HeaderFile:vcaxisgrid.h
# 	2:8:ImplFile:vcaxisgrid.cpp
# End Section
# Section WinDE : {E9E074D3-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcMarker
# 	2:10:HeaderFile:vcmarker.h
# 	2:8:ImplFile:vcmarker.cpp
# End Section
# Section WinDE : {E9E07508-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcLabel
# 	2:10:HeaderFile:vclabel.h
# 	2:8:ImplFile:vclabel.cpp
# End Section
# Section WinDE : {E9E074EA-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcDataGrid
# 	2:10:HeaderFile:vcdatagrid.h
# 	2:8:ImplFile:vcdatagrid.cpp
# End Section
# Section WinDE : {E9E074FA-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcWeighting
# 	2:10:HeaderFile:vcweighting.h
# 	2:8:ImplFile:vcweighting.cpp
# End Section
# Section WinDE : {E9E0751F-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcTick
# 	2:10:HeaderFile:vctick.h
# 	2:8:ImplFile:vctick.cpp
# End Section
# Section WinDE : {E9E0752A-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcDataPoints
# 	2:10:HeaderFile:vcdatapoints.h
# 	2:8:ImplFile:vcdatapoints.cpp
# End Section
# Section WinDE : {E9E074EE-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcLightSources
# 	2:10:HeaderFile:vclightsources.h
# 	2:8:ImplFile:vclightsources.cpp
# End Section
# Section WinDE : {E9E074DE-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcFill
# 	2:10:HeaderFile:vcfill.h
# 	2:8:ImplFile:vcfill.cpp
# End Section
# Section WinDE : {E9E0750A-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcLabels
# 	2:10:HeaderFile:vclabels.h
# 	2:8:ImplFile:vclabels.cpp
# End Section
# Section WinDE : {E9E07513-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcSeriesCollection
# 	2:10:HeaderFile:vcseriescollection.h
# 	2:8:ImplFile:vcseriescollection.cpp
# End Section
# Section WinDE : {E9E07523-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcValueScale
# 	2:10:HeaderFile:vcvaluescale.h
# 	2:8:ImplFile:vcvaluescale.cpp
# End Section
