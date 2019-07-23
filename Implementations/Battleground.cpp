#include <Game/Battleground.h>
#include <iostream>

//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
Battleground::Battleground(void)
	:
	_roundNumber(0),
	_projectilePoolSize(25),
	_monsterPoolSize(30),
	_settlementListSize(6),
	_score(0),
	_spawnRate(2.0f),
	_lastSpawn(0.0f),
	_monsterWalkTimer(0.5f),
	_monsterWalkCountdown(0.0f),
	_canSpawn(true),
	_spawnAmount(2),
	_player(nullptr),
	_projectilePool(),
	_monsterPool(),
	_settlementList(),
	_spawnZones(),
	_monsterWalkAudioSource(),
	_font(),
	_roundText(),
	_roundNumberText(),
	_scoreText()
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

	//Audio setup
	_monsterWalkAudioSource.AddClip(KE::AudioManager::Instance()->GetClip(MONSTER_WALK_CLIP));

	//Setup text
	_font.Init("bank_gothic", "./Assets/Fonts/bank_gothic.ttf", 12);

	_roundText.SetFont(_font);
	_roundText.AddText("Round:");
	_roundText.SetPosition(KM::Point(static_cast<F32>(GetLeftBorder()) * 0.9f, static_cast<F32>(GetTopBorder()) * 0.9f));
	Level::AddTextToLevel(_roundText);

	_roundNumberText.SetFont(_font);
	_roundNumberText.AddText(std::to_string(_roundNumber));
	//The equation for getting the number into the right place is pretty arbitrary. It was found by guessing pretty much. 
	_roundNumberText.SetPosition(KM::Point(static_cast<F32>(GetLeftBorder()) * 0.9f + _roundText.GetWidth() * 3.25f, static_cast<F32>(GetTopBorder()) * 0.9f));
	Level::AddTextToLevel(_roundNumberText);

	_scoreText.SetFont(_font);
	_scoreText.AddText(std::to_string(_score));
	_scoreText.SetPosition(KM::Point(static_cast<F32>(GetLeftBorder()) * 0.9f + _roundText.GetWidth() * 3.25f, static_cast<F32>(GetTopBorder()) * 0.8f));
	Level::AddTextToLevel(_scoreText);
	
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

	//Set up Spawn Zones
	//Can dynamically add more. _Spawn will support that without any additional work.
	//30% from the left border, 10% from the top of the screen
	_spawnZones.push_back(KM::Point(static_cast<F32>(GetLeftBorder()) * 0.33f, GetTopBorder() * 0.9f));
	//30% from the right border, 10% from the top
	_spawnZones.push_back(KM::Point(static_cast<F32>(GetRightBorder()) * 0.33f, GetTopBorder() * 0.9f));
	//Right on the left border, 60% from the top of the screen
	_spawnZones.push_back(KM::Point(static_cast<F32>(GetLeftBorder()), GetTopBorder() * 0.4f));
	//Right on the right border, 60% from the top of the screen
	_spawnZones.push_back(KM::Point(static_cast<F32>(GetRightBorder()), GetTopBorder() * 0.4f));

	
}

void Battleground::v_Update(void)
{
	//Exit or Menu check
	if(KE::Controller::Instance()->GetKeyDown(KE::ESCAPE))
	{
		KE::Engine::Instance()->End();
		return;
	}

	KE::AudioManager::Instance()->PlaySource(BACKGROUND_MUSIC_SOURCE);

	if(_canSpawn)
	{
		_canSpawn = false;
		_lastSpawn = 0.0f;
		_Spawn(_spawnAmount, AI_YELLOW_MONSTER);
		++_spawnAmount;
	}
	else
	{
		_lastSpawn += KM::Timer::Instance()->DeltaTime();

		if(_lastSpawn >= _spawnRate)
		{
			_canSpawn = true;
		}
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

	//Used later, if it can be made to be interesting
	//bool playWalk = false;
	//AI loop
	for(auto monster : _monsterPool)
	{
		if(monster->GetActive())
		{	
		//This may not work... the list to send to choose will change from type to type
			if(monster->GetAIState() == CHOOSE)
			{
				PotentialTargetList targets;

				bool foundTarget = false;
				
				for(auto settlement : _settlementList)
				{
					if(settlement->GetActive())
					{
						PotentialTarget target;
						target.target = settlement;
						target.weight = 0;
						targets.push_back(target);
						foundTarget = true;
					}
				}
				
				if(!foundTarget)
				{
					PotentialTarget target;
					target.target = _player;
					targets.push_back(target);
				}

				monster->Choose(targets);
			}
			else if(monster->GetAIState() == SEEK)
			{
				monster->Seek();

				//playWalk = true;
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

/*
	This sounds dumb... needs some work and some thought

	if(_monsterWalkCountdown <= 0.0f && playWalk)
	{
		_monsterWalkAudioSource.Play();
		_monsterWalkCountdown = _monsterWalkTimer;
	}
	else
	{
		_monsterWalkCountdown -= KM::Timer::Instance()->DeltaTime();
	}
*/
}

void Battleground::_Spawn(U32 amount, MonsterAIType type)
{
	KM::Point spawnOffset{KM::Random::Instance()->RandomFloat(-10.0f, 10.0f), KM::Random::Instance()->RandomFloat(-10.0f, 10.0f)};
	
	for(U32 i = 0; i < amount; ++i)
	{		
		U32 spawnZoneToUse = KM::Random::Instance()->RandomInt(1, _spawnZones.size()) - 1;

		for(auto monster : _monsterPool)
		{
			if(!monster->GetActive())
			{
				monster->Setup(type, _spawnZones[spawnZoneToUse] + spawnOffset);
				KE::AudioManager::Instance()->PlaySource(MONSTER_SPAWN_SOURCE);
				break;
			}
			//update rand
			spawnOffset.Set(KM::Random::Instance()->RandomFloat(-10.0f, 10.0f), KM::Random::Instance()->RandomFloat(-10.0f, 10.0f));
		}
	}

	_UpdateRound();
}

void Battleground::_ProcessCollisions(void)
{
	//Monsters vs Player
	for(auto monster : _monsterPool)
	{
		if(monster->GetActive())
		{
			if(_player->OverlapCheck(monster))
			{
				monster->Attack(_player);
			}
		}
	}

	//Projectiles vs Monsters
	for(auto projectile : _projectilePool)
	{
		if(projectile->GetActive())
		{
			for(auto monster : _monsterPool)
			{
				if(projectile->OverlapCheck(monster))
				{
					monster->v_Damage(projectile->GetDamage());
					projectile->HitEnemy();
					break;
				}
			}
		}
	}
}

void Battleground::_UpdateRound(void)
{
	++_roundNumber;
	RemoveTextFromLevel(_roundNumberText);
	_roundNumberText.AddText(std::to_string(_roundNumber));
	AddTextToLevel(_roundNumberText);

	_score += 1000;
	RemoveTextFromLevel(_scoreText);
	_scoreText.AddText(std::to_string(_score));
	AddTextToLevel(_scoreText);
}