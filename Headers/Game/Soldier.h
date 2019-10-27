#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/GameObject.h>
#include <Engine/Timer.h>
#include <Engine/ErrorManager.h>
#include <Engine/AABB.h>
#include <Engine/AudioManager.h>
#include <Engine/AudioSource.h>
#include <Engine/GameWindow.h>
#include <Engine/LevelManager.h>

namespace KE = KillerEngine;
namespace KM = KillerMath;
namespace KC = KillerCollisions;

#include <Game/I_Actor.h>
#include <Game/Projectile.h>
#include <Game/Icon.h>

#include <vector>

typedef std::vector<p_Icon> HealthList;
typedef std::vector<p_Icon> ArmorList;
typedef std::vector<p_Icon> KnifeList;

class Soldier : public I_Actor
{
public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
	Soldier(void);

	~Soldier(void);

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
	void v_Update(void) final;

	void v_Damage(S32 dmg = 1) final;

	void v_Heal(S32 heal=1) final;

	void v_Reset(void);

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
	void OnCollision(void);
	
	void Fire(p_Projectile projectile);

	inline void Move(F32 xVal)
	{
		//Consider stagger for player. May need another timer....
		AddScaledPosition(KM::Vector3(xVal, 0.0f), _speed * KM::Timer::Instance()->DeltaTime());
		//Need a better clip
		//_walkAudio.Play();
	}

	void SetSpeedBoost(F32 boost);
	
	inline void ResetDefaultSpeed(void)
	{
		_speed = _defaultSpeed;
		_haste = false;
	}

	void AddArmor(void);

	void AddKnife(F32 timer, U32 dmg);

	inline bool HasKnife(void)
	{
		return _knife;
	}

	inline void UseKnife(void)
	{
		_knife = false;
		_knifeBar[0]->SetActive(false);
	}

	inline U32 GetKnifeDmg(void)
	{
		return _knifeDmg;
	}

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
	inline S32 GetMaxArmor(void) const
	{
		return _maxArmor;
	}

	inline U32 GetMaxKnives(void) const
	{
		return _maxKnives;
	}

	inline ProjectileType GetActiveFireType(void) const
	{
		return _activeFireType;
	}

	inline void SetActiveFireType(ProjectileType type, F32 timer)
	{
		_activeFireType = type;
		_fireTypeTimeAlive = 0.0f;
		_fireTypeTimer = timer;
	}

	inline void AddHealthBar(HealthList bar)
	{
		_healthBar = bar;
	}

	inline void AddArmorBar(ArmorList bar)
	{
		_armorBar = bar;
	}

	inline void AddKnifeBar(KnifeList bar)
	{
		_knifeBar = bar;
	}

private:
	bool	 _canFire;
	bool	 _tookDamage;
	bool	 _haste;
	bool	 _knife;
	S32		 _maxArmor;
	S32		 _armor;
	F32		 _defaultSpeed;
	F32 	 _speed;
	F32 	 _fireRate;
	F32		 _lastFire;
	F32		 _lastDamaged;
	F32		 _immune;
	F32		 _fireTypeTimer;
	F32		 _fireTypeTimeAlive;
	F32		 _knifeTimer;
	F32		 _knifeTimeAlive;
	U32		 _knifeDmg;
	U32		 _maxKnives;
	ProjectileType _activeFireType;
	KE::AudioSource _damageAudio;
	KE::AudioSource _deathAudio;
	KE::AudioSource _defaultFireAudio;
	KE::AudioSource _walkAudio;
	HealthList		_healthBar;
	ArmorList		_armorBar;
	KnifeList		_knifeBar;

};//end Class

typedef shared_ptr<Soldier> p_Soldier;
