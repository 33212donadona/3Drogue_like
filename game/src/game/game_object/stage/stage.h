#pragma once
#include "aqua.h"
class CStage : public aqua::IGameObject
{
public:
	CStage(aqua::IGameObject* parent);
	~CStage() = default;

	void Initialize() override;
	void Update() override;
	void Finalize() override;

	void CreateStage();
private:
	aqua::CModel m_StageModel;

	static const int m_max_stage;
	aqua::CModel* m_RandStage;
	int m_StageNum;
};