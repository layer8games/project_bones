#include <Game/Battleground.h>
#include <iostream>

//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
Battleground::Battleground(void)
	:
	_projectilePoolSize(25),
	_monsterPoolSize(30),
	_settlementListSize(6),
	_player(nullptr),
	_projectilePool(),
	_monsterPool(),
	_settlementList()
{ }

Battleground::~Battleground(void)
{
	//Unload Texture
	KE::TextureManager::Instance()->RemoveTexture(SOLDIER);
	KE::TextureManager::Instance()->RemoveTexture(YELLOW_MONSTER);
	KE::TextureManager::Instance()->RemoveTexture(SETTLEMENT);
	KE::TextureManager::Instance()->RemoveTexture(DEFAULT_BULLET);

	_projectilePool.clear();
	_monsterPool.clear();
	_settlementList.clear();
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
	SetTopBorder(Level::GetHeight() / 2);
	SetBottomBorder(-Level::GetHeight() / 2);

	//Load Textures
	KE::TextureManager::Instance()->LoadTexture(SOLDIER, "./Assets/Textures/soldier_v1.png");
	KE::TextureManager::Instance()->LoadTexture(YELLOW_MONSTER, "./Assets/Textures/monster_yellow_v1.png");
	KE::TextureManager::Instance()->LoadTexture(SETTLEMENT, "./Assets/Textures/house_v1.png");
	KE::TextureManager::Instance()->LoadTexture(DEFAULT_BULLET, "./Assets/Textures/bullet_v2.png");

	//Set up player
	_player = ObjectFactory::Instance()->MakeSoldier();
	_player->SetPosition(0.0f, -200.0f);
	_player->SetScale(32.0f, 32.0f);
	_player->SetTexture(KE::TextureManager::Instance()->GetTexture(SOLDIER));
	_player->v_Awake();
	AddObjectToLevel(_player);	

	//Create Projectile Pool
	for(U32 i = 0; i < _projectilePoolSize; ++i)
	{
		p_Projectile p = ObjectFactory::Instance()->MakeProjectile();
		p->SetPosition(0.0f, -1000.0f);
		p->SetUp(BULLET);
		_projectilePool.push_back(p);
		AddObjectToLevel(p);
	}

	KM::Point settlementPos{Level::GetLeftBorder() + 128.0f, Level::GetBottomBorder() + 64.0f};

	//Create Monster Pool
	for(U32 i = 0; i < _monsterPoolSize; ++i)
	{
		p_Monster m = ObjectFactory::Instance()->MakeMonster();
		m->SetActive(false);
		m->SetPosition(0.0f, -1000.0f);
		_monsterPool.push_back(m);
		AddObjectToLevel(m);
	}
	
	//Create Settlements
	for(U32 i = 0; i < _settlementListSize; ++i)
	{
		p_Settlement s = ObjectFactory::Instance()->MakeSettlement();
		s->SetPosition(settlementPos);
		s->v_Awake();
		_settlementList.push_back(s);
		AddObjectToLevel(s);
		settlementPos[x] += 150.0f;
	}

	//TestSpawn Logic
	_Spawn(15, AI_YELLOW_MONSTER);
}

void Battleground::v_Update(void)
{
	//Exit or Menu check
	if(KE::Controller::Instance()->GetKeyDown(KE::ESCAPE))
	{
		KE::Engine::Instance()->End();
		return;
	}

	if(!_player->Alive())
	{
		std::cout << "I AM DEAD!!!\n";
	}
	
	_ProcessCollisions();

	//Player input loop
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
		for(auto p : _projectilePool)
		{
			if(!p->GetActive())
			{
				_player->Fire(p);
			}
		}
	}

	//AI loop
	for(auto monster : _monsterPool)
	{
		if(monster->GetActive())
		{	
		//This may not work... the list to send to choose will change from type to type
			if(monster->GetAIState() == CHOOSE)
			{
				PotentialTargetList targets;

				for(auto settlement : _settlementList)
				{
					PotentialTarget target;
					target.target = settlement;
					target.weight = 0;
					targets.push_back(target);
				}

				monster->Choose(targets);
			}
			else if(monster->GetAIState() == SEEK)
			{
				monster->Seek();
			}
			else if(monster->GetAIState() == ATTACK)
			{
				monster->Attack();
			}
			else
			{
				KE::ErrorManager::Instance()->SetError(KE::APPLICATION, "Battleground::v_Update Monster attempted to update with invalid AI");
			}
		}
	}
}

void Battleground::_Spawn(U32 amount, MonsterAIType type)
{
	KM::Point pos(Level::GetLeftBorder() + 32.0f, Level::GetTopBorder() - 32.0f);
	//rand for pos

	for(U32 i = 0; i < amount; ++i)
	{
		for(auto monster : _monsterPool)
		{
			if(!monster->GetActive())
			{
				monster->Setup(type, pos);
				break;
			}
			//update rand
		}
		pos[x] += 64.0f;
	}
}

void Battleground::_ProcessCollisions(void)
{
	for(auto monster : _monsterPool)
	{
		if(monster->GetActive())
		{
			if(_player->OverlapCheck(monster))
			{
				std::cout << "Gonna attack the player\n";
				monster->Attack(_player);
			}
		}
	}
}