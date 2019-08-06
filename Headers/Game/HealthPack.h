#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/Timer.h>

namespace KM = KillerMath;

//===== Game Includes =====
#include <Game/I_Item.h>


class HealthPack : public I_Item
{
public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
	HealthPack(void);

	~HealthPack(void);

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
	inline void v_Awake(void) final
	{
		_timeAlive = 0.0f;
		UpdateInternals();
	}

	void v_Update(void) final;

	void v_PickupAction(p_Actor actor) final;

	void v_SetUp(ItemType type) final;

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================


private:
	S32 _hpToRestore;
	F32 _maxTimeAlive;
	F32 _timeAlive;

};//end Class
typedef shared_ptr<HealthPack> p_HealthPack;