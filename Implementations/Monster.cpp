#include <Game/Monster.h>

//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
Monster::Monster(void)
	:
	_hp(1),
	_dmg(1),
	_speed(1.0f),
	_attackRate(1.0f),
	_pointValue(0),
	_boundingBox()
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
}