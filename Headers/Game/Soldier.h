#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/GameObject.h>
#include <Engine/Timer.h>
#include <Engine/ErrorManager.h>
#include <Engine/AABB.h>

namespace KE = KillerEngine;
namespace KM = KillerMath;
namespace KC = KillerCollisions;


class Soldier : public KE::GameObject
{
public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
	Soldier(void);

	~Soldier(void);

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
	void v_Update(void) final;

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
	inline void Damage(U32 dmg=1)
	{
		_hp -= dmg;
	}

	inline void Heal(U32 health=1)
	{
		_hp += health;
	}

	void Fire(void);

	void Move(F32 xVal)
	{
		_position[x] += xVal * _speed * KM::Timer::Instance()->DeltaTime();
		_boundingBox.SetCenter(GameObject::_position);
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

	inline void SetSpeed(F32 speed)
	{
		if(speed < 0.0f)
		{
			KE::ErrorManager::Instance()->SetError(KE::APPLICATION, "Soldier::SetSpeed: Attempted to set speed less than 0");
			return;
		}

		_speed = speed; 
	}

private:
	U32 	 _hp;
	F32 	 _speed;
	F32 	 _attackRate;
	KC::AABB _boundingBox;

};//end Class

typedef shared_ptr<Soldier> p_Soldier;
