#include "select_back_ground.h"
const int CSelectBackGround::m_max_sky = 2;
const int CSelectBackGround::m_max_effect = 2;
const float CSelectBackGround::m_sprite_move_speed = 7.5f;

CSelectBackGround::CSelectBackGround(aqua::IGameObject* parent)
	:aqua::IGameObject(parent, "SelectBackGround")
	, m_EffectRota(0.0f)
{
}

void CSelectBackGround::Initialize()
{
	m_ScrollSkySprite = AQUA_NEW aqua::CSprite[m_max_sky];
	m_EffectSprite = AQUA_NEW aqua::CSprite[m_max_effect];

	for (int sky_i = 0; sky_i < m_max_sky; sky_i++)
	{
		m_ScrollSkySprite[sky_i].Create("data\\select_graph\\select_back.png");
		m_ScrollSkySprite[sky_i].position.x = float(m_ScrollSkySprite[sky_i].GetTextureWidth() * sky_i);
	}
	m_EffectSprite[0].Create("data\\select_graph\\select_effect_in.png");
	m_EffectSprite[1].Create("data\\select_graph\\select_effect_out.png");

	for (int efc_i = 0; efc_i < m_max_effect; efc_i++)
	{
		m_EffectSprite[efc_i].position = aqua::GetWindowSize() / 2.0f;
		m_EffectSprite[efc_i].position.x -= m_EffectSprite[efc_i].GetTextureWidth() / 2.0f;
		m_EffectSprite[efc_i].position.y -= m_EffectSprite[efc_i].GetTextureHeight() / 2.0f;
		m_EffectSprite[efc_i].anchor = 
			aqua::CVector2(m_EffectSprite[efc_i].GetTextureWidth(), m_EffectSprite[efc_i].GetTextureHeight()) / 2.0f;
	}

	m_BackGroundSurface.Create(aqua::GetWindowWidth(), aqua::GetWindowHeight());
}

void CSelectBackGround::Update()
{
	for (int sky_i = 0; sky_i < m_max_sky; sky_i++)
	{
		m_ScrollSkySprite[sky_i].position.x -= m_sprite_move_speed;

		if (m_ScrollSkySprite[sky_i].position.x <= -m_ScrollSkySprite[sky_i].GetTextureWidth())
			m_ScrollSkySprite[sky_i].position.x = m_ScrollSkySprite[sky_i].GetTextureWidth();
	}
	m_EffectRota = (m_EffectRota + 0.25);

	if (m_EffectRota >= 360.0f)
		m_EffectRota = 0.0f;

	int efc_rota = -1;

	for (int efc_i = 0; efc_i < m_max_effect; efc_i++)
	{
		m_EffectSprite[efc_i].rotation = aqua::DegToRad(m_EffectRota * efc_rota);
		efc_rota = 1;
	}
}

void CSelectBackGround::Draw()
{
	m_BackGroundSurface.Begin();
	for (int sky_i = 0; sky_i < m_max_sky; sky_i++)
		m_ScrollSkySprite[sky_i].Draw();

	for (int efc_i = 0; efc_i < m_max_effect; efc_i++)
		m_EffectSprite[efc_i].Draw();
	m_BackGroundSurface.End();
}

void CSelectBackGround::Finalize()
{
	for (int sky_i = 0; sky_i < m_max_sky; sky_i++)
		m_ScrollSkySprite[sky_i].Delete();

	for (int efc_i = 0; efc_i < m_max_effect; efc_i++)
		m_EffectSprite[efc_i].Delete();

	AQUA_SAFE_DELETE_ARRAY(m_ScrollSkySprite);
	AQUA_SAFE_DELETE_ARRAY(m_EffectSprite);

}

int CSelectBackGround::GetBackGround()
{
	return m_BackGroundSurface.GetTexture().GetResourceHandle();
}
