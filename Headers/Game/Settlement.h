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

private:


};//end Class

typedef shared_ptr<Settlement> p_Settlement;
