#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/GameObject.h>
#include <Engine/AABB.h>
#include <Engine/Timer.h>
#include <Engine/Point.h>
#include <Engine/TextureManager.h>

namespace KE = KillerEngine;
namespace KC = KillerCollisions;
namespace KM = KillerMath;

#include <Game/ID_Database.h>
#include <Game/I_Actor.h>

enum ProjectileType
{
	DO_NOTHING = 0,
	BULLET = 1,
};

class Projectile : public KE::GameObject
{
public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
	Projectile(void);

	~Projectile(void);

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
	void v_Update(void) final;

//==========================================================================================================================
//
//Fucntions and Accessors
//
//==========================================================================================================================
	void SetUp(ProjectileType type);

	void Fire(const KM::Point& pos);
	
	inline void SetDamage(U32 dmg)
	{
		_damage = dmg;
	}

	inline U32 GetDamage(void) const
	{
		return _damage;
	}

	inline void HitEnemy(void)
	{
		--_numEnemies;
	}

	inline void SetRange(F32 range)
	{
		_range = range;
	}

	inline F32 GetRange(void) const
	{
		return _range;
	}

	inline void SetForwardVelocity(F32 vel)
	{
		_forwardVelocity = vel;
	}

	inline F32 GetForwardVelocity(void) const
	{
		return _forwardVelocity;
	}

	inline bool OverlapCheck(const shared_ptr<I_Actor> other)
	{
		return _boundingBox.TestCollision(other->GetBounding());
	}

	inline const KC::AABB& GetBounding(void) const
	{
		return _boundingBox;
	}

private:
	U32 _damage;
	S32 _numEnemies; 
	F32 _range;
	F32 _distTraveled;
	F32 _forwardVelocity;
	KC::AABB _boundingBox;
	ProjectileType _activeType;
};//end Class
typedef shared_ptr<Projectile> p_Projectile;
