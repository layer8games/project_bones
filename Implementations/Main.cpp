#pragma comment(lib, "Killer_Engine_Win32_Debug.lib")

//===== Engine Includes =====
#include <Engine/Atom.h>
#include <Engine/Engine.h>
#include <Engine/ErrorManager.h>
#include <Engine/TextureManager.h>
#include <Engine/LevelManager.h>
#include <Engine/ShaderManager.h>
#include <Engine/AudioManager.h>

namespace KE = KillerEngine;

//===== Project Includes =====
#include <Game/ID_Database.h>
#include <Game/Battleground.h>

#include <vector>

int main()
{
	const S32 wndWidth = 1024;
	const S32 wndHeight = 768;
	const string wndTitle = "Project Bones - version 1";
	const bool wndFullScreen = false;

	KE::Engine::Instance()->Init(wndWidth, wndHeight, wndTitle, wndFullScreen);
	KE::ErrorManager::Instance()->DisplayErrors();

	//If User indicated they want to close they Game
	if(KE::ErrorManager::Instance()->DisplayErrors())
	{
		KE::Engine::Instance()->End();
	}

	std::vector<KE::ShaderData> shaderData;
	KE::ShaderData vertexShader;
	KE::ShaderData fragmentShader;

	vertexShader.filePath = "./Assets/Shaders/Default/sprite_vertex.glsl";
	vertexShader.type = KE::VERTEX;
	shaderData.push_back(vertexShader);

	fragmentShader.filePath = "./Assets/Shaders/Default/sprite_fragment.glsl";
	fragmentShader.type = KE::FRAGMENT;
	shaderData.push_back(fragmentShader);

	KE::ShaderManager::Instance()->LoadShader(KE::SPRITE, shaderData);

	KE::p_AudioClip battleMusicClip = make_shared<KE::AudioClip>();
	battleMusicClip->LoadWAV("./Assets/Audio/battle_v1.wav");

	KE::p_AudioSource backgroundSource = make_shared<KE::AudioSource>();
	backgroundSource->AddClip(battleMusicClip);
	backgroundSource->SetLooping(true);

	if(KE::ErrorManager::Instance()->DisplayErrors())
	{
		KE::Engine::Instance()->End();
	}

	KE::AudioManager::Instance()->AddClip(BATTLE_MUSIC, battleMusicClip);
	KE::AudioManager::Instance()->AddSource(BACKGROUND_MUSIC, backgroundSource);

	if(KE::ErrorManager::Instance()->DisplayErrors())
	{
		KE::Engine::Instance()->End();
	}

	KE::AudioManager::Instance()->PlaySource(BACKGROUND_MUSIC);

	KE::LevelManager::Instance()->SetActiveLevel( p_Battleground(new Battleground()));

	//If User indicated they want to close they Game
	if(KE::ErrorManager::Instance()->DisplayErrors())
	{
		KE::Engine::Instance()->End();
	}

	while (KE::Engine::Instance()->Running())
	{
		KE::Engine::Instance()->Update();
		KE::Engine::Instance()->Render();
	}
}
			