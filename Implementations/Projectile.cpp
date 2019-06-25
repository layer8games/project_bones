#include <Game/Projectile.h>

//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
Projectile::Projectile(void)
	:
	_damage(1),
	_range(1000.0f),
	_forwardVelocity(600.0f),
	_boundingBox()
{
	MakeSprite();
	_boundingBox.SetCenter(_position);
	_boundingBox.SetDimensions(_scale);
}

Projectile::~Projectile(void)
{  }

//==========================================================================================================================
//
//Virtual functions
//
//==========================================================================================================================
void Projectile::v_Update(void)
{
	_position[y] += _forwardVelocity * KM::Timer::Instance()->DeltaTime();
	
	_boundingBox.SetCenter(_position);
}