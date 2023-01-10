#pragma once
enum class WEAPON_ID
{
	FIST,
	SWORD,
	MAGIC_STICK,
	MAX
};

struct WEAPON_STATE
{
	WEAPON_ID id = WEAPON_ID::MAX;
	float durability = 0; //! ‘Ï‹v“x
	float attack = 0;     //! UŒ‚—Í
};