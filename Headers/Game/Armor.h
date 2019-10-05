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
	void v_PickupAction(p_Soldier actor) final;

private:

};//end Class
typedef shared_ptr<Armor> p_Armor;
