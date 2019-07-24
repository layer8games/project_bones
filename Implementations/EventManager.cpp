#include <Game/EventManager.h>

//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
EventManager::EventManager(void)
{  }

EventManager::~EventManager(void)
{  }

//==========================================================================================================================
//
//Singleton Functions
//
//==========================================================================================================================
p_EventManager EventManager::_instance = nullptr;

p_EventManager EventManager::Instance(void)
{
	if(_instance == nullptr)
	{
		_instance = make_shared<EventManager>();
	}
	return _instance;
}
