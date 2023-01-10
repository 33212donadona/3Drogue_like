#pragma once

#include "..\..\..\resources\resources.h"

namespace aqua
{
	namespace core
	{


		class CObject3DResorce : public IResourceObject
		{

		public:

			CObject3DResorce();

			~CObject3DResorce() = default;

			/*!
			 *  @brief      ���f���̓ǂݍ���
			 *
			 *  @param[in]  file_name   �t�@�C����
			 */
			void        Load(const std::string& file_name,int index = 0);

			/*!
			*  @brief       ���f���̍ēǂݍ���
			* 
			*  @param[in]  file_name   �t�@�C����
			*/
			void        DuplicateLoad(const std::string& file_name);

			/*!
			 *  @brief      ���f���̉��
			 */
			void        Unload(void);

			int         GetBone()const { return m_ModelBone; }


			void        ReAttach(int a_i, int handle = -1);

			void        Dettach(int a_i);

			void        SetAnimeFrame(int a_i,float time);

			float       GetAnimeTotalTime(int a_i);

		private:

			/*!
			*  @brief      �N���X���t�����h�o�^
			*/
			friend class CObject3D;
			friend class CObject3DManager;


			/*!
			 *  @brief      �I�u�W�F�N�g�̉��
			 */
			void        Delete(void);

			//! ���f���Ɋ܂܂��{�[���̐�
			int m_ModelBone;
		};

	}
}