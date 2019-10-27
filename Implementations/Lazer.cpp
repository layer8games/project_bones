#include <Game/Lazer.h>

//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
Lazer::Lazer(void)
{  }

Lazer::~Lazer(void)
{  }

void Lazer::v_PickupAction(p_Soldier actor)
{
	actor->SetActiveFireType(LAZER, 15.0f);
	SetActive(false);
}