#pragma comment(lib, "Killer_Engine_Win32_Debug.lib")

//===== Engine Includes =====
#include <Engine/Atom.h>
#include <Engine/Engine.h>
#include <Engine/ErrorManager.h>

namespace KE = KillerEngine;

int main()
{
	const S32 wndWidth = 1024;
	const S32 wndHeight = 768;
	const string wndTitle = "Project Bones - version 1";
	const bool wndFullScreen = false;

	KE::Engine::Instance()->Init(wndWidth, wndHeight, wndTitle, wndFullScreen);
	KE::ErrorManager::Instance()->DisplayErrors();
}