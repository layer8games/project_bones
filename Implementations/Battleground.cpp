#include <Game/Battleground.h>
#include <iostream>

//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
Battleground::Battleground(void)
	:
	_roundNumber(1),
	_killedThisRound(0),
	_roundLength(10),
	_spawnsThisRound(0),
	_maxSpawn(3),
	_roundLengthIncrease(5),
	_projectilePoolSize(25),
	_monsterPoolSize(30),
	_settlementListSize(6),
	_healthPackPoolSize(5),
	_armorPoolSize(5),
	_hastePoolSize(5),
	_score(0),
	_redSpawnRate(97),
	_spawnRate(4.0f),
	_lastSpawn(0.0f),
	_monsterWalkTimer(0.5f),
	_monsterWalkCountdown(0.0f),
	_settlementXOffset(150.0f),
	_canSpawn(true),
	_spawnBlue(false),
	_gameover(false),
	_player(nullptr),
	_projectilePool(),
	_monsterPool(),
	_healthPackPool(),
	_armorPool(),
	_hastePool(),
	_settlementList(),
	_spawnZones(),
	_monsterWalkAudioSource(),
	_font(),
	_roundTitleText(),
	_scoreTitleText(),
	_roundNumberText(),
	_scoreText(),
	_gameOverTitle(),
	_retryText(),
	_playerDefaultPos(0.0f, -200.0f)
{ }

