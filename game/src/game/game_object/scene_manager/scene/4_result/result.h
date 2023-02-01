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

	// �C�[�W���O�^�C�}�[
	aqua::CTimer m_EasingTimer;

	//////////////////////////////////////////////////////////////
	aqua::CLabel m_Label;
	float m_ClearTime;
};