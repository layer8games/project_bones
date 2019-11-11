OutFile "install.exe"

!define pathToGame ".\ProjectBonesRelease\"
InstallDir "C:\Program Files (x86)\Project_Bones" 
 
Section 
	SetOutPath $INSTDIR
	File /r ${pathToGame}\*
	WriteUninstaller $INSTDIR\uninstaller.exe
SectionEnd

Section Desktop
	MessageBox MB_YESNO "Create a Desktop Shortcut?" /SD IDYES IDNO end
	CreateShortcut "$desktop\myapp.lnk" "$instdir\project_bones.exe"
	# add registry entry
	end:
SectionEnd

Section -Prerequisites
	SetOutPath $INSTDIR\OpenAL32
	MessageBox MB_YESNO "Install OpenAL32?" /SD IDYES IDNO end

	# put into its own box
	File ${pathToGame}\dependencies\oalinst.exe
	ExecWait ${pathToGame}\dependencies\oalinst.exe
	end:
SectionEnd

Section "Uninstall"
	Delete $INSTDIR\uninstaller.exe
	Delete $INSTDIR
	# delete short cut
	# delete registry entry
SectionEnd