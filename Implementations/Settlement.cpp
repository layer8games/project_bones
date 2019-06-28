#include <Game/Settlement.h>

//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
Settlement::Settlement(void)
	:
	_isDmg(false),
	_dmgTime(0.1f),
	_dmgCounter(0.0f),
	_dmgColor(0.5, 0.1f, 0.1f),
	_boundingBox()
{
	GameObject::MakeSprite();
	_boundingBox.SetCenter(_position);
	_boundingBox.SetHalfDimensions(_scale);
	_position[z] = -1.0f;

	_hp = 10;
}

Settlement::~Settlement(void)
{  }

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
void Settlement::v_Update(void)
{
	if(_isDmg)
	{
		_dmgCounter += KM::Timer::Instance()->DeltaTime();

		if(_dmgCounter >= _dmgTime)
		{
			_isDmg = false;
			_dmgCounter = 0.0f;
			SetColor(KE::Color(1.0f, 1.0f, 1.0));
		}
	}
}

void Settlement::v_Damage(S32 dmg)
{
	DefaultDamage(dmg);

	if(!_isDmg)
	{
		_isDmg = true;
		SetColor(_dmgColor);
	}
}