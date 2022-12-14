#pragma once
#include "../draw_object_3d/draw_object_3d.h"
#include <DxLib.h>

namespace aqua
{
	class CSphele : public aqua::core::DrawObject3D
	{
	public:

		struct SpheleData
		{
			int DivNum = 32;
			unsigned int DifColor = GetColor(255, 0, 0);
			unsigned int SpcColor = GetColor(255, 255, 255);
			bool FillFlag = true;
		};


		/*!
		* @brief  ���̐���
		*
		* @param[in] div_num   ���̃|���S���ׂ̍���
		* @param[in] dif_color ���_�f�B�t���[�Y�J���[
		* @param[in] spc_color ���_�X�y�L�����J���[
		* @param[in] fill_flag ���̓h��Ԃ�
		*/
		void Create(
			int div_num = 32,
			unsigned int dif_color = GetColor(255, 0, 0),
			unsigned int spc_Color = GetColor(255, 255, 255),
			bool fill_flag = true);

		void Create(SpheleData sphele_data);

		void Delete();

		/*!
		* @brief  ���̍X�V
		*
		* @param[in]  CenterPosition  ���S�_
		*
		* @param[in]  r               ���a
		*/
		void Updata(VECTOR CenterPosition, float r);

	private:

		void      Draw()override;

		VECTOR            m_Position;
		float             m_Radius;

		SpheleData m_SpheleData; //! ���̐ÓI���

	};
}