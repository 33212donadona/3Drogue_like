#include "camera.h"
#include "../graphics/draw_object_3d/draw_object_3d.h"

void aqua::CCamera::Create(int width, int height)
{
	m_Surface.Create(width, height);

	m_Rect.left = 0;
	m_Rect.top = 0;
	m_Rect.right = m_Surface.GetTexture().GetWidth();
	m_Rect.bottom = m_Surface.GetTexture().GetHeight();
}

void aqua::CCamera::Draw()
{
	if (!m_Surface.GetTexture().IsEnable() || !visible)return;

	m_Surface.Begin();

	ClearDrawScreen();

	SetCameraNearFar(15.0f, 50000.0f);

	SetCameraScreenCenter(screen_center.x, screen_center.y);

	//SetCameraPositionAndAngle(camera_position, aqua::DegToRad(angle_y), aqua::DegToRad(angle_x), aqua::DegToRad(0));
	SetCameraPositionAndTarget_UpVecY(camera_position,target_point);
	aqua::core::DrawObject3D::DrawList();

	m_Surface.End();

	int handle = m_Surface.GetTexture().GetResourceHandle();

	DrawGraph((int)screen_position.x,(int)screen_position.y,handle, false);

}

aqua::CCamera::CCamera()
{
	screen_position = aqua::CVector2::ZERO;
	
	screen_center = { 1920 / 2,1080 / 2 };
}