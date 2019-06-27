#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/TextureManager.h>

//===== Game Includes =====
#include <Game/Soldier.h>
#include <Game/Monster.h>
#include <Game/Settlement.h>
#include <Game/Projectile.h>


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
	p_Soldier MakeSoldier(void)
	{
		return p_Soldier(new Soldier());
	}

	p_Monster MakeMonster(void)
	{
		return p_Monster(new Monster());
	}

	p_Settlement MakeSettlement(void)
	{
		p_Settlement p = make_shared<Settlement>();
		
		p->SetScale(64.0f, 64.0f);
		p->SetTexture(KE::TextureManager::Instance()->GetTexture(SETTLEMENT));
		
		return p;
	}

	p_Projectile MakeProjectile(void)
	{
		return p_Projectile(new Projectile());
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
