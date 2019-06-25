#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/Level.h>

namespace KE = KillerEngine;

#include <Game/Soldier.h>
#include <Game/Monster.h>
#include <Game/Settlement.h>

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

};//end Class

typedef shared_ptr<Battleground> p_Battleground;