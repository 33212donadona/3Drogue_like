#include "camera.h"

ICamera::ICamera(aqua::IGameObject* parent, std::string name)
	:aqua::IGameObject(parent,name,"Camera")
{
}

void ICamera::Initialize()
{
	IGameObject::Initialize();
}

void ICamera::Update()
{
	IGameObject::Update();
}

void ICamera::Draw()
{
	m_Camera.Draw();
	IGameObject::Draw();
}

void ICamera::Finalize()
{
	m_Camera.Delete();
	IGameObject::Finalize();
}
