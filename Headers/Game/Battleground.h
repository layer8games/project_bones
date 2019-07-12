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

namespace KE = KillerEngine;
namespace KM = KillerMath;

#include <Game/ID_Database.h>
#include <Game/Soldier.h>
#include <Game/Monster.h>
#include <Game/Settlement.h>
#include <Game/ObjectFactory.h>
#include <Game/Projectile.h>

#include <vector>

typedef std::vector<p_Projectile> BulletPool;
typedef std::vector<p_Monster> MonsterPool;
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

//==========================================================================================================================
//
//Data
//
//==========================================================================================================================
	U32			   _projectilePoolSize;
	U32			   _monsterPoolSize;
	U32			   _settlementListSize;
	F32			   _spawnRate;
	F32			   _lastSpawn;
	bool		   _canSpawn;
	U32			   _spawnAmount;
	p_Soldier	   _player;
	BulletPool	   _projectilePool;
	MonsterPool	   _monsterPool;
	SettlementList _settlementList;
	MonsterSpawnZones _spawnZones;

};//end Class

typedef shared_ptr<Battleground> p_Battleground;