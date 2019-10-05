#include <Game/Knife.h>

//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
Knife::Knife(void)
	:
	_timeAlive(10.0f),
	_dmg(1)
{  }

Knife::~Knife(void)
{  }

void Knife::v_Update(void)
{

}

void Knife::v_PickupAction(p_Soldier actor)
{
	actor->AddKnife(_timeAlive, _dmg);
	SetActive(false);
}