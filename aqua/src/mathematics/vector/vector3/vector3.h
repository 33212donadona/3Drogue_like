#pragma once
#include <DxLib.h>

namespace aqua
{
	class CVector3 : public VECTOR
	{
	public:

		/*!
		 *  @brief  �R���X�g���N�^
		 */
		CVector3(void);

		/*!
		 *  @brief  �R���X�g���N�^
		 *
		 *  @param[in]  x   X����
		 *  @param[in]  y   Y����
		 *  @param[in]  z   Z����
		 */
		CVector3(float x, float y, float z);

		/*!
		 *  @brief  �R���X�g���N�^
		 *
		 *  @param[in]  x   X����
		 *  @param[in]  y   Y����
		 *  @param[in]  z   Z����
		 */
		CVector3(int x, int y, int z);

		/*!
		 *  @brief  �R���X�g���N�^
		 *
		 *  @param[in]  v  �x�N�g��
		 */
		CVector3(const VECTOR& v);

		/*!
		 *  @brief  �f�X�g���N�^
		 */
		~CVector3(void) = default;

		/*!
		 *  @brief      �x�N�g���̐��K��<br>
		 *              ���g�̃x�N�g�������K�������
		 *
		 *  @return     ���K�����ꂽ�x�N�g��
		 */
		CVector3            Normalize(void)const;

		/*!
		 *  @brief      �x�N�g���̐��K��
		 *
		 *  @param[in]  v   �x�N�g���N���X
		 *
		 *  @return     ���K�����ꂽ�x�N�g��
		 */
		static CVector3     Normalize(const VECTOR& v);

		/*!
		 *  @brief      �x�N�g���̑傫���擾
		 *
		 *  @return     �x�N�g���̑傫��
		 */
		float               Length(void)const;

		/*!
		 *  @brief      �x�N�g���̑傫���擾
		 *
		 *  @param[in]  v   �x�N�g���N���X
		 *
		 *  @return     �x�N�g���̑傫��
		 */
		static float        Length(const VECTOR& v);

		/*!
		 *  @brief      2�̃x�N�g���̓���<br>
		 *              dot = vA�EvB
		 *
		 *  @param[in]  vA  �x�N�g���N���X
		 *  @param[in]  vB  �x�N�g���N���X
		 *
		 *  @return     ����
		 */
		static float        Dot(const VECTOR& vA, const VECTOR& vB);

		/*!
		 *  @brief      2�̃x�N�g���̊O��<br>
		 *              cross = vA�~vB
		 *
		 *  @param[in]  vA  �x�N�g���N���X
		 *  @param[in]  vB  �x�N�g���N���X
		 *
		 *  @return     �O��
		 */
		static CVector3        Cross(const VECTOR& vA, const VECTOR& vB);

		/*!
		*  @brief        �x�N�g���ϊ�
		*/
		void                   Transform(MATRIX in_Matrix);

		/*!
		 *  @brief      ������Z�q�̃I�[�o�[���[�h
		 *
		 *  @param[in]  v   �x�N�g���N���X
		 *
		 *  @return     �x�N�g���N���X
		 */
		CVector3& operator=(const VECTOR& v)
		{
			x = v.x;
			y = v.y;
			z = v.z;

			return *this;
		}

		/*!
		 *  @brief      ���Z���Z�q�̃I�[�o�[���[�h
		 *
		 *  @param[in]  v   �x�N�g���N���X
		 *
		 *  @return     �x�N�g���N���X
		 */
		CVector3& operator+=(const VECTOR& v)
		{
			x += v.x;
			y += v.y;
			z += v.z;

			return *this;
		}

		/*!
		 *  @brief      ���Z���Z�q�̃I�[�o�[���[�h
		 *
		 *  @param[in]  v   �x�N�g���N���X
		 *
		 *  @return     �x�N�g���N���X
		 */
		CVector3& operator-=(const VECTOR& v)
		{
			x -= v.x;
			y -= v.y;
			z -= v.z;

			return *this;
		}

