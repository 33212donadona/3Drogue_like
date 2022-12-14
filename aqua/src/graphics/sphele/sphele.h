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
		* @brief  球の生成
		*
		* @param[in] div_num   球のポリゴンの細かさ
		* @param[in] dif_color 頂点ディフューズカラー
		* @param[in] spc_color 頂点スペキュラカラー
		* @param[in] fill_flag 球の塗りつぶし
		*/
		void Create(
			int div_num = 32,
			unsigned int dif_color = GetColor(255, 0, 0),
			unsigned int spc_Color = GetColor(255, 255, 255),
			bool fill_flag = true);

		void Create(SpheleData sphele_data);

		void Delete();

		/*!
		* @brief  球の更新
		*
		* @param[in]  CenterPosition  中心点
		*
		* @param[in]  r               半径
		*/
		void Updata(VECTOR CenterPosition, float r);

	private:

		void      Draw()override;

		VECTOR            m_Position;
		float             m_Radius;

		SpheleData m_SpheleData; //! 球の静的情報

	};
}