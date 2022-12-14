#pragma once
#include <DxLib.h>
namespace aqua
{

	class CMatrix :public MATRIX
	{
	public:
		//! コンストラクタ
		CMatrix();

		CMatrix(const float in_Float[4][4]);

		CMatrix(const MATRIX& in_Matrix);

		//! デストラクタ 
		~CMatrix() = default;

		/*!
		* @brief  X軸固定の回転
		*
		* @param[in] Axis       回転（ラジアン）
		*/
		CMatrix XRotation(const float Axis = 0.0f);

		/*!
		* @brief  Y軸固定の回転
		*
		* @param[in] Axis       回転（ラジアン）
		*/
		CMatrix YRotation(const float Axis = 0.0f);

		/*!
		* @brief  Z軸固定の回転
		*
		* @param[in] Axis       回転（ラジアン）
		*/
		CMatrix ZRotation(const float Axis = 0.0f);

		/*!
		* @brief  指定した軸から回転
		*
		* @param[in] in_Vector  3次元ベクトル(軸)
		*
		* @param[in] Axis       回転（ラジアン）
		*/
		void AxisRotation(VECTOR in_Vector, const float Axis = 0.0f);

		/*!
		* @brief  平行移動行列
		* 
		* @param[in] in_Vector  3次元ベクトル(移動方向)
		*/
		void SetTranslate(VECTOR in_Vector);

		/*!
		* @brief 拡大縮集行列
		* 
		* @param[in] in_Scale  3次元ベクトル(拡大率)
		* 
		*/
		void SetScale(VECTOR in_Scale);

		// オーバーロード
		CMatrix& operator=(const MATRIX Am)
		{
			return *this = Am.m;
		}

		CMatrix& operator+=(const MATRIX& Am)
		{
			return *this = MAdd(*this, Am);
		}

		CMatrix& operator-=(const MATRIX& Am)
		{

			*this = MAdd(*this, MScale(Am, -1.0f));

			return *this;
		}

		CMatrix& operator*= (float scale)
		{
			*this = MScale(*this, scale);
			return *this;
		}

		CMatrix& operator*= (const CMatrix& Am)
		{
			*this = MMult(*this, Am);
			return *this;
		}

		CMatrix operator+(const MATRIX& Am)
		{
			return MAdd(*this, Am);
		}

		CMatrix operator-(const MATRIX& Am)
		{
			return MAdd(*this, MScale(Am, -1.0f));
		}

		CMatrix operator*(const MATRIX& Am)
		{
			return MMult(*this, Am);
		}

		CMatrix operator*(float Am)
		{
			return MScale(*this, Am);
		}

		CMatrix operator/(float Am)
		{
			return MScale(*this, 1.0f / Am);
		}

	};


}