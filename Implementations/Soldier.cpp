#include <Game/Soldier.h>

//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
Soldier::Soldier(void)
:
_canFire(true),
_speed(300.0f),
_fireRate(0.2f),
_lastFire(0.0f),
_boundingBox(),
_activeFireType(BULLET)
{
	GameObject::MakeSprite();
	_boundingBox.SetCenter(GameObject::_position);
	_boundingBox.SetHalfDimensions(GameObject::_scale);
	_hp = 3;
}

Soldier::~Soldier(void)
{  }

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
void Soldier::v_Update(void)
{
	if(!_canFire)
	{
		_lastFire += KM::Timer::Instance()->DeltaTime();

		if(_lastFire >= _fireRate)
		{
			_canFire = true;
			_lastFire = 0.0f;
		}
	}

	_boundingBox.SetCenter(GameObject::_position);
}

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
void Soldier::Fire(p_Projectile projectile)
{
	if(_canFire)
	{
		projectile->SetUp(_activeFireType);
		projectile->Fire(_position);
		_canFire = false;
	}
}
