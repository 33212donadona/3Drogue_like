#include "camera.h"

ICamera::ICamera(aqua::IGameObject* parent, std::string name)
	:aqua::IGameObject(parent,name,"Camera")
{
}
/*
* 初期化
*/
void ICamera::Initialize()
{
	IGameObject::Initialize();
}
/*
* 更新
*/
void ICamera::Update()
{
	IGameObject::Update();
}
/*
* 描画
*/
void ICamera::Draw()
{
	m_Camera.Draw();
	IGameObject::Draw();
}
/*
* 解放
*/
void ICamera::Finalize()
{
	m_Camera.Delete();
	IGameObject::Finalize();
}
