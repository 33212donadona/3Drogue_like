#include "camera.h"

ICamera::ICamera(aqua::IGameObject* parent, std::string name)
	:aqua::IGameObject(parent,name,"Camera")
{
}
/*
* ‰Šú‰»
*/
void ICamera::Initialize()
{
	IGameObject::Initialize();
}
/*
* XV
*/
void ICamera::Update()
{
	IGameObject::Update();
}
/*
* •`‰æ
*/
void ICamera::Draw()
{
	m_Camera.Draw();
	IGameObject::Draw();
}
/*
* ‰ğ•ú
*/
void ICamera::Finalize()
{
	m_Camera.Delete();
	IGameObject::Finalize();
}
