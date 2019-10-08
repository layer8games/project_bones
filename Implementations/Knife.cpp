#include <Game/Knife.h>

//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
Knife::Knife(void)
	:
	_dmg(1),
	_effectActive(10.0f)
{  }

Knife::~Knife(void)
{  }


void Knife::v_PickupAction(p_Soldier actor)
{
	actor->AddKnife(_effectActive, _dmg);
	SetActive(false);
}