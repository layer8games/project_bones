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
	ARMOR_ITEM = 2,
	HASTE_ITEM = 3,
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
	inline void v_Awake(void) final
	{
		_timeAlive = 0.0f;
		UpdateInternals();
	}
	
	void v_Update(void)
	{
		ItemUpdate();
	}
	
	virtual void v_PickupAction(p_Actor actor)=0;

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
	inline ItemType GetType(void)
	{
		return _type;
	}

protected:
	void ItemUpdate(void);
//==========================================================================================================================
//
//Data
//
//==========================================================================================================================
	F32		   _maxTimeAlive;
	F32		   _timeAlive;
	ItemType   _type;
	KC::AABB   _boundingBox;

};//end Class
typedef shared_ptr<I_Item> p_Item;