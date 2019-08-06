#include <Game/Soldier.h>
#include <iostream>

//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
Soldier::Soldier(void)
:
_canFire(true),
_tookDamage(false),
_speed(350.0f),
_fireRate(0.2f),
_lastFire(0.0f),
_lastDamaged(0.0f),
_immune(0.5f),
_activeFireType(BULLET),
_damageAudio(),
_deathAudio(),
_defaultFireAudio(),
_walkAudio()
{
	GameObject::MakeSprite();
	_maxHP = 3;
	_hp = _maxHP;
	_damageAudio.AddClip(KE::AudioManager::Instance()->GetClip(PLAYER_DAMAGE_CLIP));
	_deathAudio.AddClip(KE::AudioManager::Instance()->GetClip(PLAYER_DIE_CLIP));
	_defaultFireAudio.AddClip(KE::AudioManager::Instance()->GetClip(PLAYER_DEFAULT_FIRE_CLIP));
	_walkAudio.AddClip(KE::AudioManager::Instance()->GetClip(PLAYER_WALK_CLIP));
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
}

void Soldier::v_Damage(S32 dmg)
{
	if(!_tookDamage)
	{
		DefaultDamage();
		_tookDamage = true;
		_damageAudio.Play();
	}

	if(!_alive)
	{
		_deathAudio.Play();
	}
}

void Soldier::OnCollision(void)
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
		projectile->Fire(GetPosition());

		_defaultFireAudio.Play();

		_canFire = false;
	}
}
