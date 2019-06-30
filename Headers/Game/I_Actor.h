#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/GameObject.h>
#include <Engine/AABB.h>
#include <Engine/Timer.h>

namespace KE = KillerEngine;
namespace KC = KillerCollisions;

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
	void v_Awake(void) final
	{
		_boundingBox.SetCenter(_position);
		_boundingBox.SetHalfDimensions(_scale);
	}
	
	//virtual void v_OnCollision(void)=0;
	
	inline virtual void v_Damage(S32 dmg=1)
	{
		DefaultDamage(dmg);
	}

	inline bool Alive(void)
	{
		return _alive;
	}

	inline void Heal(S32 heal)
	{
		_hp += heal;
	}

	inline S32 GetHP(void) const
	{
		return _hp;
	}

	inline bool OverlapCheck(const shared_ptr<I_Actor> other)
	{
		return _boundingBox.TestCollision(other->GetBounding());
	}

	inline const KC::AABB& GetBounding(void) const
	{
		return _boundingBox;
	}

protected:
	void DefaultDamage(S32 dmg=1);

	void DefaultUpdate(void);

	bool	  _alive;
	S32 	  _hp;
	bool	  _isDmg;
	F32		  _dmgTime;
	F32		  _dmgCounter;
	KE::Color _dmgColor;
	KC::AABB  _boundingBox;

};//end Class
typedef shared_ptr<I_Actor> p_Actor;
