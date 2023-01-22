#pragma once
#include <string>
#include <vector>
#include "..\graphic_filter\graphic_filter.h"
#include "../draw_object_3d/draw_object_3d.h"
#include "..\..\mathematics\mathematics.h"
#include "..\object3D/object3D.h"

/*!
 *  @file       model.h
 *  @brief      3D���f���N���X
 *  @author     Ryuiti Yugue
 *  @date       2022/03/10
 *  @version    7.17
 *
 */
namespace aqua
{
	/*!
	*  @param[in]   HitFlag      �Փ˔���
	*  @param[in]   HitPosition  �Փˍ��W
	*  @param[in]   Normal       �@��
	*/
	struct CollisionInfo
	{

		// �Փ˔���
		bool HitFlag;
		// �Փˍ��W
		CVector3 HitPosition;
		// �@��
		CVector3 Normal;
		// ���f���ƑΏۂ̋���
		CVector3 distance;
	};

	class CModel : public aqua::core::IDrawObject3D
	{
	public:

		/*!
		*  @brief      �R���X�g���N�^
		*/
		CModel();

		/*!
		*  @brief       ���f���𐶐�
		*
		*  @param[in]   file_name �ǂݍ��ރt�@�C��
		*/
		void      Create(const std::string& file_name,int anime_max = 1,float add_frame = 1.0f);

		//  ���f�������
		void      Delete();

		//! �{�[���̐��擾
		int       GetBone()const { return MV1GetFrameNum(m_ModelHandle); }

		/*!
		*  @brief     ���f���������̃{�[�����W���擾
		* 
		* @param[in]  bone_index   �{�[���ԍ�
		*/
		aqua::CVector3 GetBonePosistion(int bone_index);

		/*!
		*  @brief     ���f���������̃{�[����]�s����擾
		*
		* @param[in]  bone_index   �{�[���ԍ�
		*/
		aqua::CMatrix GetBoneMatrix(int bone_index);

		/*!
		*  @brief     ���f���������̃{�[����]�s����擾
		*
		* @param[in]  bone_index   �{�[���ԍ�
		*/
		void  SetMatrix(aqua::CMatrix m);

		//! ���f���̃n���h���擾
		int       GetHandle()const { return m_ModelHandle; };
		//! ���f���̃{�[���擾
		int       GetBoneIndex(std::string bone_name);
		//! ���f���̃{�[���̕\���ݒ�
		void      ChengeFrameVisible(std::string frame_name, bool visible_flag);

		//! �A�j���[�V�����ő吔�̎擾
		int       GetMaxAnimationIndex();

		void      AttachAnimation(int index = 0);
		//! �A�j���[�V�������Đ�
		void      AnimationUpdata();
		
		//! �A�j���[�V�����̏I��
		bool      AnimetionFinished();

		//! �A�j���[�V�����̏I��
		bool      AnimetionFinished(float m_time);

		/*!
		*  @brief       ���Ɛ����̏Փˏ��
		*
		*  @param[in]   bone_name    �{�[����
		*  @param[in]   r            ���a
		*  @param[in]   start_pos    �n�_
		*  @param[in]   end_pos      �I�_
		*/
		CollisionInfo GetBoneCollision
		(	std::string bone_name,
			float r,
			aqua::CVector3 start_pos,
			aqua::CVector3 end_pos
		);


		/*!
		*  @brief       �����ƃ��f���̏Փˏ��
		*
		*  @param[in]   BoneName     �{�[����
		*  @param[in]   start_pos �@ �n�_
		*  @param[in]   end_pos�@�@  �I�_
		*/
		CollisionInfo    GetBoneCollision
		(
			std::string bone_name,
			aqua::CVector3 start_pos,
			aqua::CVector3 end_pos
		);
		/*!
		*  @brief       ���ƃ��f���̏Փˏ��
		*
		*  @param[in]   bone_name    �{�[����
		*  @param[in]   position �@  ���W
		*  @param[in]   r            ���a
		*/
		CollisionInfo    GetBoneCapsuleCollision
		(
			std::string bone_name,
			aqua::CVector3 top_position,
			aqua::CVector3 bottom_position,
			float r
		);

		float          initial_angles;//! ������]�l
		aqua::CVector3 initial_axis;  //! ������]��

		float          angles;        //! ��]�l
		aqua::CVector3 axis;          //! 1�ڂ̉�]��


		aqua::CVector3 position;      //! ���W
		aqua::CVector3 scale;         //! �g�嗦

	private:

		void      Draw()override;

		static const aqua::CMatrix m_Indent;               //! �}�g���N�X�̏�����

		aqua::CObject3D  m_Object3D;                       //! ���f��
		std::vector<int> m_AnimetionObject3D;              //! �A�j���[�V�������f��
		float          m_PrevAngles;                       //! ��]�l
		float          m_PrevInitialAngles;                //! ��]�l
		aqua::CVector3 m_PrevPosition;
		aqua::CVector3 m_PrevScale;

		aqua::CMatrix m_MatrixRotation;                    //! ��]�s��
		aqua::CMatrix m_InitialMatrixRotation;             //! ��]�s��
		aqua::CMatrix m_MatrixPosition;                    //! ���W�s��
		aqua::CMatrix m_MatrixScale;                       //! �g��s��

		int m_ModelHandle;

		int m_max_animetion;

		int m_AttachIndex;

		int m_AttachHandle;

		float m_Frame;
		float m_AddFrame;

		float m_MaxTime;
		float m_NowTime;
	};

}