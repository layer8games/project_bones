OutFile "install_bones_.exe"

!define pathToGame ".\ProjectBonesRelease"
!define regKeyName "Software\Microsoft\Windows\CurrentVersion\Uninstall\ProjectBone"
InstallDir "C:\Program Files (x86)\Project_Bones" 
 
Section 
	SetOutPath $INSTDIR
	File /r ${pathToGame}\*
	WriteUninstaller $INSTDIR\uninstaller.exe
SectionEnd

Section Desktop
	MessageBox MB_YESNO "Create a Desktop Shortcut?" /SD IDYES IDNO end
	CreateShortcut "$desktop\ProjectBones.lnk" "$instdir\project_bones.exe"
	WriteRegStr HKLM ${regKeyName} "Project Bones" "Created by Layer8 Games, this arcade shooter will mystify and terrify."
	WriteRegStr HKLM ${regKeyName} "Remove Project Bones" "$\"$INSTDIR\uninstaller.exe$\""
	end:
SectionEnd

Section -Prerequisites
	MessageBox MB_YESNO "Install OpenAL32?" /SD IDYES IDNO end
	  File ${pathToGame}\OpenAL\oalinst.exe 
	  ExecWait "$INSTDIR\OpenAL\oalinst.exe"
	end:
SectionEnd

Section "Uninstall"
	RMdir /r $INSTDIR\Assets
	RMdir /r $INSTDIR\OpenAL
	delete "$desktop\ProjectBones.lnk"
	delete $INSTDIR\*
	RMdir $INSTDIR
	DeleteRegKey HKLM ${regKeyName}
SectionEnd