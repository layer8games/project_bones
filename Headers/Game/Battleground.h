#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/Level.h>
#include <Engine/GameWindow.h>
#include <Engine/Controller.h>
#include <Engine/Engine.h>
#include <Engine/TextureManager.h>

namespace KE = KillerEngine;

#include <Game/ID_Database.h>
#include <Game/Soldier.h>
#include <Game/Monster.h>
#include <Game/Settlement.h>
#include <Game/ObjectFactory.h>

class Battleground : public KE::Level
{
public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
	Battleground(void);

	~Battleground(void);

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
	void v_Init(void) final;

	void v_Update(void) final;

private:
	p_Soldier _player;
	p_Monster _monster;
	p_Settlement _settlement;

};//end Class

typedef shared_ptr<Battleground> p_Battleground;