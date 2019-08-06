#include <Game/HealthPack.h>

//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
HealthPack::HealthPack(void)
	:
	_hpToRestore(1),
	_maxTimeAlive(10.0f),
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

void HealthPack::v_PickupAction(p_Actor actor)
{
	actor->Heal(_hpToRestore);
	SetActive(false);
}

void HealthPack::v_SetUp(ItemType type)
{

}