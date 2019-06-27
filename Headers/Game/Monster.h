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

namespace KE = KillerEngine;
namespace KC = KillerCollisions;
namespace KM = KillerMath;

//===== Game Includes =====
#include <Game/ID_Database.h>

//===== STL Includes =====
#include <vector>

//==========================================================================================================================
//Potential Target 
//==========================================================================================================================
struct PotentialTarget
{
	KE::p_GameObject target = nullptr;
	S32				 weight = 0;
};

typedef std::vector<PotentialTarget> PotentialTargetList;

//==========================================================================================================================
//Monster 
//==========================================================================================================================
class Monster : public KE::GameObject
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

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
	inline void Damage(U32 dmg=1)
	{
		_hp -= dmg;
	}

	void Setup(MonsterAIType type, KM::Point pos);

//==========================================================================================================================
//
//AI Functions
//
//==========================================================================================================================
	void Choose(PotentialTargetList targetList);
	
	void Seek(void);

	void Attack(void);

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
	inline U32 GetHP(void) const
	{
		return _hp;
	}

	inline void SetDamage(U32 val)
	{
		_damage = val;
	}

	inline U32 GetPointValue(void) const
	{
		return _pointValue;
	}

	inline void SetPointValue(U32 val)
	{
		_pointValue = val;
	}

	inline MonsterAIState GetAIState(void) const
	{
		return _aiState;
	}

private:
	U32					_hp;
	U32					_damage;
	F32					_speed;
	F32					_attackRate;
	U32					_pointValue;
	KC::AABB			_boundingBox;
	MonsterAIState		_aiState;
	MonsterAIType		_aiType;
	KE::p_GameObject	_target;
	KM::Vector3			_movementDirection;
};//end Class

typedef shared_ptr<Monster> p_Monster;
