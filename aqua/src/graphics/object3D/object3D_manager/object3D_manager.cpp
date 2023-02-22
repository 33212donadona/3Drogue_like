#include "object3D_manager.h"
#include "../object3D_resorce/object3D_resorce.h"
#include "..\..\..\debug\debug.h"
#include "..\..\..\utility\memory\memory.h"

aqua::core::CObject3DManager&
aqua::core::CObject3DManager::GetInstance(void)
{
	static CObject3DManager instance;
	return instance;
}

aqua::core::CObject3DResorce*
aqua::core::CObject3DManager::Load(const std::string& file_name)
{
	// 3Dモデル検索
	CObject3DResorce* find_object_3d = Find(file_name);
	CObject3DResorce* object_3d;
	// 新規生成
	object_3d = AQUA_NEW CObject3DResorce();

		// 読み込み
	// 見つからなかった
	if (!find_object_3d)
		object_3d->Load(file_name);	
	else
		object_3d->DuplicateLoad(find_object_3d->GetResourceHandle(), file_name);

	// 3Dモデルリストに追加
	m_Object3DList.push_back(object_3d);

	// 参照カウンタ加算
	object_3d->AddReference();

	return object_3d;
}

void aqua::core::
CObject3DManager::
Unload(CObject3DResorce* model)
{
	if (!model) return;

	if (m_Object3DList.empty()) return;

	// 参照カウンタ減算
	// 参照がなくなったら解放
	if (model->RemoveReference() > 0) return;

	OBJECT_3D_LIST::iterator it = m_Object3DList.begin();
	OBJECT_3D_LIST::iterator end = m_Object3DList.end();

	while (it != end)
	{
		if ((*it)->GetResourceName() == model->GetResourceName())
		{
			(*it)->Unload();

			AQUA_SAFE_DELETE((*it));

			m_Object3DList.erase(it);

			break;
		}

		++it;
	}
}

aqua::core::CObject3DResorce*
aqua::core::CObject3DManager::
Find(const std::string& file_name)
{
	if (m_Object3DList.empty()) return nullptr;

	OBJECT_3D_LIST::iterator it = m_Object3DList.begin();
	OBJECT_3D_LIST::iterator end = m_Object3DList.end();

	// ファイル名が一致したテクスチャクラスを返す
	while (it != end)
	{
		if ((*it)->GetResourceName() == file_name)
			return (*it);

		++it;
	}

	return nullptr;
}

void aqua::core::CObject3DManager::Clear(void)
{
	if (m_Object3DList.empty()) return;

	OBJECT_3D_LIST::iterator it = m_Object3DList.begin();
	OBJECT_3D_LIST::iterator end = m_Object3DList.end();

	while (it != end)
	{
		if ((*it))
		{
			// テクスチャ解放
			(*it)->Unload();

			AQUA_SAFE_DELETE((*it));
		}

		++it;
	}

	// テクスチャリスト解放
	m_Object3DList.clear();
}
void aqua::core::
CObject3DManager::
Delete(CObject3DResorce* model)
{

	if (!model)return;

	if (m_Object3DList.empty())return;

	if (model->RemoveReference() > 0)return;

	OBJECT_3D_LIST::iterator it = m_Object3DList.begin();
	OBJECT_3D_LIST::iterator end = m_Object3DList.end();

	while (it != end)
	{
		if (model == (*it))
		{
			(*it)->Delete();

			AQUA_SAFE_DELETE((*it));

			m_Object3DList.erase(it);

			break;
		}

		++it;
	}

}

aqua::core::CObject3DManager::CObject3DManager()
{
	m_Object3DList.clear();
}