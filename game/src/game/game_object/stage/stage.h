#pragma once
#include "aqua.h"
#include "stage_object/rock/object_rock.h"
#include "stage_object/tree/object_tree.h"
class CStage : public aqua::IGameObject
{
public:
	CStage(aqua::IGameObject* parent);
	~CStage() = default;

	void Initialize() override;
	void Update() override;
	void Finalize() override;

private:

	void CreateStageObject();
	void LodaStageMap();
	void SpaceAlgorithms();
	void AutoMapCreate();

private:
	aqua::CModel m_StageModel;

	static const int m_max_stage;
	static const int m_max_template_stage;
	static const int m_map_object_space;
	static const aqua::CPoint m_map_size;
	static const std::string m_stage_commn_name;

	std::vector<std::vector<int>> m_StageMap;
	aqua::CPoint  m_StageSize;
	int           m_StageObjectSize;
	aqua::CModel* m_RandStage;
	int m_StageNum;
};