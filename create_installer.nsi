OutFile "install_bones.exe"

!define pathToGame ".\ProjectBonesRelease"
InstallDir "C:\Program Files (x86)\Project_Bones" 
 
Section 
	SetOutPath $INSTDIR
	File /r ${pathToGame}\*
	WriteUninstaller $INSTDIR\uninstaller.exe
SectionEnd

Section Desktop
	MessageBox MB_YESNO "Create a Desktop Shortcut?" /SD IDYES IDNO end
	CreateShortcut "$desktop\ProjectBones.lnk" "$instdir\project_bones.exe"
	# add registry entry
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

	# delete short cut
	# delete registry entry
SectionEnd