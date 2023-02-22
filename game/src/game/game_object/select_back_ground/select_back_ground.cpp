#include "select_back_ground.h"
#include "../scene_manager/scene/2_select/select_system/select_system.h"
const int CSelectBackGround::m_max_sky = 2;
const int CSelectBackGround::m_max_effect = 2;
const float CSelectBackGround::m_sprite_move_speed = 7.5f;
const float CSelectBackGround::m_light_time = 0.5f;
const std::string CSelectBackGround::m_bg_filr_name[] =
{
	"data\\select_graph\\sub.png",
	"data\\select_graph\\medium.png",
	"data\\select_graph\\high.png"
};
const std::string CSelectBackGround::m_light_filr_name[] =
{
	"data\\select_graph\\move_left_key_light.png",
	"data\\select_graph\\move_right_key_light.png"
};

CSelectBackGround::CSelectBackGround(aqua::IGameObject* parent)
	:aqua::IGameObject(parent, "SelectBackGround")
	, m_EffectRota(0.0f)
	, m_SelectSystem(nullptr)
	, m_AlphaReta(255)
{
}
/*
* èâä˙âª
*/
void CSelectBackGround::Initialize()
{
	std::vector<aqua::CSprite> vs;

	for (int sky_j = 0; sky_j < (int)LAVEL_BG::MAX; sky_j++)
	{
		aqua::CSprite s;

		s.Create(m_bg_filr_name[sky_j]);

		vs.push_back(s);
	}

	m_ScrollSkySprite.assign(m_max_sky, vs);

	m_EffectSprite = AQUA_NEW aqua::CSprite[m_max_effect];

	for (int sky_i = 0; sky_i < m_max_sky; sky_i++)
		for (int sky_j = 0; sky_j < (int)LAVEL_BG::MAX; sky_j++)
		{
			if (sky_j != (int)LAVEL_BG::SUB)
				m_ScrollSkySprite[sky_i][sky_j].color.alpha = (unsigned char)0;

			m_ScrollSkySprite[sky_i][sky_j].position.x = float(m_ScrollSkySprite[sky_i][sky_j].GetTextureWidth() * sky_i);
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

	for (int k_i = 0; k_i < (int)CAN_MOVE_ID::MAX; k_i++)
	{
		m_MoveKey[k_i].Create("data\\select_graph\\key_graph.png");
		m_MoveKeyLight[k_i].Create(m_light_filr_name[k_i]);
		m_MoveKey[k_i].position = aqua::GetWindowSize() / 2;
		m_MoveKey[k_i].position.y -= m_MoveKey[k_i].GetTextureHeight() / 2;
		m_MoveKey[k_i].position.x -= m_MoveKey[k_i].GetTextureWidth() / 2;

		if (k_i)
			m_MoveKey[k_i].position.x += aqua::GetWindowWidth() / 5;
		else
			m_MoveKey[k_i].position.x -= aqua::GetWindowWidth() / 5;

		m_MoveKeyLight[k_i].position = m_MoveKey[k_i].position;
	}

	m_LightTimer.Setup(m_light_time);

	m_BackGroundSurface.Create(aqua::GetWindowWidth(), aqua::GetWindowHeight());
}
/*
* çXêV
*/
void CSelectBackGround::Update()
{
	if (!m_SelectSystem)
		m_SelectSystem = (CSelectSystem*)aqua::FindGameObject("SelectSystem");

	ChangeBackGournd();

	EmittingLight();

	for (int sky_i = 0; sky_i < m_max_sky; sky_i++)
	{
		for (int sky_j = 0; sky_j < (int)LAVEL_BG::MAX; sky_j++)
		{
			m_ScrollSkySprite[sky_i][sky_j].position.x -= m_sprite_move_speed;

			if (m_ScrollSkySprite[sky_i][sky_j].position.x <= -m_ScrollSkySprite[sky_i][sky_i].GetTextureWidth())
				m_ScrollSkySprite[sky_i][sky_j].position.x = (float)m_ScrollSkySprite[sky_i][sky_i].GetTextureWidth();
		}
	}

	m_EffectRota = (m_EffectRota + 0.25f);

	if (m_EffectRota >= 360.0f)
		m_EffectRota = 0.0f;

	int efc_rota = -1;

	for (int efc_i = 0; efc_i < m_max_effect; efc_i++)
	{
		m_EffectSprite[efc_i].rotation = aqua::DegToRad(m_EffectRota * efc_rota);
		efc_rota = 1;
	}
}
/*
* ï`âÊ
*/
void CSelectBackGround::Draw()
{
	m_BackGroundSurface.Begin();

	ClearDrawScreen();

	for (int sky_i = 0; sky_i < m_max_sky; sky_i++)
	{
		for (int sky_j = 0; sky_j < (int)LAVEL_BG::MAX; sky_j++)
		{
			if (m_ScrollSkySprite[sky_i][sky_j].color.alpha != (unsigned char)0)
				m_ScrollSkySprite[sky_i][sky_j].Draw();
		}
	}

	for (int efc_i = 0; efc_i < m_max_effect; efc_i++)
		m_EffectSprite[efc_i].Draw();

	for (int k_i = 0; k_i < (int)CAN_MOVE_ID::MAX; k_i++)
	{
		m_MoveKey[k_i].Draw();
		m_MoveKeyLight[k_i].Draw();
	}

	m_BackGroundSurface.End();
}
/*
* âï˙
*/
void CSelectBackGround::Finalize()
{
	for (int sky_i = 0; sky_i < m_max_sky; sky_i++)
		for (int sky_j = 0; sky_j < (int)LAVEL_BG::MAX; sky_j++)
			m_ScrollSkySprite[sky_i][sky_j].Delete();

	for (int efc_i = 0; efc_i < m_max_effect; efc_i++)
		m_EffectSprite[efc_i].Delete();

	for (int k_i = 0; k_i < (int)CAN_MOVE_ID::MAX; k_i++)
	{
		m_MoveKey[k_i].Delete();
		m_MoveKeyLight[k_i].Delete();
	}

	m_ScrollSkySprite.clear();

	AQUA_SAFE_DELETE_ARRAY(m_EffectSprite);

}
/*
* îwåiÇÃÉnÉìÉhÉãéÊìæ
*/
aqua::CSurface& CSelectBackGround::GetBackGround()
{
	return m_BackGroundSurface;
}
/*
* îwåiÇÃçXêV
*/
void CSelectBackGround::ChangeBackGournd()
{
	if (!m_SelectSystem)return;
	if (m_SelectSystem->GetNowLavel() == m_SelectSystem->GetPrevLavel())
	{
		if (m_AlphaReta != 0)
			m_AlphaReta = 0;

		if (m_ScrollSkySprite[0][m_SelectSystem->GetPrevLavel()].color.alpha == (unsigned char)0)
			return;
	}

	m_AlphaReta += (unsigned char)2.55;

	for (int sky_i = 0; sky_i < m_max_sky; sky_i++)
	{

		m_ScrollSkySprite[sky_i][m_SelectSystem->GetNowLavel()].color.alpha =
			(unsigned char)aqua::Limit((int)m_AlphaReta, 0, 255);

		m_ScrollSkySprite[sky_i][m_SelectSystem->GetPrevLavel()].color.alpha =
			(unsigned char)aqua::Limit(255 - (int)m_AlphaReta, 0, 255);
	}
}
/*
* à⁄ìÆÇ≈Ç´ÇÈÇ©Ç«Ç§Ç©Çï`âÊ
*/
void CSelectBackGround::EmittingLight()
{

	for (int k_i = 0; k_i < (int)CAN_MOVE_ID::MAX; k_i++)
	{
		if ((m_SelectSystem->GetNowLavel() + k_i) % ((int)CAN_MOVE_ID::MAX + 1) == 0)
		{
			m_MoveKeyLight[k_i].color.alpha = (unsigned char)0;
			m_MoveKey[k_i].color = m_MoveKeyLight[k_i].color;
		}
		else
		{
			m_MoveKeyLight[k_i].color = aqua::CColor::WHITE;

			if (!m_LightTimer.Finished())
			{
				m_MoveKeyLight[k_i].color.alpha = (unsigned char)aqua::easing::InCubic
				(
					m_LightTimer.GetTime(),
					m_LightTimer.GetLimit(),
					255.0f,
					0.0f
				);
			}
			else
			{
				m_MoveKeyLight[k_i].color.alpha = (unsigned char)aqua::easing::OutCubic
				(
					m_LightTimer.GetTime() - m_LightTimer.GetLimit(),
					m_LightTimer.GetLimit(),
					0.0f,
					255.0f
				);

				if (m_LightTimer.GetTime() - m_LightTimer.GetLimit() >= m_LightTimer.GetLimit())
					m_LightTimer.Reset();

			}


			m_MoveKey[k_i].color.alpha = 255;
		}

	}

	m_LightTimer.Update();

}
