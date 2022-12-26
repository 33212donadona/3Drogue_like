#include "stage.h"

CStage::CStage(aqua::IGameObject* parent)
	:aqua::IGameObject(parent,"Stage")
{
}

void CStage::Initialize()
{
	m_StageModel.Create("data\\stage\\stage_w",0);
	m_StageModel.scale = aqua::CVector3::ONE * 10;

	m_StageModel.axis = aqua::CVector3(1.0f, 0.0f, 0.0f);
	m_StageModel.angles.x = aqua::DegToRad(90.0f);
}

void CStage::Update()
{
}

void CStage::Finalize()
{
	m_StageModel.Delete();
}
