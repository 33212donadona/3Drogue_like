#include "scene_manager.h"
#include "../sound_manager/game_sound_manager.h"
#include "scene/1_title/title.h"
#include "scene/2_select/select.h"
#include "scene/3_game_main/game_main.h"
#include "scene/4_result/result.h"
#include "../common_data/common_data.h"
#include "../input/input.h"

CSceneManager::CSceneManager(aqua::IGameObject* parent)
	: aqua::IGameObject(parent, "SceneManager")
	, m_CurrentScene_P(nullptr)
	, m_NextScene(SCENE_ID::DUMMY)
{
}

void CSceneManager::Initialize(void)
{
	// �ŏ��̃V�[����ݒ�i�^�C�g���V�[���j
	aqua::CreateGameObject<CCommonData>(this);
	aqua::CreateGameObject<CGameSoundManager>(this);

	m_NextScene = SCENE_ID::TITLE;

}

void CSceneManager::Update(void)
{
	Input::Updata();
	// ���������V�[���̍X�V�������s��
	IGameObject::Update();

	// �V�[����؂�ւ���K�v���Ȃ���Έȍ~�̏������s��Ȃ�
	if (m_NextScene == SCENE_ID::DUMMY)
		return;

	// �V�[�������݂��Ă���ꍇ�͈ȉ��̏������s��
	if (m_CurrentScene_P)
	{
		// ���݂̃V�[���̉���������s��
		m_CurrentScene_P->Finalize();
		// ���݂̃V�[�����폜����i�q���X�g����O���j
		m_ChildObjectList.erase(std::find(m_ChildObjectList.begin(), m_ChildObjectList.end(), m_CurrentScene_P));
		// �|�C���^�̔j����NULL��
		AQUA_SAFE_DELETE(m_CurrentScene_P)
	}

	// �V�[���̐����ƃV�[���̏��������s��
	switch (m_NextScene)
	{
	case SCENE_ID::TITLE:		m_CurrentScene_P = aqua::CreateGameObject<CTitle>(this);
		IGameObject::Initialize(); break;
	case SCENE_ID::SELECT:		m_CurrentScene_P = aqua::CreateGameObject<CSelect>(this);
		IGameObject::Initialize(); break;
	case SCENE_ID::GAMEMAIN:	m_CurrentScene_P = aqua::CreateGameObject<CGameMain>(this);
		IGameObject::Initialize(); break;
	case SCENE_ID::RESULT:		m_CurrentScene_P = aqua::CreateGameObject<CResult>(this);
		IGameObject::Initialize(); break;
	}

	// �V�[���𐶐�������DUMMY�ɖ߂�
	m_NextScene = SCENE_ID::DUMMY;
}

void CSceneManager::Draw(void)
{
	IGameObject::Draw();
}

void CSceneManager::Finalize(void)
{
	IGameObject::Finalize();
}

void CSceneManager::ChangeScene(SCENE_ID id)
{
	m_NextScene = id;
}