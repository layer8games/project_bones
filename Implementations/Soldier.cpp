#include <Game/Soldier.h>

//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
Soldier::Soldier(void)
:
_canFire(true),
_tookDamage(false),
_speed(300.0f),
_fireRate(0.2f),
_lastFire(0.0f),
_lastDamaged(0.0f),
_immune(0.5f),
_activeFireType(BULLET)
{
	GameObject::MakeSprite();
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
	DefaultUpdate();

	if(_tookDamage)
	{
		_lastDamaged += KM::Timer::Instance()->DeltaTime();

		if(_lastDamaged >= _immune)
		{
			_tookDamage = false;
			_lastDamaged = 0.0f;
		}
	}

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

void Soldier::v_OnCollision(void)
{

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
