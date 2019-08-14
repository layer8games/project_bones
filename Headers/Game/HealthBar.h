#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/GameObject.h>
#include <Engine/TextureManager.h>

namespace KE = KillerEngine;

#include <Game/ID_Database.h>


class HealthBar : public KE::GameObject
{
public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
	HealthBar(void);

	~HealthBar(void);

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
	void v_Update(void)
	{  }


private:

};//end Class

typedef shared_ptr<HealthBar> p_HealthBar;