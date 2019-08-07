#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/Level.h>
#include <Engine/GameWindow.h>
#include <Engine/Controller.h>
#include <Engine/Engine.h>
#include <Engine/TextureManager.h>
#include <Engine/ErrorManager.h>
#include <Engine/Point.h>
#include <Engine/Random.h>
#include <Engine/AudioManager.h>
#include <Engine/AudioSource.h>
#include <Engine/Font.h>
#include <Engine/Text.h>

namespace KE = KillerEngine;
namespace KM = KillerMath;

#include <Game/ID_Database.h>
#include <Game/Soldier.h>
#include <Game/Monster.h>
#include <Game/Settlement.h>
#include <Game/ObjectFactory.h>
#include <Game/Projectile.h>
#include <Game/EventManager.h>
#include <Game/HealthPack.h>

#include <vector>

typedef std::vector<p_Projectile> BulletPool;
typedef std::vector<p_Monster> MonsterPool;
typedef std::vector<p_HealthPack> HealthPackPool;
typedef std::vector<p_Settlement> SettlementList;
typedef std::vector<KM::Point> MonsterSpawnZones;

class Battleground : public KE::Level
{
public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
	Battleground(void);

	~Battleground(void);

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
	void v_Init(void) final;

	void v_Update(void) final;

private:
//==========================================================================================================================
//
//Private Functions
//
//==========================================================================================================================	
	void _Spawn(U32 amount, MonsterAIType type);

	void _ProcessCollisions(void);

	void _ProcessEvents(void);

	void _ProcessInput(void);
	
	void _ProcessAI(void);

	bool _SpawnItem(ItemType type);

	void _ResetLevel(void);

//==========================================================================================================================
//
//Data
//
//==========================================================================================================================
	U32			   _roundNumber;
	U32			   _killedThisRound;
	U32			   _roundLength;
	U32			   _spawnsThisRound;
	U32			   _maxSpawn;
	U32			   _roundLengthIncrease;
	U32			   _projectilePoolSize;
	U32			   _monsterPoolSize;
	U32			   _settlementListSize;
	U32			   _score;
	U32			   _healthPackPoolSize;
	F32			   _spawnRate;
	F32			   _lastSpawn;
	F32			   _monsterWalkTimer;
	F32			   _monsterWalkCountdown;
	bool		   _canSpawn;
	bool		   _gameover;
	p_Soldier	   _player;
	BulletPool	   _projectilePool;
	MonsterPool	   _monsterPool;
	HealthPackPool _healthPackPool;
	SettlementList _settlementList;
	MonsterSpawnZones _spawnZones;
	KE::AudioSource		_monsterWalkAudioSource;
	KE::Font			_font;
	KE::Text			_roundTitleText;
	KE::Text			_scoreTitleText;
	KE::Text			_roundNumberText;
	KE::Text			_scoreText;
	KE::Text			_gameOverTitle;
	KE::Text			_retryText;
	KM::Point			_playerDefaultPos;

};//end Class

typedef shared_ptr<Battleground> p_Battleground;