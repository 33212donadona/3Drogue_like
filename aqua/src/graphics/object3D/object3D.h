#pragma once

#include "object3D_resorce/object3D_resorce.h"

namespace aqua
{
	class CObject3D
	{
    public:
        /*!
         *  @brief      コンストラクタ
         */
        CObject3D();

        /*!
         *  @brief      コピーコンストラクタ
         *
         *  @param[in]  texture     モデルクラス
         */
        CObject3D(const CObject3D& model);

        /*!
         *  @brief      デストラクタ
         */
        ~CObject3D() = default;

        /*!
         *  @brief      モデルの読み込み
         *
         *  @param[in]  file_name   ファイル名
         */
        void    Load(const std::string & file_name,int index = 0);

        /*!
         *  @brief      モデルの解放
         */
        void    Unload();

        /*!
         *  @brief      モデルのリソースハンドル取得
         *
         *  @return     モデルのリソースハンドル取得
         */
        int     GetResourceHandle() const
        {
            if (!m_Object3DResorce) return AQUA_UNUSED_HANDLE;

            return m_Object3DResorce->GetResourceHandle();
        }

        /*!
         *  @brief      モデルの読み込みチェック
         *
         *  @retval     true    読み込み済み
         *  @retval     false   読み込まれていない
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
         *  @brief      代入演算子のオーバーロード
         *
         *  @param[in]  texture     モデルクラス
         */
        CObject3D& operator=(const CObject3D& texture);

    private:

        /*!
         *  @brief      モデルの解放
         */
        void    Delete(void);

        //! モデルリソースクラス
        core::CObject3DResorce* m_Object3DResorce;
	};
}