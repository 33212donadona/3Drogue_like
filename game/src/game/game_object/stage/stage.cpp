#include "stage.h"

const int CStage::m_max_stage = 2;

/*
 *  �R���X�g���N�^
 */
CStage::CStage(aqua::IGameObject* parent)
	:aqua::IGameObject(parent,"Stage")
{
}
/*
 *  ������
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
 *  �X�V
 */
void CStage::Update()
{
}
/*
 *  ���
 */
void CStage::Finalize()
{
	AQUA_SAFE_DELETE_ARRAY(m_RandStage);

	m_StageModel.Delete();
}
/*
 *  �X�e�[�W����
 */
void CStage::CreateStage()
{
	m_StageNum = (m_StageNum + 1) % 2;




}