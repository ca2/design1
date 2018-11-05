; example2.nsi
;
; This script is based on example1.nsi, but it remember the directory, 
; has uninstall support and (optionally) installs start menu shortcuts.
;
; It will install example2.nsi into a directory that the user selects,

;--------------------------------


;!include "${NSISDIR}\Contrib\Modern UI\System.nsh"
!include x64.nsh
;!define MUI_ICON "M:\stage\app-ca2\appmatter\app_core_textformat\_std\_std\main\icon.ico"

	!define /date MyTIMESTAMP "%Y-%m-%d-%H-%M-%S"
	!define MUI_PRODUCT "Text Format!! ${MyTIMESTAMP}" 
	Name "Text Format!! ${MyTIMESTAMP}"
	
;--------------------------------
;General

	;Properly display all languages (Installer will not work on Windows 95, 98 or ME!)
	Unicode true


; The default installation directory
InstallDir "$PROGRAMFILES\app_core_textformat"

; The file to write
OutFile "C:\\netnodenet\\net\\front\\ca2\\_std\\_std\\exe\\app-core\\textformat.exe"


; Registry key to check for directory (so if you install again, it will 
; overwrite the old one automatically)
InstallDirRegKey HKLM "Software\ca2\app-ca2\app_core_textformat" "Install_Dir"

; Request application privileges for Windows Vista
RequestExecutionLevel admin

;--------------------------------

; Pages

Page directory
Page instfiles

UninstPage uninstConfirm
UninstPage instfiles

;--------------------------------

; The stuff to install
Section "app_core_textformat (required)"

  SectionIn RO

  ; Set output path to the installation directory.
  SetOutPath "$INSTDIR\app\appmatter\main"
  
  ; Put file there
  File /r "M:\stage\app\appmatter\main\"
  
  ; Set output path to the installation directory.
  SetOutPath "$INSTDIR\app-core\appmatter\textformat"
  
  ; Put file there
  File /r "M:\stage\app-core\appmatter\textformat\"

  ; Set output path to the installation directory.
  SetOutPath "$INSTDIR\time\x86\stage"
  
  ; Put file there
  File "M:\stage\time\Win32\stage\ace.dll"
  File "M:\stage\time\Win32\stage\aqua.dll"
  File "M:\stage\time\Win32\stage\aura.dll"
  File "M:\stage\time\Win32\stage\axis.dll"
  File "M:\stage\time\Win32\stage\base.dll"
  File "M:\stage\time\Win32\stage\core.dll"
  File "M:\stage\time\Win32\stage\gcom.dll"
  File "M:\stage\time\Win32\stage\sphere.dll"
  File "M:\stage\time\Win32\stage\draw2d_gdiplus.dll"
  File "M:\stage\time\Win32\stage\wndfrm_core.dll"
  File "M:\stage\time\Win32\stage\libcrypto-1_1.dll"
  File "M:\stage\time\Win32\stage\libssl-1_1.dll"
  File "M:\stage\time\Win32\stage\png.dll"
  File "M:\stage\time\Win32\stage\jpeg.dll"
  File "M:\stage\time\Win32\stage\pcre.dll"
  File "M:\stage\time\Win32\stage\sqlite.dll"
  File "M:\stage\time\Win32\stage\zlib.dll"
  File "M:\stage\time\Win32\stage\bzip2.dll"
  File "M:\stage\time\Win32\stage\app_core_textformat.dll"
  File "M:\stage\time\Win32\stage\app_core_textformat.exe"
  File "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Redist\MSVC\14.13.26020\vc_redist.x86.exe"
  
${If} ${Runningx64}
	ReadRegStr $1 HKLM "SOFTWARE\Wow6432Node\Microsoft\VisualStudio\14.0\VC\Runtimes\x86" "Installed"
	StrCmp $1 1 installed_redist
${Else}
	ReadRegStr $1 HKLM "SOFTWARE\Microsoft\VisualStudio\14.0\VC\Runtimes\x86" "Installed"
	StrCmp $1 1 installed_redist
${EndIf}

  ;not installed, so run the installer
  ExecWait  '"$INSTDIR\time\x86\stage\vc_redist.x86.exe" /install /passive /norestart'

installed_redist:

  ;we are done
  ExecWait '"$INSTDIR\time\x86\stage\app_core_textformat.exe" : install' $0
  
  ; Write the installation path into the registry
  WriteRegStr HKLM "SOFTWARE\ca2\app-ca2\app_core_textformat" "Install_Dir" "$INSTDIR"
  
  ; Write the uninstall keys for Windows
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\app_core_textformat" "DisplayName" "Text Format!!"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\app_core_textformat" "UninstallString" '"$INSTDIR\uninstall.exe"'
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\app_core_textformat" "NoModify" 1
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\app_core_textformat" "NoRepair" 1
  WriteUninstaller "uninstall.exe"
  
  CreateShortCut "$DESKTOP\Text Format!!.lnk" "$INSTDIR\time\x86\stage\app_core_textformat.exe" ""

  
SectionEnd

; Optional section (can be disabled by the user)
Section "Start Menu Shortcuts"

  CreateDirectory "$SMPROGRAMS\Text Format!!"
  CreateShortcut "$SMPROGRAMS\Text Format!!\Uninstall.lnk" "$INSTDIR\uninstall.exe" "" "$INSTDIR\uninstall.exe" 0
  CreateShortcut "$SMPROGRAMS\Text Format!!\Text Format!!.lnk" "$INSTDIR\time\x86\stage\app_core_textformat.exe" "" "$INSTDIR\time\x86\stage\app_core_textformat.exe" 0
  
SectionEnd

;--------------------------------

; Uninstaller

Section "Uninstall"
  
  ; Remove registry keys
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\app_core_textformat"
  DeleteRegKey HKLM "SOFTWARE\ca2\app-ca2\app_core_textformat"

  ; Remove files and uninstaller
  Delete "$INSTDIR\app_core_textformat.nsi"
  Delete "$INSTDIR\uninstall.exe"

  ; Remove shortcuts, if any
  Delete "$SMPROGRAMS\Text Format!!\*.*"

  ; Remove directories used
  RMDir "$SMPROGRAMS\app_core_textformat"
  RMDir /r "$INSTDIR/time"
  RMDir "$INSTDIR"

SectionEnd
