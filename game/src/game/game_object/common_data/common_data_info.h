#pragma once
#include "../job_manager/job_id.h"

struct CommonDataInfo
{
	int crea_target = 10;             //! ゲーム中の最大ステージ数
	int crea_stage  =  0;             //! クリアしたステージの数
	int easy        =  0;             //! クリアした簡単なステージ数
	int normal      =  0;             //! クリアした普通なステージ数
	int hard        =  0;             //! クリアした難しいステージ数
	float hit_point      = 100.0f;    //! プレイヤーの残り体力
	float max_hit_point  = 100.0f;	  //! プレイヤーの最大体力
	float game_crea_time = 0.0f;      //! クリアまでの時間
	JOB_ID now_job; //! 就職した職業

};