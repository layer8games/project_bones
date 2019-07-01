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
	_activeType(DO_NOTHING)
{
	SetActive(false);
	MakeSprite();
	SetPosition(0.0f, -1000.0f);
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

	AddScaledPosition(KM::Vector3(0.0f, 1.0f), _distTraveled);

	if(_distTraveled >= _range)
	{
		SetActive(false);
		SetPosition(0.0f, -1000.0f);
		_distTraveled = 0.0f;
		UpdateInternals();
	}
}

void Projectile::Fire(const KM::Point& pos)
{	
	SetPosition(pos);
	UpdateInternals();
	SetActive(true);
}

void Projectile::SetUp(ProjectileType type)
{
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
		break;
		default:
		
		break;
	};
}

void Projectile::HitEnemy(void)
{
	--_numEnemies;

	if(_numEnemies == 0)
	{
		SetPosition(0.0f, -1000.0f);
		SetActive(false);
		UpdateInternals();
	}
}