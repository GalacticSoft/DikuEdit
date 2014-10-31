; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

[Setup]
AppName=Basternae Area Editor
AppVerName=Basternae Area Editor 1.91
AppPublisher=Holroyd Computing
AppPublisherURL=http://www.geocities.com/tyrus182/downloads
AppSupportURL=http://www.geocities.com/tyrus182/downloads
AppUpdatesURL=http://www.geocities.com/tyrus182/downloads
DefaultDirName=c:\Basternae Area Editor
DefaultGroupName=Basternae Area Editor
AllowNoIcons=yes
Compression=lzma
SolidCompression=yes
ChangesAssociations=yes
SetupIconFile=c:\install.ico

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked
Name: "quicklaunchicon"; Description: "{cm:CreateQuickLaunchIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "C:\WinDE\Release\Basternae Area Editor.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\WinDE\Release\Output\Generic_Vnums_v2.txt"; DestDir: "{app}\docs"; Flags: ignoreversion
Source: "C:\WinDE\Release\Output\Keywords.txt"; DestDir: "{app}\docs"; Flags: ignoreversion
Source: "C:\WinDE\Release\Output\Zone_Checklist_v1.txt"; DestDir: "{app}\docs"; Flags: ignoreversion
Source: "C:\WinDE\Release\Output\Zone_Information_v9.txt"; DestDir: "{app}\docs"; Flags: ignoreversion
Source: "C:\WinDE\Release\Output\mobprogs.txt"; DestDir: "{app}\progs"; Flags: ignoreversion
Source: "C:\WinDE\Release\Output\Beggar.prg"; DestDir: "{app}\progs"; Flags: ignoreversion
Source: "C:\WinDE\Release\Output\Child.prg"; DestDir: "{app}\progs"; Flags: ignoreversion
Source: "C:\WinDE\Release\Output\Executioner.prg"; DestDir: "{app}\progs"; Flags: ignoreversion
Source: "C:\WINDOWS\system32\MSCHRT20.OCX"; DestDir: "{sys}"; CopyMode: alwaysskipifsameorolder; Flags: restartreplace sharedfile regserver
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Registry]
Root: HKCR; Subkey: ".are"; ValueType: string; ValueName: ""; ValueData: "Area File"; Flags: uninsdeletevalue
Root: HKCR; Subkey: "Area File"; ValueType: string; ValueName: ""; ValueData: "Area File"; Flags: uninsdeletekey
Root: HKCR; Subkey: "Area File\DefaultIcon"; ValueType: string; ValueName: ""; ValueData: "{app}\Basternae Area Editor.EXE,33"
Root: HKCR; Subkey: "Area File\shell\open\command"; ValueType: string; ValueName: ""; ValueData: """{app}\Basternae Area Editor.EXE"" %1"

[Icons]
Name: "{group}\Basternae Area Editor"; Filename: "{app}\Basternae Area Editor.exe"
Name: "{group}\{cm:UninstallProgram,Basternae Area Editor}"; Filename: "{uninstallexe}"
Name: "{userdesktop}\Basternae Area Editor"; Filename: "{app}\Basternae Area Editor.exe"; Tasks: desktopicon
Name: "{userappdata}\Microsoft\Internet Explorer\Quick Launch\Basternae Area Editor"; Filename: "{app}\Basternae Area Editor.exe"; Tasks: quicklaunchicon

[Run]
Filename: "{app}\Basternae Area Editor.exe"; Description: "{cm:LaunchProgram,Basternae Area Editor}"; Flags: nowait postinstall skipifsilent
