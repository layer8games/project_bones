#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/GameObject.h>
#include <Engine/AABB.h>

namespace KE = KillerEngine;
namespace KC = KillerCollisions;

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
		_dmg = val;
	}

	inline U32 GetPointValue(void) const
	{
		return _pointValue;
	}

	inline void SetPointValue(U32 val)
	{
		_pointValue = val;
	}

private:
	U32		 _hp;
	U32		 _dmg;
	F32		 _speed;
	F32		 _attackRate;
	U32		 _pointValue;
	KC::AABB _boundingBox;
};//end Class

typedef shared_ptr<Monster> p_Monster;
