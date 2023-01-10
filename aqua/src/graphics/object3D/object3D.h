#pragma once

#include "object3D_resorce/object3D_resorce.h"

namespace aqua
{
	class CObject3D
	{
    public:
        /*!
         *  @brief      �R���X�g���N�^
         */
        CObject3D();

        /*!
         *  @brief      �R�s�[�R���X�g���N�^
         *
         *  @param[in]  texture     ���f���N���X
         */
        CObject3D(const CObject3D& model);

        /*!
         *  @brief      �f�X�g���N�^
         */
        ~CObject3D() = default;

        /*!
         *  @brief      ���f���̓ǂݍ���
         *
         *  @param[in]  file_name   �t�@�C����
         */
        void    Load(const std::string & file_name,int index = 0);

        /*!
         *  @brief      ���f���̉��
         */
        void    Unload();

        /*!
         *  @brief      ���f���̃��\�[�X�n���h���擾
         *
         *  @return     ���f���̃��\�[�X�n���h���擾
         */
        int     GetResourceHandle() const
        {
            if (!m_Object3DResorce) return AQUA_UNUSED_HANDLE;

            return m_Object3DResorce->GetResourceHandle();
        }

        /*!
         *  @brief      ���f���̓ǂݍ��݃`�F�b�N
         *
         *  @retval     true    �ǂݍ��ݍς�
         *  @retval     false   �ǂݍ��܂�Ă��Ȃ�
         */
        bool    IsEnable(void) const
        {
            if (!m_Object3DResorce) return false;

            return m_Object3DResorce->IsEnable();
        }

        void        ReAttach(int a_i, int handle = -1);

        void        Detach(int a_i);

        void        SetAnimeFrame(int a_i,float time);

        float       GetAnimeTotalTime(int a_i);

        /*!
         *  @brief      ������Z�q�̃I�[�o�[���[�h
         *
         *  @param[in]  texture     ���f���N���X
         */
        CObject3D& operator=(const CObject3D& texture);

    private:

        /*!
         *  @brief      ���f���̉��
         */
        void    Delete(void);

        //! ���f�����\�[�X�N���X
        core::CObject3DResorce* m_Object3DResorce;
	};
}