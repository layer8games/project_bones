#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/GameObject.h>
#include <Engine/AABB.h>
#include <Engine/Timer.h>

namespace KE = KillerEngine;
namespace KC = KillerCollisions;
namespace KM = KillerMath;

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
private:
	U32 _damage;
	F32 _range;
	F32 _forwardVelocity;
	KC::AABB _boundingBox;
};//end Class
