#include "select_back_ground.h"
#include "../scene_manager/scene/2_select/select_system/select_system.h"
const int CSelectBackGround::m_max_sky = 2;
const int CSelectBackGround::m_max_effect = 2;
const float CSelectBackGround::m_sprite_move_speed = 7.5f;
const std::string CSelectBackGround::m_filr_name[] =
{
	"data\\select_graph\\sub.png",
	"data\\select_graph\\medium.png",
	"data\\select_graph\\high.png"
};

CSelectBackGround::CSelectBackGround(aqua::IGameObject* parent)
	:aqua::IGameObject(parent, "SelectBackGround")
	, m_EffectRota(0.0f)
	, m_SelectSystem(nullptr)
	, m_AlphaReta(255)
{
}

void CSelectBackGround::Initialize()
{
	std::vector<aqua::CSprite> vs;

	for (int sky_j = 0; sky_j < (int)LAVEL_BG::MAX; sky_j++)
	{
		aqua::CSprite s;

		s.Create(m_filr_name[sky_j]);

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

	m_BackGroundSurface.Create(aqua::GetWindowWidth(), aqua::GetWindowHeight());
}

void CSelectBackGround::Update()
{
	if (!m_SelectSystem)
		m_SelectSystem = (CSelectSystem*)aqua::FindGameObject("SelectSystem");

	ChangeBackGournd();

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

	m_BackGroundSurface.End();
}

void CSelectBackGround::Finalize()
{
	for (int sky_i = 0; sky_i < m_max_sky; sky_i++)
		for (int sky_j = 0; sky_j < (int)LAVEL_BG::MAX; sky_j++)
			m_ScrollSkySprite[sky_i][sky_j].Delete();

	for (int efc_i = 0; efc_i < m_max_effect; efc_i++)
		m_EffectSprite[efc_i].Delete();

	m_ScrollSkySprite.clear();

	AQUA_SAFE_DELETE_ARRAY(m_EffectSprite);

}

aqua::CSurface& CSelectBackGround::GetBackGround()
{
	return m_BackGroundSurface;
}

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
