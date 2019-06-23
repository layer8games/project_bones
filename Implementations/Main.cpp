#pragma comment(lib, "Killer_Engine_Win32_Debug.lib")

//===== Engine Includes =====
#include <Engine/Atom.h>
#include <Engine/Engine.h>
#include <Engine/ErrorManager.h>
#include <Engine/TextureManager.h>

namespace KE = KillerEngine;

//===== Project Includes =====
#include <Game/ID_Database.h>

int main()
{
	const S32 wndWidth = 1024;
	const S32 wndHeight = 768;
	const string wndTitle = "Project Bones - version 1";
	const bool wndFullScreen = false;

	KE::Engine::Instance()->Init(wndWidth, wndHeight, wndTitle, wndFullScreen);
	KE::ErrorManager::Instance()->DisplayErrors();

	KE::TextureManager::Instance()->LoadTexture(SOLDIER, "./Assets/Textures/soldier_v1.png");
	KE::TextureManager::Instance()->LoadTexture(YELLOW_MONSTER, "./Assets/Textures/monster_yellow_v1.png");

	KE::ErrorManager::Instance()->DisplayErrors();
}
