#include "title.h"
#include "../../../sound_manager/game_sound_manager.h"
CTitle::CTitle(aqua::IGameObject* parent)
// parent(scene_manager)
	: IScene(parent, "Title")
{
}

void CTitle::Initialize(void)
{
	

	m_SoundManager = (CGameSoundManager*)aqua::FindGameObject("GameSoundManager");
	m_SoundManager->Play(SoundID::TITLE_BGM);
	m_TitleSprite.Create("data\\title_graph\\title.png");
	m_TitleSprite.color.alpha = 0;
	m_TitleSprite.ApplyGaussFilter(32, 1000);
	m_TitleSprite.position = { (float)aqua::GetWindowWidth() / 2 - m_TitleSprite.GetTextureWidth() / 2,(float)aqua::GetWindowHeight() / 2 - m_TitleSprite.GetTextureHeight() + 150 };

	m_TitleSpriteAdd.Create("data\\title_graph\\title_add.png");
	m_TitleSprite.blend_mode = aqua::ALPHABLEND::ADD;
	m_TitleSpriteAdd.position = m_TitleSprite.position;
	m_TitleSpriteAdd.color.alpha = 0;

	m_PushMassage.Create("data\\title_graph\\push_z.png");
	m_PushMassage.position = { (float)aqua::GetWindowWidth() / 2 - m_PushMassage.GetTextureWidth() / 2,(float)aqua::GetWindowHeight() - m_PushMassage.GetTextureHeight() - 150 };
	m_PushMassage.blend_mode = aqua::ALPHABLEND::ADD;
	m_PushMassage.ApplyGaussFilter(32, 200);
	m_PushMassage.color.alpha = 0;

	m_CinemaSpriteUp.Create("data\\title_graph\\cinema.png");
	m_CinemaSpriteUp.position.y = -(float)(m_CinemaSpriteUp.GetTextureHeight());

	m_CinemaSpriteUpSecond.Create("data\\title_graph\\cinema.png");
	m_CinemaSpriteUpSecond.position.x = (float)m_CinemaSpriteUpSecond.GetTextureWidth();

	m_CinemaSpriteDown.Create("data\\title_graph\\cinema.png");
	m_CinemaSpriteDown.position.y = (float)aqua::GetWindowHeight();

	m_CinemaSpriteDownSecond.Create("data\\title_graph\\cinema.png");
	m_CinemaSpriteDownSecond.position.x = -((float)m_CinemaSpriteDownSecond.GetTextureWidth());
	m_CinemaSpriteDownSecond.position.y = (float)aqua::GetWindowHeight() - m_CinemaSpriteDownSecond.GetTextureHeight();

	m_WhiteSprite.Create("data\\title_graph\\white.png");
	m_WhiteSprite.color.alpha = 0;

	///////////////////////////////////////////////////////////////////

	m_DesignBox.Create("data\\title_graph\\design.png");
	m_DesignBox.ApplyGaussFilter(32, 100);
	m_DesignBox.color.alpha = 0;
	m_DesignBox.anchor = { m_DesignBox.GetTextureWidth() / 2,m_DesignBox.GetTextureHeight() / 2 };
	m_DesignBox.position = { (float)aqua::GetWindowWidth() / 2 - m_DesignBox.GetTextureWidth() / 2,(float)aqua::GetWindowHeight() / 2 - m_DesignBox.GetTextureHeight() / 2 };

	m_DesignBoxUp.Create("data\\title_graph\\design_up.png");
	m_DesignBoxUp.ApplyGaussFilter(32, 100);
	m_DesignBoxUp.color.alpha = 0;
	m_DesignBoxUp.position = { (float)aqua::GetWindowWidth() / 2 - m_DesignBox.GetTextureWidth() / 2,(float)aqua::GetWindowHeight() / 2 - m_DesignBox.GetTextureHeight() / 2 };

	m_DesignBoxDown.Create("data\\title_graph\\design_down.png");
	m_DesignBoxDown.ApplyGaussFilter(32, 100);
	m_DesignBoxDown.color.alpha = 0;
	m_DesignBoxDown.position = { (float)aqua::GetWindowWidth() / 2 - m_DesignBox.GetTextureWidth() / 2,(float)aqua::GetWindowHeight() / 2 - m_DesignBox.GetTextureHeight() / 2 };

	m_TeamNameSpeite.Create("data\\title_graph\\kawagishi_games.png");
	m_TeamNameSpeite.color.alpha = 0;
	m_TeamNameSpeite.anchor = { m_TeamNameSpeite.GetTextureWidth() / 2,m_TeamNameSpeite.GetTextureHeight() / 2 };
	m_TeamNameSpeite.position = { (float)aqua::GetWindowWidth() / 2 - m_TeamNameSpeite.GetTextureWidth() / 2,700.0f };

	m_TitleStartTimer.Setup(4.0f);
	m_EasingTimer.Setup(3.0f);
}

