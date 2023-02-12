#pragma once

enum class SoundID
{
	TITLE_BGM,
	SELECT,
	GAME_BGM,
	RESULT_BGM,

	PUNCH,
	SLASH,
	MAGIC,
	MONEY,

	GET_MONEY,

	SENE_BOTTON,
	STAGE_BOTTON,

	MAX
};

class SoundInfo
{
public:

	std::string name;
	bool flag;

	SoundInfo()
		: name("")
		, flag(false) 
	{};

	SoundInfo(std::string m_name, bool m_flag)
		: name(m_name)
		, flag(m_flag)
	{};

	SoundInfo(const SoundInfo& s)
		: name(s.name)
		, flag(s.flag) 
	{};

	SoundInfo& operator=(SoundInfo& s)
	{
		name = s.name;
		flag = s.flag;
		return *this;
	}

};