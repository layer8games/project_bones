#include <Game/Settlement.h>

//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
Settlement::Settlement(void)
	:
	_damageAudio(),
	_deathAudio()
{
	GameObject::MakeSprite();
	_maxHP = 10;
	_hp = _maxHP;
	_damageAudio.AddClip(KE::AudioManager::Instance()->GetClip(SETTLEMENT_DAMAGE_CLIP));
	_deathAudio.AddClip(KE::AudioManager::Instance()->GetClip(SETTLEMENT_DIE_CLIP));
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
	DefaultUpdate();
}

void Settlement::v_Damage(S32 dmg)
{
	DefaultDamage(dmg);
	_damageAudio.Play();

	if(!_alive)
	{
		_deathAudio.Play();
	}
}