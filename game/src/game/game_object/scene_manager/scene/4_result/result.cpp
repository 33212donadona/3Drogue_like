#include "result.h"

#include "../../../sound_manager/game_sound_manager.h"
#include "../../../common_data/common_data.h"

CResult::CResult(IGameObject* parent)
	: IScene(parent, "Result")
{
}

void CResult::Initialize(void)
{
	// �X�R�A�{�[�h�̃X�v���C�g����
	m_ScoreBoardSprite.Create("data/result/score_board.png");

	// �X�R�A�{�[�h�̏����ʒu��ݒ�
	m_ScoreBoardSprite.position.x = -1000;

	// �w�i�X�v���C�g�̐���
	m_BackGround.Create("data/result/bg.png");

	// �g�X�v���C�g�̐����i�P���ځj
	m_FrameFirst.Create("data/result/frame.png");
	// �g�X�v���C�g�̐����i�Q���ځj
	m_FrameSecond.Create("data/result/frame.png");

	// �w�i�X�v���C�g�i�Q���ځj���i�P���ځj�̉E�ɔz�u
	m_FrameSecond.position.x = (float)aqua::GetWindowWidth();

	// �C�[�W���O�^�C�}�[�̐ݒ�
	m_EasingTimer.Setup(0.5f);


	/////////////////////////////////////////////////////////////////////////////
	m_Label.Create(50);
	m_Label.position.x = 600;
	m_Label.position.y = 290;
	m_Label.color.alpha = 0;
	m_ClearTime = ((CCommonData*)aqua::FindGameObject("CommonData"))->GetData().game_crea_time;
	m_Label.text = std::to_string(m_ClearTime);
}

void CResult::Update(void)
{
	// �u�X�y�[�X�v�L�[�������ƃ^�C�g���V�[���֑J�ڂ���
	if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::SPACE))
		((CSceneManager*)aqua::FindGameObject("SceneManager"))->ChangeScene(SCENE_ID::TITLE);

	// �^�C�}�[���I�����Ă��Ȃ���΁A�^�C�}�[���X�V��������
	if (!m_EasingTimer.Finished()) m_EasingTimer.Update();
	// �^�C�}�[���I�����Ă���ꍇ�A���l��_�ł�����
	else m_Label.color.alpha += 5;

	// �X�R�A�{�[�h�̃A�j���[�V��������
	m_ScoreBoardSprite.position.x = aqua::easing::InCubic(m_EasingTimer.GetTime(), m_EasingTimer.GetLimit(), -1000, 0);

	// �w�i�������ֈړ������鏈��
	m_FrameFirst.position.x--;
	m_FrameSecond.position.x--;

	// �w�i�i�P���ځj�̈ʒu�������ֈړ����Č����Ȃ��Ȃ�����E�[�֖߂�
	if (m_FrameFirst.position.x <= -(float)aqua::GetWindowWidth())
		m_FrameFirst.position.x = (float)aqua::GetWindowWidth();

	// �w�i�i�Q���ځj�̈ʒu�������ֈړ����Č����Ȃ��Ȃ�����E�[�֖߂�
	else if (m_FrameSecond.position.x <= -(float)aqua::GetWindowWidth())
		m_FrameSecond.position.x = (float)aqua::GetWindowWidth();
}

void CResult::Draw(void)
{
	m_BackGround.Draw();
	m_FrameFirst.Draw();
	m_FrameSecond.Draw();
	m_ScoreBoardSprite.Draw();

	m_Label.Draw();
}

void CResult::Finalize(void)
{
	m_ScoreBoardSprite.Delete();
	m_FrameSecond.Delete();
	m_FrameFirst.Delete();
	m_BackGround.Draw();
}
