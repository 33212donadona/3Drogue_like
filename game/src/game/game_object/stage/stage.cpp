#include "stage.h"

const int CStage::m_max_stage = 2;

/*
 *  コンストラクタ
 */
CStage::CStage(aqua::IGameObject* parent)
	:aqua::IGameObject(parent,"Stage")
{
}
/*
 *  初期化
 */
void CStage::Initialize()
{
	m_RandStage = AQUA_NEW aqua::CModel[m_max_stage];

	m_StageModel.Create("data\\stage\\stage_w",0);
	m_StageModel.scale = aqua::CVector3::ONE * 10;

	m_StageModel.axis = aqua::CVector3(1.0f, 0.0f, 0.0f);
	m_StageModel.angles.x = aqua::DegToRad(90.0f);

	m_StageNum = 0;
	CreateStage();
}
/*
 *  更新
 */
void CStage::Update()
{
}
/*
 *  解放
 */
void CStage::Finalize()
{
	AQUA_SAFE_DELETE_ARRAY(m_RandStage);

	m_StageModel.Delete();
}
/*
 *  ステージ生成
 */
void CStage::CreateStage()
{
	m_StageNum = (m_StageNum + 1) % 2;




}