#if DEBUG
#pragma comment(lib, "Tempest_Win32_Debug.lib")
#else
#pragma comment(lib, "Tempest_Win32_Release.lib")
#endif

//===== Engine Includes =====
#include <Engine/Atom.h>
#include <Engine/Engine.h>
#include <Engine/ErrorManager.h>
#include <Engine/TextureManager.h>
#include <Engine/LevelManager.h>
#include <Engine/ShaderManager.h>
#include <Engine/AudioManager.h>

namespace TE = Tempest;

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

	TE::Engine::Instance()->Init(wndWidth, wndHeight, wndTitle, wndFullScreen);

	//If User indicated they want to close they Game
	if(TE::ErrorManager::Instance()->DisplayErrors())
	{
		TE::Engine::Instance()->End();
	}

	std::vector<TE::ShaderData> shaderData;
	TE::ShaderData vertexShader;
	TE::ShaderData fragmentShader;

	vertexShader.filePath = "./Assets/Shaders/Default/sprite_vertex.glsl";
	vertexShader.type = TE::VERTEX;
	shaderData.push_back(vertexShader);

	fragmentShader.filePath = "./Assets/Shaders/Default/sprite_fragment.glsl";
	fragmentShader.type = TE::FRAGMENT;
	shaderData.push_back(fragmentShader);

	TE::ShaderManager::Instance()->LoadShader(TE::SPRITE, shaderData);

	//Load audio clips
	TE::p_AudioClip battleMusicClip = make_shared<TE::AudioClip>();
	battleMusicClip->LoadWAV2("./Assets/Audio/battle_v1.wav");
	TE::AudioManager::Instance()->AddClip(BATTLE_MUSIC_CLIP, battleMusicClip);

	TE::p_AudioClip monsterDamage = make_shared<TE::AudioClip>();
	monsterDamage->LoadWAV2("./Assets/Audio/monster_damage.wav");
	TE::AudioManager::Instance()->AddClip(MONSTER_DAMAGE_CLIP, monsterDamage);

	TE::p_AudioClip monsterDie = make_shared<TE::AudioClip>();
	monsterDie->LoadWAV2("./Assets/Audio/monster_die.wav");
	TE::AudioManager::Instance()->AddClip(MONSTER_DIE_CLIP, monsterDie);

	TE::p_AudioClip monsterSpawn = make_shared<TE::AudioClip>();
	monsterSpawn->LoadWAV2("./Assets/Audio/monster_spawn2.wav");
	TE::AudioManager::Instance()->AddClip(MONSTER_SPAWN_CLIP, monsterSpawn);

	TE::p_AudioClip monsterWalk = make_shared<TE::AudioClip>();
	monsterWalk->LoadWAV2("./Assets/Audio/monster_walk.wav");
	TE::AudioManager::Instance()->AddClip(MONSTER_WALK_CLIP, monsterWalk);

	TE::p_AudioClip playerDamage = make_shared<TE::AudioClip>();
	playerDamage->LoadWAV2("./Assets/Audio/player_damage.wav");
	TE::AudioManager::Instance()->AddClip(PLAYER_DAMAGE_CLIP, playerDamage);

	TE::p_AudioClip playerDeath = make_shared<TE::AudioClip>();
	playerDeath->LoadWAV2("./Assets/Audio/player_death.wav");
	TE::AudioManager::Instance()->AddClip(PLAYER_DIE_CLIP, playerDeath);

	TE::p_AudioClip playerDefaultFire = make_shared<TE::AudioClip>();
	playerDefaultFire->LoadWAV2("./Assets/Audio/player_default_fire.wav");
	TE::AudioManager::Instance()->AddClip(PLAYER_DEFAULT_FIRE_CLIP, playerDefaultFire);

	TE::p_AudioClip playerWalk = make_shared<TE::AudioClip>();
	playerWalk->LoadWAV2("./Assets/Audio/player_walk.wav");
	TE::AudioManager::Instance()->AddClip(PLAYER_WALK_CLIP, playerWalk);

	TE::p_AudioClip settlmentDamage = make_shared<TE::AudioClip>();
	settlmentDamage->LoadWAV2("./Assets/Audio/settlement_damage.wav");
	TE::AudioManager::Instance()->AddClip(SETTLEMENT_DAMAGE_CLIP, settlmentDamage);

	TE::p_AudioClip settlementDeath = make_shared<TE::AudioClip>();
	settlementDeath->LoadWAV2("./Assets/Audio/settlement_death.wav");
	TE::AudioManager::Instance()->AddClip(SETTLEMENT_DIE_CLIP, settlementDeath);

	if(TE::ErrorManager::Instance()->DisplayErrors())
	{
		TE::Engine::Instance()->End();
	}

	//Create gloabl sources
	TE::p_AudioSource backgroundSource = make_shared<TE::AudioSource>();
	backgroundSource->AddClip(battleMusicClip);
	backgroundSource->SetLooping(true);
	TE::AudioManager::Instance()->AddSource(BACKGROUND_MUSIC_SOURCE, backgroundSource);

	TE::p_AudioSource monsterDamgeSrc = make_shared<TE::AudioSource>();
	monsterDamgeSrc->AddClip(monsterDamage);
	TE::AudioManager::Instance()->AddSource(MONSTER_DAMAGE_SOURCE, monsterDamgeSrc);

	TE::p_AudioSource monsterSpawnSrc = make_shared<TE::AudioSource>();
	monsterSpawnSrc->AddClip(monsterSpawn);
	TE::AudioManager::Instance()->AddSource(MONSTER_SPAWN_SOURCE, monsterSpawnSrc);

	TE::p_AudioSource monsterWalkSrc = make_shared<TE::AudioSource>();
	monsterWalkSrc->AddClip(monsterWalk);
	TE::AudioManager::Instance()->AddSource(MONSTER_WALK_SOURCE, monsterWalkSrc);

	if(TE::ErrorManager::Instance()->DisplayErrors())
	{
		TE::Engine::Instance()->End();
	}	

	TE::LevelManager::Instance()->SetActiveLevel( p_Battleground(new Battleground()));

	//If User indicated they want to close they Game
	if(TE::ErrorManager::Instance()->DisplayErrors())
	{
		TE::Engine::Instance()->End();
	}

	while (TE::Engine::Instance()->Running())
	{
		TE::Engine::Instance()->Update();
		TE::Engine::Instance()->Render();
	}
}
			