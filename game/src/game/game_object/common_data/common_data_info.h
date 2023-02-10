#pragma once
#include "../job_manager/job_id.h"
#include "../stage/stage_id.h"

struct CommonDataInfo
{
	int crea_target = 10;                             //! ゲーム中の最大ステージ数
	int crea_stage  =  0;                             //! クリアしたステージの数
	int easy        =  0;                             //! クリアした簡単なステージ数
	int nomal      =  0;                             //! クリアした普通なステージ数
	int hard        =  0;                             //! クリアした難しいステージ数
	float hit_point      = 100.0f;                    //! プレイヤーの残り体力
	float max_hit_point  = 100.0f;	                  //! プレイヤーの最大体力
	float game_crea_time = 0.0f;                      //! クリアまでの時間
	JOB_ID now_job = JOB_ID::STUDENT;                 //! 就職した職業
	STAGE_LEVER stage_lever = STAGE_LEVER::EASE; //! 次に生成するステージのレベル

};