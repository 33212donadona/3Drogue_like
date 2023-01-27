#pragma once
#include "aqua.h"
#include "../camera.h"

class CPlayer;
class CCommonData;

class CGameCamera : public ICamera
{
public :
	CGameCamera(aqua::IGameObject* parent);
	~CGameCamera() = default;

	void Initialize() override;
	void Update() override;
	void Draw() override;

private:
	static const aqua::CVector3 m_camera_position;
	CPlayer* m_PlayerClass;
	CCommonData* m_CommonData;
};