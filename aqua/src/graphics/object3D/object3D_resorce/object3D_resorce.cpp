
/*!
 *  @file       object3D_resorce.cpp
 *  @brief      3Dモデルリソース
 */

#include "object3D_resorce.h"
#include "../object3D_manager/object3D_manager.h"
#include "../../../debug/debug.h"
#include "../../../utility/utility.h"
#include <DxLib.h>

aqua::core::CObject3DResorce::CObject3DResorce()
	: IResourceObject(aqua::core::RESOURCE_TYPE::LOAD_TEXTURE)
{
	m_ModelBone = 0;
}

void aqua::core::CObject3DResorce::Load(const std::string& file_name, int index)
{
	// モデル読み込み
	if (m_Enabel)return;

	m_ResourceHandle = MV1LoadModel(file_name.c_str());

	AQUA_DX_ASSERT(m_ResourceHandle, file_name + "の読み込みに失敗しました。");

	MV1AttachAnim(m_ResourceHandle, index, -1, FALSE);

	m_ModelBone = MV1GetFrameNum(m_ResourceHandle);

	// ファイルパスを保存
	m_ResourceName = file_name;

	// 読み込み済み
	m_Enabel = true;
}

void aqua::core::CObject3DResorce::DuplicateLoad(const int handle, std::string name)
{
	// モデル読み込み
	if (m_Enabel)return;

	// モデル読み込み
	int h = MV1DuplicateModel(handle);

	AQUA_DX_ASSERT(h,"モデルの読み込みに失敗しました。");

	MV1AttachAnim(h,0, -1, FALSE);

	m_ModelBone = MV1GetFrameNum(h);

	// ファイルパスを保存
	m_ResourceName = name;

	m_Enabel = true;

	m_ResourceHandle = h;
}

void aqua::core::CObject3DResorce::Unload(void)
{
	MV1DeleteModel(m_ResourceHandle);

	m_ResourceHandle = AQUA_UNUSED_HANDLE;

	m_ResourceName.clear();

	m_ReferenceCount = 0;

	m_ResourceType = RESOURCE_TYPE::DUMMY;

	m_Enabel = false;
}

void aqua::core::CObject3DResorce::ReAttach(int a_i, int handle)
{
	MV1AttachAnim(m_ResourceHandle, a_i, handle, FALSE);
}

void aqua::core::CObject3DResorce::Dettach(int a_i)
{
	MV1DetachAnim(m_ResourceHandle, a_i);
}

void aqua::core::CObject3DResorce::SetAnimeFrame(int a_i, float time)
{
	MV1SetAttachAnimTime(m_ResourceHandle, a_i, time);
}

float aqua::core::CObject3DResorce::GetAnimeTotalTime(int a_i)
{
	return MV1GetAttachAnimTotalTime(m_ResourceHandle, a_i);
}

void aqua::core::CObject3DResorce::Delete(void)
{
	m_ResourceName.clear();

	m_ReferenceCount = 0;

	m_ResourceType = RESOURCE_TYPE::DUMMY;

	m_Enabel = false;
}