Battleground::~Battleground(void)
{
	//Unload Texture
	KE::TextureManager::Instance()->RemoveTexture(SOLDIER);
	KE::TextureManager::Instance()->RemoveTexture(YELLOW_MONSTER);
	KE::TextureManager::Instance()->RemoveTexture(RED_MONSTER);
	KE::TextureManager::Instance()->RemoveTexture(BLUE_MONSTER);
	KE::TextureManager::Instance()->RemoveTexture(SETTLEMENT);
	KE::TextureManager::Instance()->RemoveTexture(DEFAULT_BULLET);
	KE::TextureManager::Instance()->RemoveTexture(HEALTH_PACK);
	KE::TextureManager::Instance()->RemoveTexture(HEALTH_BAR);
	KE::TextureManager::Instance()->RemoveTexture(ARMOR);
	KE::TextureManager::Instance()->RemoveTexture(HASTE);

	_projectilePool.clear();
	_monsterPool.clear();
	_settlementList.clear();
	_healthPackPool.clear();
	_armorPool.clear();
	_hastePool.clear();
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

	_defaultSettlementPos.Set(Level::GetLeftBorder() + 128.0f, Level::GetBottomBorder() + 64.0f);
	
	//Load Textures
	KE::TextureManager::Instance()->LoadTexture(SOLDIER, "./Assets/Textures/soldier_v1.png");
	KE::TextureManager::Instance()->LoadTexture(YELLOW_MONSTER, "./Assets/Textures/monster_yellow_v1.png");
	KE::TextureManager::Instance()->LoadTexture(RED_MONSTER, "./Assets/Textures/monster_red_v2.png");
	KE::TextureManager::Instance()->LoadTexture(BLUE_MONSTER, "./Assets/Textures/monster_blue_v1.png");
	KE::TextureManager::Instance()->LoadTexture(SETTLEMENT, "./Assets/Textures/house_v1.png");
	KE::TextureManager::Instance()->LoadTexture(DEFAULT_BULLET, "./Assets/Textures/bullet_v2.png");
	KE::TextureManager::Instance()->LoadTexture(LAZER_BULLET, "./Assets/Textures/lazer_projectile_v1.png");
	KE::TextureManager::Instance()->LoadTexture(LAZER_PICKUP, "./Assets/Textures/lazer_pickup_v1.png");
	KE::TextureManager::Instance()->LoadTexture(HEALTH_PACK, "./Assets/Textures/health_v2.png");
	KE::TextureManager::Instance()->LoadTexture(HEALTH_BAR, "./Assets/Textures/health_bar_v1.png");
	KE::TextureManager::Instance()->LoadTexture(ARMOR, "./Assets/Textures/armor_v1.png");
	KE::TextureManager::Instance()->LoadTexture(HASTE, "./Assets/Textures/haste_v1.png");

	//Audio setup
	_monsterWalkAudioSource.AddClip(KE::AudioManager::Instance()->GetClip(MONSTER_WALK_CLIP));

	//Setup text
	_font.Init("bank_gothic", "./Assets/Fonts/bank_gothic.ttf", 12);

	_gameOverTitle.SetFont(_font);
	_gameOverTitle.AddText("Game Over!");
	_gameOverTitle.SetPosition(0.0f, 0.0f);
	_gameOverTitle.SetActive(false);
	AddTextToLevel(_gameOverTitle);

	_retryText.SetFont(_font);
	_retryText.AddText("Try again? Y/N");
	_retryText.SetPosition(0.0f, -50.0f);
	_retryText.SetActive(false);
	AddTextToLevel(_retryText);

	_roundTitleText.SetFont(_font);
	_roundTitleText.AddText("Round:");
	_roundTitleText.SetPosition(KM::Point(static_cast<F32>(GetLeftBorder()) * 0.9f, static_cast<F32>(GetTopBorder()) * 0.9f));
	Level::AddTextToLevel(_roundTitleText);

	_scoreTitleText.SetFont(_font);
	_scoreTitleText.AddText("Score:");
	_scoreTitleText.SetPosition(KM::Point(static_cast<F32>(GetLeftBorder()) * 0.9f, static_cast<F32>(GetTopBorder()) * 0.85f));
	Level::AddTextToLevel(_scoreTitleText);

	_roundNumberText.SetFont(_font);
	_roundNumberText.AddText(std::to_string(_roundNumber));
	//The equation for getting the number into the right place is pretty arbitrary. It was found by guessing pretty much. 
	_roundNumberText.SetPosition(KM::Point(static_cast<F32>(GetLeftBorder()) * 0.9f + _roundTitleText.GetWidth() * 3.25f, static_cast<F32>(GetTopBorder()) * 0.9f));
	Level::AddTextToLevel(_roundNumberText);

	_scoreText.SetFont(_font);
	_scoreText.AddText(std::to_string(_score));
	_scoreText.SetPosition(KM::Point(static_cast<F32>(GetLeftBorder()) * 0.9f + _roundTitleText.GetWidth() * 3.25f, static_cast<F32>(GetTopBorder()) * 0.85f));
	Level::AddTextToLevel(_scoreText);
		
	//Set up player
	_player = ObjectFactory::Instance()->MakeSoldier();
	_player->SetPosition(_playerDefaultPos);
	_player->SetScale(32.0f, 32.0f);
	_player->SetTexture(KE::TextureManager::Instance()->GetTexture(SOLDIER));
	_player->v_Awake();
	AddObjectToLevel(_player);

	//Setup Player HealthBar
	KM::Point barPos{ static_cast<F32>(KE::GameWindow::Instance()->GetWidth()) * 0.35f,
					  static_cast<F32>(KE::GameWindow::Instance()->GetHeight()) * 0.4f };

	F32 barWidth = 16.0f;
	F32 barOffset = 12.0f;
	S32 maxHP = _player->GetHP();
	HealthList healthBar{};

	for(S32 i = 0; i < maxHP; ++i)
	{
		p_Icon bar = make_shared<Icon>();
		bar->SetScale(barWidth, barWidth);
		bar->SetTexture(KE::TextureManager::Instance()->GetTexture(HEALTH_BAR));
		bar->SetPosition(barPos);
		barPos[x] += barWidth + barOffset;
		AddObjectToLevel(bar);
		healthBar.push_back(bar);
	}
	_player->AddHealthBar(healthBar);

	//Setup Player ArmorBar
	barPos.Set(static_cast<F32>(KE::GameWindow::Instance()->GetWidth()) * 0.35f,
			   static_cast<F32>(KE::GameWindow::Instance()->GetHeight()) * 0.35f);

	barWidth = 16.0f;
	barOffset = 32.0f;
	maxHP = _player->GetMaxArmor();
	ArmorList armorBar{};

	for(S32 i = 0; i < maxHP; ++i)
	{
		p_Icon bar = make_shared<Icon>();
		bar->SetScale(barWidth, barWidth);
		bar->SetTexture(KE::TextureManager::Instance()->GetTexture(ARMOR));
		bar->SetPosition(barPos);
		barPos[x] += barWidth + barOffset;
		bar->SetActive(false);
		AddObjectToLevel(bar);
		armorBar.push_back(bar);
	}
	_player->AddArmorBar(armorBar);

	//Create Projectile Pool
	for(U32 i = 0; i < _projectilePoolSize; ++i)
	{
		p_Projectile p = ObjectFactory::Instance()->MakeProjectile();
		p->SetPosition(1000.0f, 1000.0f);
		p->UpdateInternals();
		p->SetActive(false);
		_projectilePool.push_back(p);
		AddObjectToLevel(p);
	}

	KM::Point settlementPos = _defaultSettlementPos;

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
		settlementPos[x] += _settlementXOffset;
	}

	// Set up Spawn Zones
	// Can dynamically add more. _Spawn will support that without any additional work.
	// 30% from the left border, 10% from the top of the screen
	_spawnZones.push_back(KM::Point(static_cast<F32>(GetLeftBorder()) * 0.33f, GetTopBorder() * 0.9f));
	// 30% from the right border, 10% from the top
	_spawnZones.push_back(KM::Point(static_cast<F32>(GetRightBorder()) * 0.33f, GetTopBorder() * 0.9f));
	// Right on the left border, 60% from the top of the screen
	_spawnZones.push_back(KM::Point(static_cast<F32>(GetLeftBorder()), GetTopBorder() * 0.4f));
	// Right on the right border, 60% from the top of the screen
	_spawnZones.push_back(KM::Point(static_cast<F32>(GetRightBorder()), GetTopBorder() * 0.4f));

	// Create Health Pack Pool
	for(U32 i = 0; i < _healthPackPoolSize; ++i)
	{
		p_HealthPack pack = ObjectFactory::Instance()->MakeHealthPack();
		pack->SetActive(false);
		Level::AddObjectToLevel(pack);
		_healthPackPool.push_back(pack);
	}

	// Create Armor Pool
	for(U32 i = 0; i < _armorPoolSize; ++i)
	{
		p_Armor armor = ObjectFactory::Instance()->MakeArmor();
		armor->SetActive(false);
		Level::AddObjectToLevel(armor);
		_armorPool.push_back(armor);
	}

	// Create Haste Pool
	for(U32 i = 0; i < _hastePoolSize; ++i)
	{
		p_Haste haste = ObjectFactory::Instance()->MakeHaste();
		haste->SetActive(false);
		Level::AddObjectToLevel(haste);
		_hastePool.push_back(haste);
	}
}

