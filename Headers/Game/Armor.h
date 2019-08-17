#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>

//===== Game Includes =====
#include <Game/I_Item.h>


class Armor : public I_Item
{
public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
	Armor(void);

	~Armor(void);

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
	inline void v_Awake(void) final
	{
		_timeAlive = 0.0f;
		UpdateInternals();
	}

	void v_PickupAction(p_Actor actor) final;

private:

};//end Class
typedef shared_ptr<Armor> p_Armor;
