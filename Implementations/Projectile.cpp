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
	_distTraveled += _forwardVelocity * TM::Timer::Instance()->DeltaTime();

	AddScaledPosition(TM::Vector3(0.0f, 1.0f), _distTraveled);

	if(_distTraveled >= _range)
	{
		
		SetPosition(0.0f, -1000.0f);
		UpdateInternals();
		SetActive(false);
		_distTraveled = 0.0f;
	}
}

void Projectile::Fire(const TM::Point& pos)
{	
	SetPosition(pos);
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
			SetTexture(TE::TextureManager::Instance()->GetTexture(DEFAULT_BULLET));
		break; 
		case LAZER:
			_damage = 1;
			_numEnemies = 100;
			_range = 250.0f;
			_distTraveled = 0.0f;
			_forwardVelocity = 90.0f;
			SetScale(8.0f, 8.0f);
			SetTexture(TE::TextureManager::Instance()->GetTexture(LAZER_BULLET));
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