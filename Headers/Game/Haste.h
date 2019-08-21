#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/Timer.h>

namespace KM = KillerMath;

//===== Game Includes =====
#include <Game/I_Item.h>
#include <Game/Soldier.h>


class Haste : public I_Item
{
public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
	Haste(void);

	~Haste(void);

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
	void v_Update(void) final;
	
	void v_PickupAction(p_Actor actor) final;

private:
	bool _on;
	F32 _timeActive;
	F32 _onTimer;
	F32 _speedBoost;
	p_Actor _target;

};//end Class
typedef shared_ptr<Haste> p_Haste;