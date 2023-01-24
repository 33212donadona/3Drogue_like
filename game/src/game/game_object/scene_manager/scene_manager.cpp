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
	// 最初のシーンを設定（タイトルシーン）
	aqua::CreateGameObject<CCommonData>(this);
	aqua::CreateGameObject<CGameSoundManager>(this);

	m_NextScene = SCENE_ID::TITLE;

}

void CSceneManager::Update(void)
{
	Input::Updata();
	// 生成したシーンの更新処理を行う
	IGameObject::Update();

	// シーンを切り替える必要がなければ以降の処理を行わない
	if (m_NextScene == SCENE_ID::DUMMY)
		return;

	// シーンが存在している場合は以下の処理を行う
	if (m_CurrentScene_P)
	{
		// 現在のシーンの解放処理を行う
		m_CurrentScene_P->Finalize();
		// 現在のシーンを削除する（子リストから外す）
		m_ChildObjectList.erase(std::find(m_ChildObjectList.begin(), m_ChildObjectList.end(), m_CurrentScene_P));
		// ポインタの破棄＆NULL化
		AQUA_SAFE_DELETE(m_CurrentScene_P)
	}

	// シーンの生成とシーンの初期化を行う
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

	// シーンを生成したらDUMMYに戻す
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