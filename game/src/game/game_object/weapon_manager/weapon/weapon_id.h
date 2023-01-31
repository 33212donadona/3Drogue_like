#pragma once
enum class WEAPON_ID
{
	FIST,
	SWORD,
	MAGIC,
	MONEY,
	MAX
};

struct WEAPON_STATE
{
	WEAPON_ID id;
	float attack;
	float durability;
};