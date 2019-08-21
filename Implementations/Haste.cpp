#include <Game/Haste.h>

//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
Haste::Haste(void)
	:
	_on(false),
	_timeActive(10.0f),
	_onTimer(0.0f),
	_speedBoost(2.5f),
	_target(nullptr)
{  }

Haste::~Haste(void)
{  }

void Haste::v_Update(void)
{
	if(!_on)
	{
		ItemUpdate();
		return;
	}

	_onTimer += KM::Timer::Instance()->DeltaTime();

	if(_onTimer >= _timeActive)
	{
		_target->ResetDefaultSpeed();
		_target = nullptr;
		_on = false;
		SetActive(false);
	}
}

void Haste::v_PickupAction(p_Actor actor)
{
	if(!_on)
	{
		_on = true;
		_target = actor;
		_target->SetSpeedBoost(_speedBoost);
		SetActiveRender(false);
	}
}