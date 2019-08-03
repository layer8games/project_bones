/*
	This is not a good version of how to make an EventManager. I made the choice to just make it, even its crappy in order
	to be able to finish this project so that I could move on. This was done because I wanted to get onto the next project.
	Later on, a better version of this same system needs to be created. 
*/

#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>


class EventManager
{
public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
	~EventManager(void);

//==========================================================================================================================
//
//Singleton Functions
//
//==========================================================================================================================
	static shared_ptr<EventManager> Instance(void);

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
	inline bool HasEvent(void)
	{
		if (_event)
		{
			_event = false;
			return true;
		}
		return _event;
	}
	
	inline void AddEnemyKilled(U32 points)
	{
		++_enemiesKilled;
		_pointsEarned += points;
		_event = true;
	}

	U32 CheckEnemiesKilled(void);
	U32 CheckPointsEarned(void);

protected:
	EventManager(void);

private:
	static shared_ptr<EventManager> _instance;

	bool _event;
	U32 _enemiesKilled;
	U32 _pointsEarned;

};//end Class
typedef shared_ptr<EventManager> EventManagerPtr;