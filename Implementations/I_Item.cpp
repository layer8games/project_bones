#include <Game/I_Item.h>

//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
I_Item::I_Item(void)
	:
	_maxTimeAlive(10.0f),
	_timeAlive(0.0f),
	_type()
{
	GameObject::MakeSprite();
}

I_Item::~I_Item(void)
{  }


void I_Item::ItemUpdate(void)
{
	_timeAlive += KM::Timer::Instance()->DeltaTime();

	if(_timeAlive >= _maxTimeAlive)
	{
		SetActive(false);
	}
}