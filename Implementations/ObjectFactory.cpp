#include <Game/ObjectFactory.h>

//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
ObjectFactory::ObjectFactory(void)
{  }

ObjectFactory::~ObjectFactory(void)
{  }

//==========================================================================================================================
//
//Singleton Pattern
//
//==========================================================================================================================
p_ObjectFactory ObjectFactory::_instance = nullptr;

p_ObjectFactory ObjectFactory::Instance(void)
{
	if (_instance == nullptr)
	{
		_instance = p_ObjectFactory(new ObjectFactory());
	}
	return _instance;
}