void Battleground::v_Update(void)
{
	// Exit or Menu check
	if(KE::Controller::Instance()->GetKeyDown(KE::ESCAPE))
	{
		KE::Engine::Instance()->End();
		return;
	}

	if(_gameover)
	{
		// Run the AI because its fun
		_ProcessAI();

		if(KE::Controller::Instance()->GetKeyDown(KE::Y))
		{
			_ResetLevel();
		}
		else if(KE::Controller::Instance()->GetKeyDown(KE::N))
		{
			KE::Engine::Instance()->End();
		}
		return;
	}

	KE::AudioManager::Instance()->PlaySource(BACKGROUND_MUSIC_SOURCE);

	// Update Round Logic
	if (EventManager::Instance()->HasEvent())
	{
		_ProcessEvents();
	}
	
	_ProcessCollisions();

	if(!_player->Alive())
	{
		_gameover = true;
		_gameOverTitle.SetActive(true);
		_retryText.SetActive(true);
	}

	//Player input loop
	_ProcessInput();

	//Used later, if it can be made to be interesting
	//bool playWalk = false;
	
	//AI loop
	_ProcessAI();
/*
	This sounds dumb... needs some work and some thought
	By sounds dumb, I mean it makes the game hard to play because all the foot steps are distracting. 
	Note: In diablo 3, enemies do not making a walking sound, the player walking sound is very subtle.

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
	F32 offset = 32.0f;
	
	KM::Point spawnOffset{KM::Random::Instance()->RandomFloat(-offset, offset), KM::Random::Instance()->RandomFloat(-offset, offset)};
	
	for(U32 i = 0; i < amount; ++i)
	{		
		for(auto monster : _monsterPool)
		{
			U32 spawnZoneToUse = KM::Random::Instance()->RandomInt(1, _spawnZones.size()) - 1;
			if(!monster->GetActive())
			{
				monster->Setup(type, _spawnZones[spawnZoneToUse] + spawnOffset);
				KE::AudioManager::Instance()->PlaySource(MONSTER_SPAWN_SOURCE);
				break;
			}
			//update rand
			spawnOffset.Set(KM::Random::Instance()->RandomFloat(-offset, offset), KM::Random::Instance()->RandomFloat(-offset, offset));
		}
	}
}

void Battleground::_ProcessCollisions(void)
{
	// Monsters vs Player
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

	// Projectiles vs Monsters
	for(auto projectile : _projectilePool)
	{
		if(projectile->GetActive())
		{
			for(auto monster : _monsterPool)
			{
				if(monster->GetActive() && projectile->OverlapCheck(monster))
				{
					monster->v_Damage(projectile->GetDamage());
					projectile->HitEnemy();
					break;
				}
			}
		}
	}

	// Power ups vs Player
	for(auto pack : _healthPackPool)
	{
		if(pack->GetActive())
		{
			if(pack->OverlapCheck(_player))
			{
				pack->v_PickupAction(_player);
			}
		}
	}

	for(auto armor : _armorPool)
	{
		if(armor->GetActive())
		{
			if(armor->OverlapCheck(_player))
			{
				armor->v_PickupAction(_player);
			}
		}
	}

	for(auto haste : _hastePool)
	{
		if(haste->GetActive())
		{
			if(haste->OverlapCheck(_player))
			{
				haste->v_PickupAction(_player);
			}
		}
	}
}

void Battleground::_ProcessEvents(void)
{	
	_killedThisRound += EventManager::Instance()->CheckEnemiesKilled();
	_score += EventManager::Instance()->CheckPointsEarned();

	// Chance to spawn item on kill
	S32 healthPackSpawnChance = KM::Random::Instance()->RandomInt(1, 100);
	
	if (_killedThisRound >= _roundLength)
	{
		++_roundNumber;
		_killedThisRound = 0;
		_roundLength += _roundLengthIncrease;
	
		// Needs additional logic
		_roundLengthIncrease += 3;

		if(_roundNumber % 3 == 1)
		{
			_maxSpawn += 2;
		}

		// Make health spanw 30% more likely
		healthPackSpawnChance += 30;

		//Make red more likely to spawn
		_redSpawnRate -= 2;

		if(_roundNumber == 5 || _roundNumber == 8)
		{
			_redSpawnRate -= 10;
		}
		
		//Check if we should spawn a blue
		if(_roundNumber == 5 || _roundNumber == 8)
		{
			_spawnBlue = true;
		}
		else if(_roundNumber > 10)
		{
			//10% chance to spawn a blue
			S32 chance = KM::Random::Instance()->RandomInt(0, 99);

			if(chance > 89)
			{
				_spawnBlue = true;
			}
		}
	}

	// 5% chance to spawn a health pack
	if(healthPackSpawnChance >= 95)
	{
		_SpawnItem(HEALTH_ITEM);
	}
	
	S32 powerupSpawnChance = KM::Random::Instance()->RandomInt(0, 99);
	
	if(powerupSpawnChance >= 95)
	{
		_SpawnItem(ARMOR_ITEM);
	}

	powerupSpawnChance = KM::Random::Instance()->RandomInt(0, 99);

	if(powerupSpawnChance >= 90)
	{
		_SpawnItem(HASTE_ITEM);
	}

	Level::UpdateText(_roundNumberText, std::to_string(_roundNumber));
	Level::UpdateText(_scoreText, std::to_string(_score));
}

void Battleground::_ProcessInput(void)
{
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

	if(KE::Controller::Instance()->GetKeyDown(KE::SPACE) || KE::Controller::Instance()->GetKeyDown(KE::UP_ARROW))
	{
		for(auto p : _projectilePool)
		{
			if(!p->GetActive())
			{
				_player->Fire(p);
			}
		}
	}
}

void Battleground::_ProcessAI(void)
{
	// Check if we can spawn more
	if(_canSpawn)
	{
		_canSpawn = false;
		_lastSpawn = 0.0f;
		_Spawn(_maxSpawn, AI_YELLOW_MONSTER);
		
		//Chance to spawn red every time
		S32 chance = KM::Random::Instance()->RandomInt(0, 99);
		
		if(chance > _redSpawnRate)
		{
			_Spawn(1, AI_RED_MONSTER);
		}

		if(_spawnBlue)
		{
			_Spawn(1, AI_BLUE_MONSTER);
			_spawnBlue = false;
		}
	}
	else
	{
		_lastSpawn += KM::Timer::Instance()->DeltaTime();

		if(_lastSpawn >= _spawnRate)
		{
			_canSpawn = true;
		}
	}
	
	// Run through AI states
	for(auto monster : _monsterPool)
	{
		if(monster->GetActive())
		{
			if(monster->GetAIState() == CHOOSE)
			{
				PotentialTargetList targets;

				bool foundTarget = false;

				if(monster->GetType() == AI_RED_MONSTER)
				{
					monster->SetTarget(_player);
					monster->SetAIState(SEEK);
					continue;
				}
				
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

				if(monster->GetType() == AI_BLUE_MONSTER)
				{
					PotentialTarget target;
					target.target = _player;
					target.weight = 50;
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
}

//rename spawn item
bool Battleground::_SpawnItem(ItemType type)
{	
	bool spawnedItem = false;
	switch(type)
	{
		case HEALTH_ITEM :
			for(auto pack : _healthPackPool)
			{
				if(!pack->GetActive())
				{
					pack->SetPosition(_GetRandomXPos(), _player->GetPosition()[y]);
					pack->SetActive(true);
					spawnedItem = true;
					break;
				}
			}
		break;
		case ARMOR_ITEM :
			for(auto armor : _armorPool)
			{
				if(!armor->GetActive())
				{
					armor->SetPosition(_GetRandomXPos(), _player->GetPosition()[y]);
					armor->SetActive(true);
					spawnedItem = true;
					break;
				}
			}
		break;
		case HASTE_ITEM :
			for(auto haste : _hastePool)
			{
				if(!haste->GetActive())
				{
					haste->SetPosition(_GetRandomXPos(), _player->GetPosition()[y]);
					haste->SetActive(true);
					spawnedItem = true;
					break;
				}
			}
		break;
	}
	
	//No item spawned
	return spawnedItem;
}

void Battleground::_ResetLevel(void)
{
	//Player
	_player->SetPosition(_playerDefaultPos);
	_player->v_Reset();

	KM::Point settlementPos = _defaultSettlementPos;

	//Settlements
	for(auto settlement : _settlementList)
	{
		settlement->v_Reset();
		settlement->SetPosition(settlementPos);
		settlementPos[x] += _settlementXOffset;
	}

	//Monsters
	for(auto monster : _monsterPool)
	{
		if(monster->GetActive())
		{
			monster->SetActive(false);
		}
	}
	
	//Items
	for(auto healthPack : _healthPackPool)
	{
		if(healthPack->GetActive())
		{
			healthPack->SetActive(false);
		}
	}

	//Score and Rounds
	_roundNumber		 = 1;
	_killedThisRound	 = 0;
	_roundLength		 = 10;
	_spawnsThisRound	 = 0;
	_maxSpawn		 	 = 3;
	_roundLengthIncrease = 5;
	_canSpawn			 = true;
	_spawnBlue			 = false;
	_lastSpawn			 = 0.0f;
	_score				 = 0;

	Level::UpdateText(_roundNumberText, std::to_string(_roundNumber));
	Level::UpdateText(_scoreText, std::to_string(_score));

	//Game Over text
	_gameOverTitle.SetActive(false);
	_retryText.SetActive(false);
	_gameover = false;

	//Restart Audio
	KE::AudioManager::Instance()->StopSource(BACKGROUND_MUSIC_SOURCE);
}

F32 Battleground::_GetRandomXPos(void)
{
	F32 padding = 50.0f;
	F32 xPos = KM::Random::Instance()->RandomFloat(static_cast<F32>(GetLeftBorder()), static_cast<F32>(GetRightBorder()));

	if(xPos <= static_cast<F32>(GetLeftBorder()) + padding)
	{
		xPos += padding;
	}
	else if(xPos >= static_cast<F32>(GetRightBorder()) - padding)
	{
		xPos -= padding;
	}

	return xPos;
}