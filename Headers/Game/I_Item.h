#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/GameObject.h>

namespace TE = Tempest;

//===== Game Includes =====
#include <Game/Soldier.h>

enum ItemType
{
	HEALTH_ITEM = 1,
	ARMOR_ITEM = 2,
	HASTE_ITEM = 3,
	KNIFE_ITEM = 4,
	LAZER_ITEM = 5,
};

class I_Item : public TE::GameObject
{
public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
	I_Item(void);

	virtual ~I_Item(void);

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
	inline void v_Awake(void) final
	{
		UpdateInternals();
	}
	
	void v_Update(void)
	{
		ItemUpdate();
	}
	
	virtual void v_PickupAction(p_Soldier actor)=0;

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

};//end Class
typedef shared_ptr<I_Item> p_Item;