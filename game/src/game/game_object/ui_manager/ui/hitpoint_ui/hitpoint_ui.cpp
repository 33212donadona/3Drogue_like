#include "hitpoint_ui.h"
#include "../../../common_data/common_data.h"

CHitPointUI::CHitPointUI(aqua::IGameObject* parent)
	:IUserInterface(parent,"HitPointUI")
	, m_CommonData(nullptr)
{
}
/*
* 初期化
*/
void CHitPointUI::Initialize()
{
	m_CommonData = (CCommonData*)aqua::FindGameObject("CommonData");

	m_HitPointSprite.Create("data\\game_graph\\hit_point.png");
	m_HitPointFrameSprite.Create("data\\game_graph\\hit_point_frame.png");
	
	m_HitPointMaskHandle = LoadMask("data\\game_graph\\hit_point_mask.png");

	GetMaskSize(&m_MaskSize.x, &m_MaskSize.y, m_HitPointMaskHandle);

	m_MaskPosition.x = (float)m_HitPointSprite.GetTextureWidth();

	m_HitPointPositionZero = m_HitPointSprite.GetTextureWidth() - m_MaskSize.x * 1.01f;
}
/*
* 更新
*/
void CHitPointUI::Update()
{
	float hp = aqua::Limit(m_CommonData->GetData().hit_point, 0.0f, m_CommonData->GetData().max_hit_point);
	m_MaskPosition.x = m_HitPointPositionZero +  hp / m_CommonData->GetData().max_hit_point * m_MaskSize.x;
}
/*
* 描画
*/
void CHitPointUI::Draw()
{
	m_HitPointFrameSprite.Draw();
	
	CreateMaskScreen();

	DrawMask((int)m_MaskPosition.x, (int)m_MaskPosition.y, m_HitPointMaskHandle, DX_MASKTRANS_NONE);

	m_HitPointSprite.Draw();

	DeleteMaskScreen();
}
/*
* 更新
*/
void CHitPointUI::Finalize()
{
	m_HitPointSprite.Delete();
	m_HitPointFrameSprite.Delete();
	DeleteMask(m_HitPointMaskHandle);

	InitMask();
}
