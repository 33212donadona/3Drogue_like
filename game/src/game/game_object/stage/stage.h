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
private:
	aqua::CModel m_StageModel;
};