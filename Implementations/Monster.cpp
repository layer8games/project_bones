#include <Game/Monster.h>

//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
Monster::Monster(void)
	:
	_hp(1),
	_damage(1),
	_speed(1.0f),
	_attackRate(1.0f),
	_pointValue(0),
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
	_boundingBox.SetCenter(_position);

	//Move

	
}

void Monster::Setup(MonsterAIType type, KM::Point pos)
{
	switch(type)
	{
		case AI_YELLOW_MONSTER :
			_aiType = type;
			_aiState = CHOOSE;
			_position = pos;
			_hp = 1;
			_speed = 100.0f;
			_damage = 1;
			_attackRate = 0.1f;
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
	//if we found our target
	_aiState = ATTACK;
}

void Monster::Attack(void)
{
	//Attack timer logic

	//if target is no longer in range
	//_aiState = SEEK;
	
	//If our target is dead
	//_aiState = CHOOSE;
}