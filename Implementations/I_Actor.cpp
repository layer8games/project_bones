#include <Game/I_Actor.h>

//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
I_Actor::I_Actor(void)
	:
	_alive(true),
	_hp(1),
	_isDmg(false),
	_dmgTime(0.1f),
	_dmgCounter(0.0f),
	_dmgColor(0.5, 0.1f, 0.1f),
	_boundingBox()
{  }

I_Actor::~I_Actor(void)
{  }

void I_Actor::DefaultDamage(S32 dmg)
{
	_hp -= dmg;

	if(_hp <= 0)
	{
		_alive = false;
	}

	if(!_isDmg)
	{
		_isDmg = true;
		//Later this will set the damaged animation to play
		SetColor(_dmgColor);
	}
}

void I_Actor::DefaultUpdate(void)
{
	if(!_alive)
	{
		SetActive(false);
	}
	
	if(_isDmg)
	{
		_dmgCounter += KM::Timer::Instance()->DeltaTime();

		if(_dmgCounter >= _dmgTime)
		{
			_isDmg = false;
			_dmgCounter = 0.0f;
			//Later this will maybe set other animations to run
			SetColor(KE::Color(1.0f, 1.0f, 1.0));
		}
	}
}