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

	//Load audio clips
	KE::p_AudioClip battleMusicClip = make_shared<KE::AudioClip>();
	battleMusicClip->LoadWAV2("./Assets/Audio/battle_v1.wav");
	KE::AudioManager::Instance()->AddClip(BATTLE_MUSIC_CLIP, battleMusicClip);

	KE::p_AudioClip monsterDamage = make_shared<KE::AudioClip>();
	monsterDamage->LoadWAV2("./Assets/Audio/monster_damage.wav");
	KE::AudioManager::Instance()->AddClip(MONSTER_DAMAGE_CLIP, monsterDamage);

	KE::p_AudioClip monsterDie = make_shared<KE::AudioClip>();
	monsterDie->LoadWAV2("./Assets/Audio/monster_die.wav");
	KE::AudioManager::Instance()->AddClip(MONSTER_DIE_CLIP, monsterDie);

	KE::p_AudioClip monsterSpawn = make_shared<KE::AudioClip>();
	monsterSpawn->LoadWAV2("./Assets/Audio/monster_spawn2.wav");
	KE::AudioManager::Instance()->AddClip(MONSTER_SPAWN_CLIP, monsterSpawn);

	KE::p_AudioClip monsterWalk = make_shared<KE::AudioClip>();
	monsterWalk->LoadWAV2("./Assets/Audio/monster_walk.wav");
	KE::AudioManager::Instance()->AddClip(MONSTER_WALK_CLIP, monsterWalk);

	KE::p_AudioClip playerDamage = make_shared<KE::AudioClip>();
	playerDamage->LoadWAV2("./Assets/Audio/player_damage.wav");
	KE::AudioManager::Instance()->AddClip(PLAYER_DAMAGE_CLIP, playerDamage);

	KE::p_AudioClip playerDeath = make_shared<KE::AudioClip>();
	playerDeath->LoadWAV2("./Assets/Audio/player_death.wav");
	KE::AudioManager::Instance()->AddClip(PLAYER_DIE_CLIP, playerDeath);

	KE::p_AudioClip playerDefaultFire = make_shared<KE::AudioClip>();
	playerDefaultFire->LoadWAV2("./Assets/Audio/player_default_fire.wav");
	KE::AudioManager::Instance()->AddClip(PLAYER_DEFAULT_FIRE_CLIP, playerDefaultFire);

	KE::p_AudioClip playerWalk = make_shared<KE::AudioClip>();
	playerWalk->LoadWAV2("./Assets/Audio/player_walk.wav");
	KE::AudioManager::Instance()->AddClip(PLAYER_WALK_CLIP, playerWalk);

	KE::p_AudioClip settlmentDamage = make_shared<KE::AudioClip>();
	settlmentDamage->LoadWAV2("./Assets/Audio/settlement_damage.wav");
	KE::AudioManager::Instance()->AddClip(SETTLEMENT_DAMAGE_CLIP, settlmentDamage);

	KE::p_AudioClip settlementDeath = make_shared<KE::AudioClip>();
	settlementDeath->LoadWAV2("./Assets/Audio/settlement_death.wav");
	KE::AudioManager::Instance()->AddClip(SETTLEMENT_DIE_CLIP, settlementDeath);

	if(KE::ErrorManager::Instance()->DisplayErrors())
	{
		KE::Engine::Instance()->End();
	}

	//Create gloabl sources
	KE::p_AudioSource backgroundSource = make_shared<KE::AudioSource>();
	backgroundSource->AddClip(battleMusicClip);
	backgroundSource->SetLooping(true);
	KE::AudioManager::Instance()->AddSource(BACKGROUND_MUSIC_SOURCE, backgroundSource);

	KE::p_AudioSource monsterDamgeSrc = make_shared<KE::AudioSource>();
	monsterDamgeSrc->AddClip(monsterDamage);
	KE::AudioManager::Instance()->AddSource(MONSTER_DAMAGE_SOURCE, monsterDamgeSrc);

	KE::p_AudioSource monsterSpawnSrc = make_shared<KE::AudioSource>();
	monsterSpawnSrc->AddClip(monsterSpawn);
	KE::AudioManager::Instance()->AddSource(MONSTER_SPAWN_SOURCE, monsterSpawnSrc);

	KE::p_AudioSource monsterWalkSrc = make_shared<KE::AudioSource>();
	monsterWalkSrc->AddClip(monsterWalk);
	KE::AudioManager::Instance()->AddSource(MONSTER_WALK_SOURCE, monsterWalkSrc);

	if(KE::ErrorManager::Instance()->DisplayErrors())
	{
		KE::Engine::Instance()->End();
	}	

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
			