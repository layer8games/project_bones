#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/GameObject.h>
#include <Engine/AABB.h>
#include <Engine/Color.h>
#include <Engine/Timer.h>
#include <Engine/AudioManager.h>
#include <Engine/AudioSource.h>

namespace TE = Tempest;
namespace TC = TempestCollisions;
namespace TM = TempestMath;

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
	TE::AudioSource _damageAudio;
	TE::AudioSource _deathAudio;

};//end Class

typedef shared_ptr<Settlement> p_Settlement;
