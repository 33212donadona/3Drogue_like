#include "camera.h"
#include "../graphics/draw_object_3d/draw_object_3d.h"

void aqua::CCamera::Create(int width, int height)
{
	m_Surface.Create(width, height);

	m_Rect.left = 0;
	m_Rect.top = 0;
	m_Rect.right = m_Surface.GetTexture().GetWidth();
	m_Rect.bottom = m_Surface.GetTexture().GetHeight();
	m_ShadowMapHandle = MakeShadowMap(width, height); //! シャドウマップ
	// ライトの方向を設定
	SetLightDirection(aqua::CVector3(0.5f, -0.5f, 0.5f));

	// シャドウマップが想定するライトの方向もセット
	SetShadowMapLightDirection(m_ShadowMapHandle, aqua::CVector3(0.5f, -0.5f, 0.5f));

	// シャドウマップに描画する範囲を設定
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

	// Effekseerに3D描画を設定する
	Effekseer_Sync3DSetting();

	// シャドウマップへの描画
	ShadowMap_DrawSetup(m_ShadowMapHandle);
	ClearDrawScreenZBuffer();
	aqua::core::IDrawObject3D::DrawList();
	ShadowMap_DrawEnd();

	// 背景画像描画
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