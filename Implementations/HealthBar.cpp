#include <Game/HealthBar.h>

//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
HealthBar::HealthBar(void)
{
	MakeSprite();
	SetTexture(KE::TextureManager::Instance()->GetTexture(HEALTH_BAR));
}

HealthBar::~HealthBar(void)
{  }