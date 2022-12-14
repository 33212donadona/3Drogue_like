#pragma once
#include <DxLib.h>

namespace aqua
{
	class CVector3 : public VECTOR
	{
	public:

		/*!
		 *  @brief  コンストラクタ
		 */
		CVector3(void);

		/*!
		 *  @brief  コンストラクタ
		 *
		 *  @param[in]  x   X成分
		 *  @param[in]  y   Y成分
		 *  @param[in]  z   Z成分
		 */
		CVector3(float x, float y, float z);

		/*!
		 *  @brief  コンストラクタ
		 *
		 *  @param[in]  x   X成分
		 *  @param[in]  y   Y成分
		 *  @param[in]  z   Z成分
		 */
		CVector3(int x, int y, int z);

		/*!
		 *  @brief  コンストラクタ
		 *
		 *  @param[in]  v  ベクトル
		 */
		CVector3(const VECTOR& v);

		/*!
		 *  @brief  デストラクタ
		 */
		~CVector3(void) = default;

		/*!
		 *  @brief      ベクトルの正規化<br>
		 *              自身のベクトルも正規化される
		 *
		 *  @return     正規化されたベクトル
		 */
		CVector3            Normalize(void)const;

		/*!
		 *  @brief      ベクトルの正規化
		 *
		 *  @param[in]  v   ベクトルクラス
		 *
		 *  @return     正規化されたベクトル
		 */
		static CVector3     Normalize(const VECTOR& v);

		/*!
		 *  @brief      ベクトルの大きさ取得
		 *
		 *  @return     ベクトルの大きさ
		 */
		float               Length(void)const;

		/*!
		 *  @brief      ベクトルの大きさ取得
		 *
		 *  @param[in]  v   ベクトルクラス
		 *
		 *  @return     ベクトルの大きさ
		 */
		static float        Length(const VECTOR& v);

		/*!
		 *  @brief      2つのベクトルの内積<br>
		 *              dot = vA・vB
		 *
		 *  @param[in]  vA  ベクトルクラス
		 *  @param[in]  vB  ベクトルクラス
		 *
		 *  @return     内積
		 */
		static float        Dot(const VECTOR& vA, const VECTOR& vB);

		/*!
		 *  @brief      2つのベクトルの外積<br>
		 *              cross = vA×vB
		 *
		 *  @param[in]  vA  ベクトルクラス
		 *  @param[in]  vB  ベクトルクラス
		 *
		 *  @return     外積
		 */
		static CVector3        Cross(const VECTOR& vA, const VECTOR& vB);

		/*!
		*  @brief        ベクトル変換
		*/
		void                   Transform(MATRIX in_Matrix);

		/*!
		 *  @brief      代入演算子のオーバーロード
		 *
		 *  @param[in]  v   ベクトルクラス
		 *
		 *  @return     ベクトルクラス
		 */
		CVector3& operator=(const VECTOR& v)
		{
			x = v.x;
			y = v.y;
			z = v.z;

			return *this;
		}

		/*!
		 *  @brief      加算演算子のオーバーロード
		 *
		 *  @param[in]  v   ベクトルクラス
		 *
		 *  @return     ベクトルクラス
		 */
		CVector3& operator+=(const VECTOR& v)
		{
			x += v.x;
			y += v.y;
			z += v.z;

			return *this;
		}

		/*!
		 *  @brief      減算演算子のオーバーロード
		 *
		 *  @param[in]  v   ベクトルクラス
		 *
		 *  @return     ベクトルクラス
		 */
		CVector3& operator-=(const VECTOR& v)
		{
			x -= v.x;
			y -= v.y;
			z -= v.z;

			return *this;
		}

		/*!
		 *  @brief      乗算演算子のオーバーロード
		 *
		 *  @param[in]  scalar  スカラー値
		 *
		 *  @return     ベクトルクラス
		 */
		CVector3& operator*=(float scalar)
		{
			x *= scalar;
			y *= scalar;
			z *= scalar;

			return *this;
		}

		/*!
		 *  @brief      等価演算子のオーバーロード
		 *
		 *  @param[in]  v   ベクトルクラス
		 *
		 *  @return     二つのベクトルが等しい
		 *  @retval     true    等しい
		 *  @retval     false   等しくない
		 */
		bool                operator==(const VECTOR& v) const 
		{ return (x == v.x && y == v.y && z == v.z); }

		bool                operator<=(const VECTOR& v) const
		{ return (x <= v.x || y <= v.y || z <= v.z);}
		/*!
		 *  @brief      不等演算子のオーバーロード
		 *
		 *  @param[in]  v   ベクトルクラス
		 *
		 *  @return     二つのベクトルが等しくない
		 *  @retval     true    等しくない
		 *  @retval     false   等しい
		 */
		bool                operator!=(const VECTOR& v) const
		{ return (x != v.x || y != v.y || z != v.z); }

		/*!
		 *  @brief      正符号演算子のオーバーロード
		 *
		 *  @param[in]  v   ベクトルクラス
		 *
		 *  @return     ベクトルクラス
		 */
		CVector3     operator+()
		{
			return *this;
		}

		/*!
		 *  @brief      負符号演算子のオーバーロード
		 *
		 *  @return     ベクトルクラス
		 */
		CVector3     operator-()const
		{
			return CVector3( -this->x, -this->y, -this->z );
		}
		/*!
		 *  @brief      加算演算子のオーバーロード
		 *
		 *  @param[in]  vA  ベクトルクラス
		 *
		 *  @return     ベクトルクラス
		 */
		CVector3     operator + (const VECTOR& vA)const
		{
			return VAdd(*this,vA);
		}

		/*!
		 *  @brief      減算演算子のオーバーロード
		 *
		 *  @param[in]  vA  ベクトルクラス
		 *
		 *  @return     ベクトルクラス
		 */
		CVector3     operator - (const VECTOR& vA)const
		{
			return VSub(*this,vA);
		}

		/*!
		 *  @brief      乗算演算子のオーバーロード
		 *
		 *  @param[in]  scalar  スカラー値
		 *
		 *  @return     ベクトルクラス
		 */
		CVector3     operator *(float scalar)const
		{
			return CVector3(VScale(*this, scalar));
		}

		/*!
		*  @brief      乗算演算子のオーバーロード
		*
		*  @param[in]  v VECTOR
		*
		*  @return     ベクトルクラス
		*/
		friend CVector3  operator*(const CVector3& m_v, const CVector3& c_v)
		{
			return CVector3(m_v.x * c_v.x, m_v.y * c_v.y, m_v.z * c_v.z);
		}
		/*!
		*  @brief      乗算演算子のオーバーロード
		*
		*  @param[in]  v CVector3
		*
		*  @return     ベクトルクラス
		*/
		friend VECTOR  operator*(const VECTOR& m_v,const CVector3& c_v)
		{
			return VGet(m_v.x * c_v.x, m_v.y * c_v.y, m_v.z * c_v.z);
		}
		/*!
		 *  @brief      除算演算子のオーバーロード
		 *
		 *  @param[in]  scalar  スカラー値
		 *
		 *  @return     ベクトルクラス
		 */
		CVector3     operator/(float scalar)
		{
			return VScale(*this,1.0f/scalar);
		}

		//! 成分がすべて0のベクトル
		static const CVector3   ZERO;
		//! 成分がすべて1のベクトル
		static const CVector3   ONE;
	};
}