#pragma once
#include "aqua.h"

class CUnit;

class CGameCamera : public aqua::IGameObject
{
public :
	CGameCamera(aqua::IGameObject* parent);
	~CGameCamera() = default;

	void Initialize() override;
	void Update() override;
	void Draw() override;

private:
	static const aqua::CVector3 m_camera_position;
	aqua::CCamera m_Camera;
	CUnit* m_UnitClass;
};