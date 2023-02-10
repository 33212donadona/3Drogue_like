#pragma once
#include "../job_manager/job_id.h"
#include "../stage/stage_id.h"

struct CommonDataInfo
{
	int crea_target = 10;                             //! �Q�[�����̍ő�X�e�[�W��
	int crea_stage  =  0;                             //! �N���A�����X�e�[�W�̐�
	int easy        =  0;                             //! �N���A�����ȒP�ȃX�e�[�W��
	int nomal      =  0;                             //! �N���A�������ʂȃX�e�[�W��
	int hard        =  0;                             //! �N���A��������X�e�[�W��
	float hit_point      = 100.0f;                    //! �v���C���[�̎c��̗�
	float max_hit_point  = 100.0f;	                  //! �v���C���[�̍ő�̗�
	float game_crea_time = 0.0f;                      //! �N���A�܂ł̎���
	JOB_ID now_job = JOB_ID::STUDENT;                 //! �A�E�����E��
	STAGE_LEVER stage_lever = STAGE_LEVER::EASE; //! ���ɐ�������X�e�[�W�̃��x��

};