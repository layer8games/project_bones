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

namespace TE = Tempest;
namespace TM = TempestMath;

#include <Game/ID_Database.h>
#include <Game/Soldier.h>
#include <Game/Monster.h>
#include <Game/Settlement.h>
#include <Game/ObjectFactory.h>
#include <Game/Projectile.h>
#include <Game/EventManager.h>
#include <Game/HealthPack.h>
#include <Game/Armor.h>
#include <Game/Haste.h>
#include <Game/Knife.h>
#include <Game/Lazer.h>
#include <Game/Icon.h>

#include <vector>

typedef std::vector<p_Projectile> BulletPool;
typedef std::vector<p_Monster> MonsterPool;
typedef std::vector<p_HealthPack> HealthPackPool;
typedef std::vector<p_Armor> ArmorPool;
typedef std::vector<p_Haste> HastePool;
typedef std::vector<p_Knife> KnifePool;
typedef std::vector<p_Lazer> LazerPool;
typedef std::vector<p_Settlement> SettlementList;
typedef std::vector<TM::Point> MonsterSpawnZones;

class Battleground : public TE::Level
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

	F32 _GetRandomXPos(void);

//==========================================================================================================================
//
//Data
//
//==========================================================================================================================
	U32					 _killedThisRound;
	U32					 _roundNumber;
	U32					 _roundLength;
	U32					 _spawnsThisRound;
	U32					 _maxSpawn;
	U32					 _roundLengthIncrease;
	U32					 _projectilePoolSize;
	U32					 _monsterPoolSize;
	U32					 _settlementListSize;
	U32					 _defaultPoolSize;
	U32					 _score;
	S32					 _redSpawnRate;
	F32					 _spawnRate;
	F32					 _lastSpawn;
	F32					 _monsterWalkTimer;
	F32					 _monsterWalkCountdown;
	F32					 _settlementXOffset;
	bool				 _canSpawn;
	bool				 _spawnBlue;
	bool				 _gameover;
	p_Soldier			 _player;
	p_Icon				 _background;
	p_Icon				 _playerPath;
	BulletPool			 _projectilePool;
	MonsterPool			 _monsterPool;
	SettlementList		 _settlementList;
	HealthPackPool		 _healthPackPool;
	ArmorPool			 _armorPool;
	HastePool			 _hastePool;
	KnifePool			 _knifePool;
	LazerPool			 _lazerPool;
	MonsterSpawnZones	 _spawnZones;
	TE::AudioSource		 _monsterWalkAudioSource;
	TE::Font			 _font;
	TE::Text			 _roundTitleText;
	TE::Text			 _scoreTitleText;
	TE::Text			 _roundNumberText;
	TE::Text			 _scoreText;
	TE::Text			 _gameOverTitle;
	TE::Text			 _retryText;
	TM::Point			 _playerDefaultPos;
	TM::Point			 _defaultSettlementPos;

};//end Class

typedef shared_ptr<Battleground> p_Battleground;