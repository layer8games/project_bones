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