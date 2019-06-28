#include <Game/Monster.h>
#include <iostream>

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
	_boundingBox(),
	_aiState(NO_STATE),
	_aiType(NO_TYPE),
	_target(nullptr)
{
	GameObject::MakeSprite();
	_boundingBox.SetCenter(_position);
	_boundingBox.SetHalfDimensions(_scale);
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
	if(!_canAttack)
	{
		_lastAttack += KM::Timer::Instance()->DeltaTime();

		if(_lastAttack >= _attackRate)
		{
			_canAttack = true;
			_lastAttack = 0.0f;
		}
	}
	
	_boundingBox.SetCenter(_position);
}

void Monster::Setup(MonsterAIType type, KM::Point pos)
{
	switch(type)
	{
		case AI_YELLOW_MONSTER :
			_hp = 1;
			_aiType = type;
			_aiState = CHOOSE;
			_position = pos;
			_speed = 150.0f;
			_damage = 1;
			_attackRate = 1.0f;
			_pointValue = 1;
			SetScale(32.0f, 32.0f);
			SetTexture(KE::TextureManager::Instance()->GetTexture(YELLOW_MONSTER));
			SetActive(true);
		break;
		case AI_RED_MONSTER :
			
		break;
		case AI_BLUE_MONSTER :

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
	if(_aiType == AI_YELLOW_MONSTER)
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
	}
	else if(_aiType == AI_RED_MONSTER)
	{

	}
	else if(_aiType == AI_BLUE_MONSTER)
	{

	}
	else
	{
		KE::ErrorManager::Instance()->SetError(KE::APPLICATION, "Monster::Choose No such AI present with id " + _aiType);
	}
	
	_aiState = SEEK;
}

void Monster::Seek(void)
{	
	if(_target != nullptr)
	{
		KM::Vector3 targetVec = _target->GetPosition() - _position;

		if(targetVec.SqrMagnitude() <= _attackRange * _attackRange)
		{
			_aiState = ATTACK;
		}
		else
		{
			targetVec.Normalize();
			_position += targetVec * _speed * KM::Timer::Instance()->DeltaTime();
		}
	}
}

void Monster::Attack(void)
{
	if(_canAttack)
	{
		_target->v_Damage(_damage);
		_canAttack = false;
	}

	if(!_target->Alive())
	{
		_target->SetActive(false);
		SetActive(false);
	}

}