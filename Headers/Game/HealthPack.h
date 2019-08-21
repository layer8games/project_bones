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
	void v_PickupAction(p_Actor actor) final;

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================


private:
	S32 _hpToRestore;	

};//end Class
typedef shared_ptr<HealthPack> p_HealthPack;