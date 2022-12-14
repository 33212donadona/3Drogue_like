#pragma once
#include <DxLib.h>
namespace aqua
{

	class CMatrix :public MATRIX
	{
	public:
		//! �R���X�g���N�^
		CMatrix();

		CMatrix(const float in_Float[4][4]);

		CMatrix(const MATRIX& in_Matrix);

		//! �f�X�g���N�^ 
		~CMatrix() = default;

		/*!
		* @brief  X���Œ�̉�]
		*
		* @param[in] Axis       ��]�i���W�A���j
		*/
		CMatrix XRotation(const float Axis = 0.0f);

		/*!
		* @brief  Y���Œ�̉�]
		*
		* @param[in] Axis       ��]�i���W�A���j
		*/
		CMatrix YRotation(const float Axis = 0.0f);

		/*!
		* @brief  Z���Œ�̉�]
		*
		* @param[in] Axis       ��]�i���W�A���j
		*/
		CMatrix ZRotation(const float Axis = 0.0f);

		/*!
		* @brief  �w�肵���������]
		*
		* @param[in] in_Vector  3�����x�N�g��(��)
		*
		* @param[in] Axis       ��]�i���W�A���j
		*/
		void AxisRotation(VECTOR in_Vector, const float Axis = 0.0f);

		/*!
		* @brief  ���s�ړ��s��
		* 
		* @param[in] in_Vector  3�����x�N�g��(�ړ�����)
		*/
		void SetTranslate(VECTOR in_Vector);

		/*!
		* @brief �g��k�W�s��
		* 
		* @param[in] in_Scale  3�����x�N�g��(�g�嗦)
		* 
		*/
		void SetScale(VECTOR in_Scale);

		// �I�[�o�[���[�h
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