#pragma once
enum class WEAPON_ID
{
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