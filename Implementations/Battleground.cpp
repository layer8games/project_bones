#include <Game/Battleground.h>

//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
Battleground::Battleground(void)
	:
	_poolSize(25),
	_player(nullptr),
	_monster(nullptr),
	_settlement(nullptr),
	_pool()
{

}

Battleground::~Battleground(void)
{
	//Unload Texture
	KE::TextureManager::Instance()->RemoveTexture(SOLDIER);
	KE::TextureManager::Instance()->RemoveTexture(YELLOW_MONSTER);
	KE::TextureManager::Instance()->RemoveTexture(SETTLEMENT);

	_pool.clear();
}

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
void Battleground::v_Init(void)
{
	SetID(BATTLEGROUND);
	SetWidth(KE::GameWindow::Instance()->GetWidth());
	SetHeight(KE::GameWindow::Instance()->GetHeight());
	SetBackgroundColor(KE::Color(0.2f, 0.2f, 0.2f));
	SetLeftBorder(-GetWidth() / 2);
	SetRightBorder(Level::GetWidth()/ 2);

	//Load Textures
	KE::TextureManager::Instance()->LoadTexture(SOLDIER, "./Assets/Textures/soldier_v1.png");
	KE::TextureManager::Instance()->LoadTexture(YELLOW_MONSTER, "./Assets/Textures/monster_yellow_v1.png");
	KE::TextureManager::Instance()->LoadTexture(SETTLEMENT, "./Assets/Textures/house_v1.png");
	KE::TextureManager::Instance()->LoadTexture(DEFAULT_BULLET, "./Assets/Textures/bullet_v2.png");

	_player = ObjectFactory::Instance()->MakeSoldier();
	_player->SetPosition(0.0f, -200.0f);
	_player->SetScale(32.0f, 32.0f);
	_player->SetTexture(KE::TextureManager::Instance()->GetTexture(SOLDIER));
	AddObjectToLevel(_player);

	_monster = ObjectFactory::Instance()->MakeMonster();
	_monster->SetPosition(0.0f, 150.0f);
	_monster->SetScale(32.0f, 32.0f);
	_monster->SetTexture(KE::TextureManager::Instance()->GetTexture(YELLOW_MONSTER));
	AddObjectToLevel(_monster);

	_settlement = ObjectFactory::Instance()->MakeSettlement();
	_settlement->SetPosition(0.0f, -300.0f);
	_settlement->SetScale(64.0f, 64.0f);
	_settlement->SetTexture(KE::TextureManager::Instance()->GetTexture(SETTLEMENT));
	AddObjectToLevel(_settlement);

	for(U32 i = 0; i < _poolSize; ++i)
	{
		p_Projectile p = ObjectFactory::Instance()->MakeProjectile();
		p->SetPosition(0.0f, -1000.0f);
		p->SetUp(BULLET);
		_pool.push_back(p);
		AddObjectToLevel(p);
	}
}

void Battleground::v_Update(void)
{
	if (KE::Controller::Instance()->GetKeyDown(KE::ESCAPE))
	{
		KE::Engine::Instance()->End();
	}

	if(KE::Controller::Instance()->GetKeyHeld(KE::LEFT_ARROW))
	{
		if(_player->GetPosition()[x] > Level::GetLeftBorder())
		{
			_player->Move(-1.0f);
		}
	}
	else if(KE::Controller::Instance()->GetKeyHeld(KE::RIGHT_ARROW))
	{
		if(_player->GetPosition()[x] < GetRightBorder())
		{
			_player->Move(1.0f);
		}
	}
	
	if(KE::Controller::Instance()->GetKeyDown(KE::SPACE))
	{
		for(auto p : _pool)
		{
			if(!p->GetActive())
			{
				_player->Fire(p);
			}
		}
	}
}