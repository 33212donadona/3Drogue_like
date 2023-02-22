#include "sword.h"
#include "../../../sound_manager/game_sound_manager.h"

const std::string m_file_pass = "data\\model\\weapon\\sword";

CSword::CSword(aqua::IGameObject* parent)
	:IWeapon(parent,"Sword")
{
}
/*
* 初期化
*/
void CSword::Initialize()
{
	m_SwordModel.Create("data\\model\\weapon\\sword",0);
	m_SwordModel.axis.y = 1.0f;
	m_SwordModel.position.y -= 100.0f;
	m_SoundManager = (CGameSoundManager*)aqua::FindGameObject("GameSoundManager");
}
/*
* 更新
*/
void CSword::Update()
{
	m_SwordModel.axis.y = 0.0f;
}
/*
* 解放
*/
void CSword::Finalize()
{
	m_SwordModel.Delete();
}
/*
* 衝突判定
*/
bool CSword::CheckHit(aqua::CVector3 first_pos, aqua::CVector3 end_pos)
{
	return m_SwordModel.GetBoneCapsuleCollision("Collision.000", first_pos, end_pos, 3).HitFlag ||
		m_SwordModel.GetBoneCapsuleCollision("Collision.001", first_pos, end_pos, 3).HitFlag;;
}
/*
* モデルにプレイヤーの手の行列を設定
*/
void CSword::SetMatrix(aqua::CMatrix matrix)
{
	m_SwordModel.SetMatrix(matrix);
}
