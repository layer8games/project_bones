#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/GameObject.h>
#include <Engine/AABB.h>
#include <Engine/Point.h>
#include <Engine/ErrorManager.h>
#include <Engine/TextureManager.h>
#include <Engine/Vector3.h>
#include <Engine/Random.h>
#include <Engine/Timer.h>
#include <Engine/AudioManager.h>
#include <Engine/AudioSource.h>

namespace TE = Tempest;
namespace TC = TempestCollisions;
namespace TM = TempestMath;

//===== Game Includes =====
#include <Game/I_Actor.h>
#include <Game/ID_Database.h>
#include <Game/EventManager.h>

//===== STL Includes =====
#include <vector>

//==========================================================================================================================
//Potential Target 
//==========================================================================================================================
struct PotentialTarget
{
	p_Actor target = nullptr;
	S32				 weight = 0;
};

typedef std::vector<PotentialTarget> PotentialTargetList;

//==========================================================================================================================
//Monster 
//==========================================================================================================================
class Monster : public I_Actor
{
public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
	Monster(void);

	~Monster(void);

//==========================================================================================================================
//
//Virtal Functions
//
//==========================================================================================================================
	void v_Update(void);

	void v_Damage(S32 dmg = 1) final;

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
	void Setup(MonsterAIType type, TM::Point pos);

//==========================================================================================================================
//
//AI Functions
//
//==========================================================================================================================
	void Choose(PotentialTargetList targetList);

	inline void SetTarget(p_Actor target)
	{
		_target = target;
	}
	
	void Seek(void);

	void Attack(void);

	void Attack(const p_Actor target);

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
	inline U32 GetPointValue(void) const
	{
		return _pointValue;
	}

	inline void SetPointValue(U32 val)
	{
		_pointValue = val;
	}

	inline void SetAIState(MonsterAIState state)
	{
		_aiState = state;
	}
	
	inline MonsterAIState GetAIState(void) const
	{
		return _aiState;
	}

	inline MonsterAIType GetType(void) const
	{
		return _aiType;
	}

private:
	U32					_damage;
	F32					_speed;
	bool				_canAttack;
	F32					_attackRate;
	F32					_lastAttack;
	U32					_pointValue;
	F32					_attackRange;
	F32					_shuffleDir;
	MonsterAIState		_aiState;
	MonsterAIType		_aiType;
	p_Actor				_target;
	TM::Vector3			_movementDirection;
	TE::AudioSource		_deathAudioSource;
};//end Class

typedef shared_ptr<Monster> p_Monster;
