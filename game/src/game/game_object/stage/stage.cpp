#include "stage.h"

const int CStage::m_max_stage = 2;
const int CStage::m_max_template_stage = 5;
const std::string CStage::m_stage_commn_name = "data\\stage\\template_stage_";

/*
 *  コンストラクタ
 */
CStage::CStage(aqua::IGameObject* parent)
	:aqua::IGameObject(parent,"Stage")
	, m_RandStage(nullptr)
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
void CStage::CreateStageObject()
{

}

void CStage::LodaStage()
{
	m_TemplateStage.Unload();
	m_TemplateStage.Load(m_stage_commn_name + std::to_string(aqua::Rand(m_max_template_stage, 0)) + ".csv");

	int col = m_TemplateStage.GetInteger(0,1);
	int row = m_TemplateStage.GetInteger(0,2);

	for (int i = 0; i < row; ++i)
		for (int j = 0; j < col; ++j)
			m_StageMap[i][j] = m_TemplateStage.GetInteger(i, j);


}
