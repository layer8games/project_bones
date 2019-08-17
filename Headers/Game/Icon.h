#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/GameObject.h>
#include <Engine/TextureManager.h>

namespace KE = KillerEngine;

#include <Game/ID_Database.h>


class Icon : public KE::GameObject
{
public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
	Icon(void);

	~Icon(void);

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
	void v_Update(void)
	{  }


private:

};//end Class

typedef shared_ptr<Icon> p_Icon;