#pragma once
#include "../camera.h"

class CSelectBackGround;
class CSelectSystem;

class CSelsectCamera : public ICamera
{
public :
	CSelsectCamera(aqua::IGameObject* parent);
	~CSelsectCamera() = default;

	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Finalize()override;

private:
	static const aqua::CVector3 m_camera_position;

	aqua::CLabel       m_StageTargetLabel;

	CSelectBackGround* m_BackGround;
	CSelectSystem*     m_System;
};