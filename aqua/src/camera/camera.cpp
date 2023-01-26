#include "camera.h"
#include "../graphics/draw_object_3d/draw_object_3d.h"

void aqua::CCamera::Create(int width, int height)
{
	m_Surface.Create(width, height);

	m_Rect.left = 0;
	m_Rect.top = 0;
	m_Rect.right = m_Surface.GetTexture().GetWidth();
	m_Rect.bottom = m_Surface.GetTexture().GetHeight();
	m_ShadowMapHandle = MakeShadowMap(width, height); //! �V���h�E�}�b�v
	// ���C�g�̕�����ݒ�
	SetLightDirection(aqua::CVector3(0.5f, -0.5f, 0.5f));

	// �V���h�E�}�b�v���z�肷�郉�C�g�̕������Z�b�g
	SetShadowMapLightDirection(m_ShadowMapHandle, aqua::CVector3(0.5f, -0.5f, 0.5f));

	// �V���h�E�}�b�v�ɕ`�悷��͈͂�ݒ�
	SetShadowMapDrawArea(m_ShadowMapHandle, aqua::CVector3(-1000.0f, -1.0f, -1000.0f), aqua::CVector3(1000.0f, 1000.0f, 1000.0f));
}

void aqua::CCamera::Draw()
{
	if (!m_Surface.GetTexture().IsEnable() || !visible)return;

	m_Surface.Begin();

	ClearDrawScreen();
	SetWriteZBufferFlag(TRUE);
	SetCameraNearFar(1.0f, 50000.0f);
	SetCameraScreenCenter(screen_center.x, screen_center.y);

	SetCameraPositionAndTarget_UpVecY(camera_position, target_point);

	// Effekseer��3D�`���ݒ肷��
	Effekseer_Sync3DSetting();

	// �V���h�E�}�b�v�ւ̕`��
	ShadowMap_DrawSetup(m_ShadowMapHandle);
	ClearDrawScreenZBuffer();
	aqua::core::IDrawObject3D::DrawList();
	ShadowMap_DrawEnd();

	// �w�i�摜�`��
	m_BackGraph.Draw();

	ClearDrawScreenZBuffer();
	SetUseShadowMap(1, m_ShadowMapHandle);
	aqua::core::IDrawObject3D::DrawList();
	SetWriteZBufferFlag(FALSE);
	SetUseShadowMap(1, -1);

	m_Surface.End();

	int handle = m_Surface.GetTexture().GetResourceHandle();

	DrawGraph((int)screen_position.x, (int)screen_position.y, handle, false);

}

void aqua::CCamera::Delete()
{
	m_BackGraph.Delete();
	DeleteShadowMap(m_ShadowMapHandle);
}

aqua::CCamera::CCamera()
{
	screen_position = aqua::CVector2::ZERO;

	screen_center = { 1920 / 2,1080 / 2 };
}