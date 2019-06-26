#include <Game/Projectile.h>

//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
Projectile::Projectile(void)
	:
	_damage(1),
	_numEnemies(1),
	_range(1000.0f),
	_distTraveled(0.0f),
	_forwardVelocity(600.0f),
	_boundingBox(),
	_activeType(DO_NOTHING)
{
	SetActive(false);
	MakeSprite();
	_position.Set(0.0f, -1000.0f);
	_boundingBox.SetCenter(_position);
	_boundingBox.SetDimensions(_scale);
}

Projectile::~Projectile(void)
{  }

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
void Projectile::v_Update(void)
{
	_distTraveled += _forwardVelocity * KM::Timer::Instance()->DeltaTime();

	_position[y] += _distTraveled;
	
	_boundingBox.SetCenter(_position);

	if(_distTraveled >= _range)
	{
		SetActive(false);
		_position.Set(0.0f, -1000.0f);
		_distTraveled = 0.0f;
	}
}

void Projectile::Fire(const KM::Point& pos)
{
	_position = pos;
	SetActive(true);
}

void Projectile::SetUp(ProjectileType type)
{
	if(_activeType == type)
	{
		return;
	}

	switch(type)
	{
		case BULLET:
			_damage = 1;
			_numEnemies = 1;
			_range = 250.0f;
			_distTraveled = 0.0f;
			_forwardVelocity = 60.0f;
			SetScale(8.0f, 8.0f);
			SetTexture(KE::TextureManager::Instance()->GetTexture(DEFAULT_BULLET));
			_boundingBox.SetDimensions(_scale);
		break;
		default:
		
		break;
	};
}