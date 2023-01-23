#pragma once

#include <list>
#include <string>

namespace aqua
{
	/*!
	 *  @brief      aqua::core名前空間
	 */
	namespace core
	{
		class CObject3DResorce;

		class CObject3DManager
		{
		public:
			/*!
			 *  @brief      インスタンスの取得
			 *
			 *  @return     インスタンスへの参照
			 */
			static CObject3DManager& GetInstance(void);

			/*!
			 *  @brief      テクスチャの読み込み
			 *
			 *  @param[in]  file_name   ファイル名
			 *
			 *  @return     テクスチャリソースクラス
			 */
			CObject3DResorce* Load(const std::string& file_name);

			/*!
			 *  @brief      テクスチャの解放
			 *
			 *  @param[in]  texture     テクスチャリソースクラス
			 */
			void            Unload(CObject3DResorce* model);

			/*!
			 *  @brief      テクスチャの検索
			 *
			 *  @param[in]  file_name   ファイル名
			 *
			 *  @return     テクスチャリソースクラス
			 */
			CObject3DResorce* Find(const std::string& file_name);

			/*!
			 *  @brief      テクスチャリストのクリア
			 */
			void                    Clear(void);

			/*!
			 *  @brief      テクスチャの解放
			 */
			void            Delete(CObject3DResorce* model);

		private:
			/*!
			 *  @brief      コンストラクタ
			 */
			CObject3DManager(void);

			/*!
			 *  @brief      コピーコンストラクタ
			 *
			 *  @param[in]  rhs コピーオブジェクト
			 */
			CObject3DManager(const CObject3DManager& rhs);

			/*!
			 *  @brief      デストラクタ
			 */
			~CObject3DManager(void) = default;

			/*!
			 *  @brief      代入演算子
			 *
			 *  @param[in]  rhs 代入オブジェクト
			 *
			 *  @return     自身のオブジェクト
			 */
			CObject3DManager& operator=(const CObject3DManager& rhs)
			{

				(void)rhs;

				return *this;

			};

			/*!
			 *  @brief      テクスチャリソースリスト
			 */
			typedef std::list<CObject3DResorce*> OBJECT_3D_LIST;

			//! テクスチャリソースリスト
			OBJECT_3D_LIST    m_Object3DList;


		};

	}

}