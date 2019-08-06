#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/GameObject.h>
#include <Engine/AABB.h>

namespace KE = KillerEngine;
namespace KC = KillerCollisions;

//===== Game Includes =====
#include <Game/I_Actor.h>

enum ItemType
{
	HEALTH_ITEM = 1,

};

class I_Item : public KE::GameObject
{
public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
	I_Item(void);

	~I_Item(void);

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
	virtual void v_PickupAction(p_Actor actor)=0;

	virtual void v_SetUp(ItemType type)=0;

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
	inline ItemType GetType(void)
	{
		return _type;
	}

	void CollisionCheck(const KC::AABB& other);

protected:
	ItemType   _type;
	KC::AABB   _boundingBox;

};//end Class
typedef shared_ptr<I_Item> p_Item;