#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/GameObject.h>
#include <Engine/AABB.h>
#include <Engine/Color.h>
#include <Engine/Timer.h>

namespace KE = KillerEngine;
namespace KC = KillerCollisions;
namespace KM = KillerMath;

//===== Game Includes =====
#include <Game/I_Actor.h>

class Settlement : public I_Actor 
{
public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
	Settlement(void);

	~Settlement(void);

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
	void v_Update(void) final;

	void v_Damage(S32 dmg) final;

private:
	bool	 _isDmg;
	F32		 _dmgTime;
	F32		 _dmgCounter;
	KE::Color _dmgColor;
	KC::AABB _boundingBox;

};//end Class

typedef shared_ptr<Settlement> p_Settlement;
