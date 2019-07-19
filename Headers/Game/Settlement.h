#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/GameObject.h>
#include <Engine/AABB.h>
#include <Engine/Color.h>
#include <Engine/Timer.h>
#include <Engine/AudioManager.h>
#include <Engine/AudioSource.h>

namespace KE = KillerEngine;
namespace KC = KillerCollisions;
namespace KM = KillerMath;

//===== Game Includes =====
#include <Game/ID_Database.h>
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

	void v_Damage(S32 dmg = 1) final;

private:
	KE::AudioSource _damageAudio;
	KE::AudioSource _deathAudio;

};//end Class

typedef shared_ptr<Settlement> p_Settlement;
