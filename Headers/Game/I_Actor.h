#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/GameObject.h>

namespace KE = KillerEngine;

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
	inline bool Alive(void)
	{
		return _alive;
	}
	
	inline virtual void v_Damage(S32 dmg=1)
	{
		DefaultDamage(dmg);
	}

	inline void Heal(S32 heal)
	{
		_hp += heal;
	}

	inline S32 GetHP(void) const
	{
		return _hp;
	}

protected:
	inline void DefaultDamage(S32 dmg = 1)
	{
		_hp -= dmg;

		if(_hp <= 0)
		{
			_alive = false;
		}
	}

	bool	 _alive;
	S32 	 _hp;
};//end Class
typedef shared_ptr<I_Actor> p_Actor;
