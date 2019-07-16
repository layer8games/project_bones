#pragma once

enum TextureID
{
	SOLDIER			= 1,
	YELLOW_MONSTER	= 2,
	SETTLEMENT		= 3,
	DEFAULT_BULLET	= 4,
};

enum LevelID
{
	START_MENU	 = 1,
	BATTLEGROUND = 2,
};

enum MonsterAIType
{
	NO_TYPE			  = 0,
	AI_YELLOW_MONSTER = 1,
	AI_RED_MONSTER	  = 2,
	AI_BLUE_MONSTER	  = 3,
};

enum MonsterAIState
{
	NO_STATE	= 0,
	CHOOSE	= 1,
	SEEK	= 2,
	ATTACK	= 3,
};

enum AudioClipID
{
	BATTLE_MUSIC_CLIP			= 1,
	MONSTER_DAMAGE_CLIP			= 2,
	MONSTER_DIE_CLIP			= 3,
	MONSTER_SPAWN_CLIP			= 4,
	MONSTER_WALK_CLIP			= 5,
	PLAYER_DAMAGE_CLIP			= 6,
	PLAYER_DIE_CLIP				= 7,
	PLAYER_DEFAULT_FIRE_CLIP	= 8,
	PLAYER_WALK_CLIP			= 9,
	SETTLEMENT_DAMAGE_CLIP		= 10,
	SETTLEMENT_DIE_CLIP			= 11,
};

enum AudioSourceID
{
	BACKGROUND_MUSIC_SOURCE = 1,
};