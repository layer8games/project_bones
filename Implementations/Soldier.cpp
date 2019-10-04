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
_haste(false),
_maxArmor(3),
_armor(0),
_defaultSpeed(450.0f),
_speed(_defaultSpeed),
_fireRate(0.2f),
_lastFire(0.0f),
_lastDamaged(0.0f),
_immune(0.5f),
_activeFireType(LAZER),
_damageAudio(),
_deathAudio(),
_defaultFireAudio(),
_walkAudio(),
_healthBar()
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
		bool armor = false;
		_tookDamage = true;
		_damageAudio.Play();

		if(_armor > 0)
		{
			armor = true;
			--_armor;

			for(S32 i = _armorBar.size() - 1; i >= 0; --i)
			{
				if(_armorBar[i]->GetActive())
				{

					_armorBar[i]->SetActive(false);
					break;
				}
			}
		}
		
		
		if(!armor)
		{
			DefaultDamage();

			//Back to front, turn off a bar
			for(S32 i = _healthBar.size() - 1; i >= 0; --i)
			{
				if(_healthBar[i]->GetActive())
				{
					_healthBar[i]->SetActive(false);
					break;
				}
			}
		}
	}

	if(!_alive)
	{
		_deathAudio.Play();
	}
}

void Soldier::v_Heal(S32 heal)
{
	DefaultHeal(heal);

	//front to back, turn on a bar
	for(U32 i = 0; i < _healthBar.size(); ++i)
	{
		if(!_healthBar[i]->GetActive())
		{
			_healthBar[i]->SetActive(true);
			break;
		}
	}
}

void Soldier::v_AddArmor(void)
{
	if(_armor < _maxArmor)
	{
		++_armor;

		for(U32 i = 0; i < _armorBar.size(); ++i)
		{
			if(!_armorBar[i]->GetActive())
			{
				_armorBar[i]->SetActive(true);
				break;
			}
		}
	}
}

void Soldier::v_Reset(void)
{
	DefaultReset();
	//Make sure all hp bars on on
	for(U32 i = 0; i < _healthBar.size(); ++i)
	{
		_healthBar[i]->SetActive(true);
	}
}

void Soldier::v_SetSpeedBoost(F32 boost)
{
	if(!_haste)
	{
		_speed *= boost;
		_haste = true;
	}
}

void Soldier::OnCollision(void)
{

}

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