#include <Game/Soldier.h>

//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
Soldier::Soldier(void)
:
_hp(3),
_speed(3.0f),
_attackRate(2.0f),
_boundingBox()
{
	GameObject::MakeSprite();
	_boundingBox.SetCenter(GameObject::_position);
	_boundingBox.SetHalfDimensions(GameObject::_scale);
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
	
}

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
void Soldier::Fire(void)
{

}