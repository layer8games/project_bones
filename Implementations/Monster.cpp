#include <Game/Monster.h>


//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
Monster::Monster(void)
	:
	_damage(1),
	_speed(1.0f),
	_canAttack(true),
	_attackRate(1.0f),
	_lastAttack(0.0f),
	_pointValue(0),
	_attackRange(5.0f),
	_shuffleDir(0.0f),
	_aiState(NO_STATE),
	_aiType(NO_TYPE),
	_target(nullptr),
	_deathAudioSource()
{
	GameObject::MakeSprite();
	_deathAudioSource.AddClip(KE::AudioManager::Instance()->GetClip(MONSTER_DIE_CLIP));
}

Monster::~Monster(void)
{

}

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
void Monster::v_Update(void)
{
	DefaultUpdate();

	if(!_canAttack)
	{
		_lastAttack += KM::Timer::Instance()->DeltaTime();

		if(_lastAttack >= _attackRate)
		{
			_canAttack = true;
			_lastAttack = 0.0f;
		}
	}
}

void Monster::v_Damage(S32 dmg)
{
	DefaultDamage();
	KE::AudioManager::Instance()->PlaySource(MONSTER_DAMAGE_SOURCE);

	if(!_alive)
	{
		EventManager::Instance()->AddEnemyKilled(_pointValue);
		_deathAudioSource.Play();
	}
}

void Monster::Setup(MonsterAIType type, KM::Point pos)
{
	switch(type)
	{
		case AI_YELLOW_MONSTER :
			_alive = true;
			_maxHP = 1;
			_hp = _maxHP;
			_aiType = type;
			_aiState = CHOOSE;
			SetColor(1.0f);
			SetPosition(pos);
			_speed = 70.0f;
			_damage = 1;
			_attackRate = 1.0f;
			_pointValue = 100;
			SetScale(32.0f, 32.0f);
			SetTexture(KE::TextureManager::Instance()->GetTexture(YELLOW_MONSTER));
			SetActive(true);
		break;
		case AI_RED_MONSTER :
			_alive = true;
			_maxHP = 1;
			_hp = _maxHP;
			_aiType = type;
			_aiState = CHOOSE;
			SetColor(1.0f);
			SetPosition(pos);
			_speed = 140.0f;
			_damage = 1;
			_attackRate = 5.0f;
			_pointValue = 200;
			SetScale(32.0f, 32.0f);
			SetTexture(KE::TextureManager::Instance()->GetTexture(RED_MONSTER));
			SetActive(true);
		break;
		case AI_BLUE_MONSTER :
			_alive = true;
			_maxHP = 5;
			_hp = _maxHP;
			_aiType = type;
			_aiState = CHOOSE;
			SetColor(1.0f);
			SetPosition(pos);
			_speed = 35.0f;
			_damage = 2;
			_attackRate = 1.0f;
			_pointValue = 300;
			SetScale(36.0f, 46.0f);
			SetTexture(KE::TextureManager::Instance()->GetTexture(BLUE_MONSTER));
			SetActive(true);
		break;
		default : 
			KE::ErrorManager::Instance()->SetError(KE::APPLICATION, "Monster:Setup Attempted to create a Monster with an invalid type " + type);
		break;
	}
}

//==========================================================================================================================
//
//AI Functions
//
//==========================================================================================================================
void Monster::Choose(PotentialTargetList targetList)
{
	S32 maxChance = 0;
	U32 currentIndex = 0;
	U32 useIndex = currentIndex;
	for(auto potential : targetList)
	{
		S32 chance = KM::Random::Instance()->RandomInt(0, 100) + potential.weight;

		if(chance > maxChance)
		{
			maxChance = chance;
			useIndex = currentIndex;
		}
		++currentIndex;
	}

	_target = targetList[useIndex].target;
	
	_aiState = SEEK;
}

void Monster::Seek(void)
{	
	if(_target != nullptr)
	{
		KM::Vector3 targetVec = _target->GetPosition() - GetPosition();

		if(targetVec.SqrMagnitude() <= _attackRange * _attackRange)
		{
			_aiState = ATTACK;
		}
		else
		{
			targetVec.Normalize();
			AddScaledPosition(targetVec, _speed * KM::Timer::Instance()->DeltaTime());	
		}

		if(!_target->GetActive())
		{
			_aiState = CHOOSE;
		}
	}
}

void Monster::Attack(void)
{
	KM::Vector3 targetVec = _target->GetPosition() - GetPosition();

	if(targetVec.SqrMagnitude() >= _attackRange * _attackRange && _target->GetActive())
	{
		_aiState = SEEK;
		return;
	}
	
	if(_canAttack)
	{		
		_target->v_Damage(_damage);
		_canAttack = false;
		
		U32 shuffleChance = KM::Random::Instance()->RandomInt(0, 100);

		if(shuffleChance <= 50)
		{
			_shuffleDir = -1.0f;
		}
		else
		{
			_shuffleDir = 1.0f;
		}
	}
	else
	{
		AddScaledPosition(KM::Vector3(_shuffleDir, 0.0f), (_speed * 0.12f) * KM::Timer::Instance()->DeltaTime());
	}

	if(!_target->Alive())
	{
		_target->SetActive(false);
		SetActive(false);
	}

}

void Monster::Attack(const p_Actor target)
{
	if(_canAttack)
	{
		target->v_Damage(_damage);
		_canAttack = false;
	}
}
