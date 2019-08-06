#include <Game/HealthPack.h>

//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
HealthPack::HealthPack(void)
	:
	_hpToRestore(1),
	_maxTimeAlive(5.0f),
	_timeAlive(0.0f)
{  }

HealthPack::~HealthPack(void)
{  }

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
void HealthPack::v_Update(void)
{
	_timeAlive += KM::Timer::Instance()->DeltaTime();

	if(_timeAlive >= _maxTimeAlive)
	{
		SetActive(false);
	}
}

void HealthPack::v_PickupAction(I_Actor& actor)
{
	actor.Heal(_hpToRestore);
}

void HealthPack::v_SetUp(ItemType type)
{

}