#include <Game/EventManager.h>

//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
EventManager::EventManager(void)
	:	
	_enemiesKilled(0),
	_pointsEarned(0)
{  }

EventManager::~EventManager(void)
{  }

//==========================================================================================================================
//
//Singleton Functions
//
//==========================================================================================================================
EventManagerPtr EventManager::_instance = nullptr;

EventManagerPtr EventManager::Instance(void)
{
	if(_instance == nullptr)
	{
		_instance = EventManagerPtr(new EventManager());
	}
	return _instance;
}

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
U32 EventManager::CheckEnemiesKilled(void)
{
	U32 killed = _enemiesKilled;
	_enemiesKilled = 0;

	return killed;
}

U32 EventManager::CheckPointsEarned(void)
{
	U32 points = _pointsEarned;
	_pointsEarned = 0;

	return points;
}