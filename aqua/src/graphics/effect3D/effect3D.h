
/*!
 *  @file       effect3D.h
 *  @brief      Effekseer�p3D�G�t�F�N�g
 */

#pragma once

#include <DxLib.h>
#include <EffekseerForDXLib.h>
#include "../draw_object_3d/draw_object_3d.h"
#include "..\..\mathematics\mathematics.h"
#include ".\..\color\color.h"
#include "..\effekseer\effekseer.h"

 /*!
  *  @brief      aqua���O���
  */
namespace aqua
{
    /*!
     *  @class      CEffect3D
     *
     *  @brief      Effekseer�p3D�G�t�F�N�g�N���X
     */
    class CEffect3D
        : public aqua::core::IDrawObject3D
    {
    public:
        //! �\���ʒu
        aqua::CVector3  position;
        //! �g�嗦
        aqua::CVector3  scale;
        //! ��]�l(���W�A��)
        aqua::CVector3  rotation;
        //! �F
        aqua::CColor    color;

        /*!
         *  @brief  �R���X�g���N�^
         */
        CEffect3D(void);

        /*!
         *  @brief  �f�X�g���N�^
         */
        ~CEffect3D(void) = default;

        /*!
         *  @brief  ����
         *
         *  @param[in]  file_name   �t�@�C����
         */
        void    Create(const std::string& file_name);

        /*!
         *  @brief  ���
         */
        void    Delete(void);

        /*!
         *  @brief  �X�V
         */
        void    Update(void);

        /*!
         *  @brief  �Đ�
         */
        void    Play(void);

        /*!
         *  @brief  ��~
         */
        void    Stop(void);

        /*!
         *  @brief  �G�t�F�N�g�I�����m
         *
         *  @retval true    �G�t�F�N�g�Đ��I��
         *  @retval false   �G�t�F�N�g�Đ���
         */
        bool    Finished(void);

        /*!
         *  @brief  �Đ����̃G�t�F�N�g�̍Đ����x�擾
         *
         *  @return �Đ����x
         */
        float   GetPlayingSpeed(void);

        /*!
         *  @brief  �Đ����̃G�t�F�N�g�̍Đ����x�ݒ�
         *
         *  @param[in]  speed   �Đ����x
         */
        void    SetPlayingSpeed(float speed);

        /*!
         *  @brief  ���\�[�X�n���h���擾
         *
         *  @return ���\�[�X�n���h��
         */
        int     GetResourceHandle(void) const;

    private:
        /*!
         *  @brief  �`��
         */
        void    Draw(void) override;

        //! Effekseer���\�[�X
        CEffekseer  m_Effekseer;
        //! �Đ����̃G�t�F�N�g�n���h��
        int         m_PlayingEffectHandle;
        //! �Đ����x
        float       m_PlaySpeed;
    };
}