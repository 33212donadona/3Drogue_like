#include "camera.h"
#include "../graphics/draw_object_3d/draw_object_3d.h"

const int aqua::CCamera::m_updata_shadow = 5;

void aqua::CCamera::Create(int width, int height)
{
	m_Surface.Create(width, height);

	m_DrawFrame = 0;

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
	// �V���h�E�}�b�v�ւ̕`��

	if ((m_DrawFrame++) % m_updata_shadow == 0)
	{
		ClearDrawScreen();
		ShadowMap_DrawSetup(m_ShadowMapHandle);
		aqua::core::IDrawObject3D::DrawList();
		ShadowMap_DrawEnd();
	}


	m_Surface.Begin();

	ClearDrawScreen();
	SetWriteZBufferFlag(TRUE);

	SetCameraNearFar(1.0f, 50000.0f);
	SetCameraScreenCenter(screen_center.x, screen_center.y);
	SetCameraPositionAndTarget_UpVecY(camera_position, target_point);

	// Effekseer��3D�`���ݒ肷��
	Effekseer_Sync3DSetting();

	// �w�i�摜�`��
	m_BackGraph.Draw();

	ClearDrawScreenZBuffer();
	SetUseShadowMap(0, m_ShadowMapHandle);
	aqua::core::IDrawObject3D::DrawList();
	SetWriteZBufferFlag(FALSE);
	SetUseShadowMap(0, -1);

	m_Surface.End();

	DrawGraph((int)screen_position.x, (int)screen_position.y, m_Surface.GetTexture().GetResourceHandle(), false);
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