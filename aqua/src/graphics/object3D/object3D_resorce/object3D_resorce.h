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
			 *  @brief      モデルの読み込み
			 *
			 *  @param[in]  file_name   ファイル名
			 */
			void        Load(const std::string& file_name,int index = 0);

			/*!
			*  @brief       モデルの再読み込み
			* 
			*  @param[in]  file_name   ファイル名
			*/
			void        DuplicateLoad(const std::string& file_name);

			/*!
			 *  @brief      モデルの解放
			 */
			void        Unload(void);

			int         GetBone()const { return m_ModelBone; }


			void        ReAttach(int a_i, int handle = -1);

			void        Dettach(int a_i);

			void        SetAnimeFrame(int a_i,float time);

			float       GetAnimeTotalTime(int a_i);

		private:

			/*!
			*  @brief      クラスをフレンド登録
			*/
			friend class CObject3D;
			friend class CObject3DManager;


			/*!
			 *  @brief      オブジェクトの解放
			 */
			void        Delete(void);

			//! モデルに含まれるボーンの数
			int m_ModelBone;
		};

	}
}