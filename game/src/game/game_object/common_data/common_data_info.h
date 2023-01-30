#pragma once

struct CommonDataInfo
{
	const int selct_max_mode = 3;
	int max_stage;                //!ゲーム中の最大ステージ数
	int crea_stage;
	int easy;
	int normal;
	int hard;

	float game_crea_time;
};