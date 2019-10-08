#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/TextureManager.h>

//===== Game Includes =====
#include <Game/Soldier.h>
#include <Game/Monster.h>
#include <Game/Settlement.h>
#include <Game/Projectile.h>
#include <Game/HealthPack.h>
#include <Game/Armor.h>
#include <Game/Haste.h>
#include <Game/Knife.h>


class ObjectFactory
{
public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
	ObjectFactory(void);

	~ObjectFactory(void);

//==========================================================================================================================
//
//Factories
//
//==========================================================================================================================
	inline p_Soldier MakeSoldier(void)
	{
		return p_Soldier(new Soldier());
	}

	inline p_Monster MakeMonster(void)
	{
		return p_Monster(new Monster());
	}

	inline p_Settlement MakeSettlement(void)
	{
		p_Settlement p = make_shared<Settlement>();
		
		p->SetScale(64.0f, 64.0f);
		p->SetTexture(KE::TextureManager::Instance()->GetTexture(SETTLEMENT));
		
		return p;
	}

	inline p_Projectile MakeProjectile(void)
	{
		return p_Projectile(new Projectile());
	}

	inline p_HealthPack MakeHealthPack(void)
	{
		p_HealthPack pack = make_shared<HealthPack>();
		pack->SetScale(16.0f, 16.0f);
		pack->SetTexture(KE::TextureManager::Instance()->GetTexture(HEALTH_PACK));

		return pack;
	}

	inline p_Armor MakeArmor(void)
	{
		p_Armor armor = make_shared<Armor>();
		armor->SetScale(16.0f, 16.0f);
		armor->SetTexture(KE::TextureManager::Instance()->GetTexture(ARMOR));

		return armor;
	}

	inline p_Haste MakeHaste(void)
	{
		p_Haste haste = make_shared<Haste>();
		haste->SetScale(16.0f, 16.0f);
		haste->SetTexture(KE::TextureManager::Instance()->GetTexture(HASTE));
		return haste;
	}

	inline p_Knife MakeKnife(void)
	{
		p_Knife knife = make_shared<Knife>();
		knife->SetScale(16.0f, 32.0f);
		knife->SetTexture(KE::TextureManager::Instance()->GetTexture(KNIFE));
		return knife;
	}

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
	static shared_ptr<ObjectFactory> Instance(void);

private:
	static shared_ptr<ObjectFactory> _instance;

};//end Class
typedef shared_ptr<ObjectFactory> p_ObjectFactory;
