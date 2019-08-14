#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/GameObject.h>
#include <Engine/AABB.h>
#include <Engine/Timer.h>

namespace KE = KillerEngine;
namespace KC = KillerCollisions;

#include <iostream>

class I_Actor : public KE::GameObject
{
public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
	I_Actor(void);

	~I_Actor(void);

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
	inline virtual void v_Reset(void)
	{
		DefaultReset();
	}
	
	inline virtual void v_Damage(S32 dmg=1)
	{
		DefaultDamage(dmg);
	}

	inline virtual void v_Heal(S32 heal=1)
	{
		DefaultHeal(heal);
	}

	inline bool Alive(void)
	{
		return _alive;
	}

	inline void DefaultHeal(S32 heal)
	{
		if(_hp < _maxHP)
		{
			_hp += heal;
		}
	}

	inline S32 GetHP(void) const
	{
		return _hp;
	}

protected:
	void DefaultDamage(S32 dmg=1);

	void DefaultUpdate(void);

	void DefaultReset(void);

	bool	  _alive;
	S32 	  _hp;
	S32		  _maxHP;
	bool	  _isDmg;
	F32		  _dmgTime;
	F32		  _dmgCounter;
	KE::Color _dmgColor;

};//end Class
typedef shared_ptr<I_Actor> p_Actor;
