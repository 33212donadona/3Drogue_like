#pragma once

#include <list>
#include <string>

namespace aqua
{
	/*!
	 *  @brief      aqua::core���O���
	 */
	namespace core
	{
		class CObject3DResorce;

		class CObject3DManager
		{
		public:
			/*!
			 *  @brief      �C���X�^���X�̎擾
			 *
			 *  @return     �C���X�^���X�ւ̎Q��
			 */
			static CObject3DManager& GetInstance(void);

			/*!
			 *  @brief      �e�N�X�`���̓ǂݍ���
			 *
			 *  @param[in]  file_name   �t�@�C����
			 *
			 *  @return     �e�N�X�`�����\�[�X�N���X
			 */
			CObject3DResorce* Load(const std::string& file_name);

			/*!
			 *  @brief      �e�N�X�`���̉��
			 *
			 *  @param[in]  texture     �e�N�X�`�����\�[�X�N���X
			 */
			void            Unload(CObject3DResorce* model);

			/*!
			 *  @brief      �e�N�X�`���̌���
			 *
			 *  @param[in]  file_name   �t�@�C����
			 *
			 *  @return     �e�N�X�`�����\�[�X�N���X
			 */
			CObject3DResorce* Find(const std::string& file_name);

			/*!
			 *  @brief      �e�N�X�`�����X�g�̃N���A
			 */
			void                    Clear(void);

			/*!
			 *  @brief      �e�N�X�`���̉��
			 */
			void            Delete(CObject3DResorce* model);

		private:
			/*!
			 *  @brief      �R���X�g���N�^
			 */
			CObject3DManager(void);

			/*!
			 *  @brief      �R�s�[�R���X�g���N�^
			 *
			 *  @param[in]  rhs �R�s�[�I�u�W�F�N�g
			 */
			CObject3DManager(const CObject3DManager& rhs);

			/*!
			 *  @brief      �f�X�g���N�^
			 */
			~CObject3DManager(void) = default;

			/*!
			 *  @brief      ������Z�q
			 *
			 *  @param[in]  rhs ����I�u�W�F�N�g
			 *
			 *  @return     ���g�̃I�u�W�F�N�g
			 */
			CObject3DManager& operator=(const CObject3DManager& rhs)
			{

				(void)rhs;

				return *this;

			};

			/*!
			 *  @brief      �e�N�X�`�����\�[�X���X�g
			 */
			typedef std::list<CObject3DResorce*> OBJECT_3D_LIST;

			//! �e�N�X�`�����\�[�X���X�g
			OBJECT_3D_LIST    m_Object3DList;


		};

	}

}