void CTitle::Update(void)
{
	// スペースでゲームシーンへ移動
	if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::L))
	{
		((CSceneManager*)aqua::FindGameObject("SceneManager"))->ChangeScene(SCENE_ID::RESULT);
	}

	if (!m_TitleStartTimer.Finished())
	{
		m_DesignBox.color.alpha++;
		m_DesignBoxUp.color.alpha++;
		m_DesignBoxDown.color.alpha++;

		if (!(m_TeamNameSpeite.color.alpha >= 250))
			m_TeamNameSpeite.color.alpha += 2;
		m_TitleStartTimer.Update();
		return;
	}

	// イージングタイマー
	if (!m_EasingTimer.Finished())
	{
		m_EasingTimer.Update();
	}

	// イージング処理
	{
		m_CinemaSpriteUp.position.y = aqua::easing::OutQuintic(m_EasingTimer.GetTime(), m_EasingTimer.GetLimit(), -((float)m_CinemaSpriteUp.GetTextureHeight()), 0);
		m_CinemaSpriteDown.position.y = aqua::easing::OutQuintic(m_EasingTimer.GetTime(), m_EasingTimer.GetLimit(), (float)aqua::GetWindowHeight(), float(aqua::GetWindowHeight() - m_CinemaSpriteDown.GetTextureHeight()));
	}

	//////////////////////////////////////////////////////////////////////////////////// 

	m_DesignBoxUp.position.y = aqua::easing::OutQuintic(m_EasingTimer.GetTime(), m_EasingTimer.GetLimit(), aqua::GetWindowHeight() / 2.0f - m_DesignBoxUp.GetTextureHeight() / 2.0f, aqua::GetWindowHeight() / 2 - 15.0f);
	m_DesignBoxDown.position.y = aqua::easing::OutQuintic(m_EasingTimer.GetTime(), m_EasingTimer.GetLimit(),(float)aqua::GetWindowHeight() / 2 - m_DesignBoxUp.GetTextureHeight() / 2, aqua::GetWindowHeight() / 2 + m_DesignBoxDown.GetTextureHeight() / 3 - 100.0f);
	m_DesignBox.color.alpha = (unsigned char)aqua::easing::OutQuintic(m_EasingTimer.GetTime(), m_EasingTimer.GetLimit(), 255, 0);
	m_DesignBox.scale.x = aqua::easing::OutQuintic(m_EasingTimer.GetTime(), m_EasingTimer.GetLimit(), 1, 0);
	m_DesignBoxUp.color.alpha = (unsigned char)aqua::easing::OutQuintic(m_EasingTimer.GetTime(), m_EasingTimer.GetLimit(), 255, 0);
	m_DesignBoxDown.color.alpha = (unsigned char)aqua::easing::OutQuintic(m_EasingTimer.GetTime(), m_EasingTimer.GetLimit(), 255, 0);

	if (m_EasingTimer.GetTime() >= 0.25f)
	{
		if (m_WhiteSprite.color.alpha != 255)
		{
			m_TeamNameSpeite.color.alpha -= 4;
			m_WhiteSprite.color.alpha += 5;
			if (!(m_TeamNameSpeite.scale.x <= 0))
			{
				m_TeamNameSpeite.color.alpha --;
				m_TeamNameSpeite.scale -= {0.022f, 0.022f};
			}
			else if (m_TeamNameSpeite.scale.x <= 0.01)
			{
				m_TeamNameSpeite.color.alpha = 0;
				m_TeamNameSpeite.scale = { 0.0f,0.0f };
			}
		}
	}

	/// ////////////////////////////////////////////////////////////////////////////////

	if (m_TitleSprite.color.alpha != 255&&m_EasingTimer.Finished())
	{
		m_TitleSprite.color.alpha++;
	}
	if(m_EasingTimer.Finished())
		m_PushMassage.color.alpha+=2;

	m_CinemaSpriteUp.position.x -= 5.0f;
	m_CinemaSpriteUpSecond.position.x -= 5.0f;
	m_CinemaSpriteDown.position.x += 5.0f;
	m_CinemaSpriteDownSecond.position.x += 5.0f;


	// スペースでゲームシーンへ移動
	if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::SPACE))
	{
		((CSceneManager*)aqua::FindGameObject("SceneManager"))->ChangeScene(SCENE_ID::SELECT);
	}
}

void CTitle::Draw(void)
{
	IScene::Draw();

	m_DesignBox.Draw();
	m_DesignBoxUp.Draw();
	m_DesignBoxDown.Draw();
	m_TeamNameSpeite.Draw();
	m_WhiteSprite.Draw();
	m_PushMassage.Draw();

	m_TitleSprite.Draw();
}

void CTitle::Finalize(void)
{
	m_SoundManager->Stop(SoundID::TITLE_BGM);
	m_TitleSprite.Delete();

	m_CinemaSpriteUp.Delete();
	m_CinemaSpriteDown.Delete();
}