		/*!
		 *  @brief      ��Z���Z�q�̃I�[�o�[���[�h
		 *
		 *  @param[in]  scalar  �X�J���[�l
		 *
		 *  @return     �x�N�g���N���X
		 */
		CVector3& operator*=(float scalar)
		{
			x *= scalar;
			y *= scalar;
			z *= scalar;

			return *this;
		}

		/*!
		 *  @brief      �������Z�q�̃I�[�o�[���[�h
		 *
		 *  @param[in]  v   �x�N�g���N���X
		 *
		 *  @return     ��̃x�N�g����������
		 *  @retval     true    ������
		 *  @retval     false   �������Ȃ�
		 */
		bool                operator==(const VECTOR& v) const 
		{ return (x == v.x && y == v.y && z == v.z); }

		bool                operator<=(const VECTOR& v) const
		{ return (x <= v.x || y <= v.y || z <= v.z);}
		/*!
		 *  @brief      �s�����Z�q�̃I�[�o�[���[�h
		 *
		 *  @param[in]  v   �x�N�g���N���X
		 *
		 *  @return     ��̃x�N�g�����������Ȃ�
		 *  @retval     true    �������Ȃ�
		 *  @retval     false   ������
		 */
		bool                operator!=(const VECTOR& v) const
		{ return (x != v.x || y != v.y || z != v.z); }

		/*!
		 *  @brief      ���������Z�q�̃I�[�o�[���[�h
		 *
		 *  @param[in]  v   �x�N�g���N���X
		 *
		 *  @return     �x�N�g���N���X
		 */
		CVector3     operator+()
		{
			return *this;
		}

		/*!
		 *  @brief      ���������Z�q�̃I�[�o�[���[�h
		 *
		 *  @return     �x�N�g���N���X
		 */
		CVector3     operator-()const
		{
			return CVector3( -this->x, -this->y, -this->z );
		}
		/*!
		 *  @brief      ���Z���Z�q�̃I�[�o�[���[�h
		 *
		 *  @param[in]  vA  �x�N�g���N���X
		 *
		 *  @return     �x�N�g���N���X
		 */
		CVector3     operator + (const VECTOR& vA)const
		{
			return VAdd(*this,vA);
		}

		/*!
		 *  @brief      ���Z���Z�q�̃I�[�o�[���[�h
		 *
		 *  @param[in]  vA  �x�N�g���N���X
		 *
		 *  @return     �x�N�g���N���X
		 */
		CVector3     operator - (const VECTOR& vA)const
		{
			return VSub(*this,vA);
		}

		/*!
		 *  @brief      ��Z���Z�q�̃I�[�o�[���[�h
		 *
		 *  @param[in]  scalar  �X�J���[�l
		 *
		 *  @return     �x�N�g���N���X
		 */
		CVector3     operator *(float scalar)const
		{
			return CVector3(VScale(*this, scalar));
		}

		/*!
		*  @brief      ��Z���Z�q�̃I�[�o�[���[�h
		*
		*  @param[in]  v VECTOR
		*
		*  @return     �x�N�g���N���X
		*/
		friend CVector3  operator*(const CVector3& m_v, const CVector3& c_v)
		{
			return CVector3(m_v.x * c_v.x, m_v.y * c_v.y, m_v.z * c_v.z);
		}
		/*!
		*  @brief      ��Z���Z�q�̃I�[�o�[���[�h
		*
		*  @param[in]  v CVector3
		*
		*  @return     �x�N�g���N���X
		*/
		friend VECTOR  operator*(const VECTOR& m_v,const CVector3& c_v)
		{
			return VGet(m_v.x * c_v.x, m_v.y * c_v.y, m_v.z * c_v.z);
		}
		/*!
		 *  @brief      ���Z���Z�q�̃I�[�o�[���[�h
		 *
		 *  @param[in]  scalar  �X�J���[�l
		 *
		 *  @return     �x�N�g���N���X
		 */
		CVector3     operator/(float scalar)
		{
			return VScale(*this,1.0f/scalar);
		}

		//! ���������ׂ�0�̃x�N�g��
		static const CVector3   ZERO;
		//! ���������ׂ�1�̃x�N�g��
		static const CVector3   ONE;
	};
}