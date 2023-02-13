#pragma once

#include "../../scene_manager.h"

class CResult : public IScene
{
public: // ���J�����o�֐�

	// �R���X�g���N�^
	CResult(IGameObject* parent);

	// �f�X�g���N�^
	~CResult(void) = default;

	// �������֐�
	void Initialize(void)	override;

	// �X�V�֐�
	void Update(void)	override;

	// �`��֐�
	void Draw(void)	override;

	// ����֐�
	void Finalize(void)	override;

private: // ����J�����o�֐�

	// �X�R�A�{�[�h�X�v���C�g
	aqua::CSprite m_ScoreBoardSprite;

	// �w�i�X�v���C�g
	aqua::CSprite m_BackGround;

	// �g�X�v���C�g�i�P���ځj
	aqua::CSprite m_FrameFirst;

	// �g�X�v���C�g�i�Q���ځj
	aqua::CSprite m_FrameSecond;

	// �����_���X�v���C�g
	aqua::CSprite m_MedalSprite;

	// �⃁�_���X�v���C�g
	aqua::CSprite m_SilverMedalSprite;

	// �����_���X�v���C�g
	aqua::CSprite m_GoldMedalSprite;

	// �X�R�A���[�^�[�X�v���C�g
	aqua::CSprite m_ScoreMeter;

	// �C�[�W���O�^�C�}�[
	aqua::CTimer m_EasingTimer;

private: // ����J�����o�萔

	static const aqua::CVector2 m_medal_position;

	//////////////////////////////////////////////////////////////
	aqua::CLabel m_ClearTimeText;
	aqua::CLabel m_EasyNumText;
	aqua::CLabel m_NormalNumText;
	aqua::CLabel m_HardText;
	aqua::CLabel m_TotalScoreText;

	float m_ClearTime;


	POINT mouse;
	int X;
	int Y;
};