#include "stage.h"

const int CStage::m_max_stage = 2;
const int CStage::m_max_template_stage = 4;
const std::string CStage::m_stage_commn_name = "data\\stage\\template_stage_";

/*
 *  �R���X�g���N�^
 */
CStage::CStage(aqua::IGameObject* parent)
	:aqua::IGameObject(parent, "Stage")
	, m_RandStage(nullptr)
{
}
/*
 *  ������
 */
void CStage::Initialize()
{
	m_RandStage = AQUA_NEW aqua::CModel[m_max_stage];

	m_StageModel.Create("data\\stage\\stage_w", 0);
	m_StageModel.scale = aqua::CVector3::ONE * 10;

	m_StageModel.axis = aqua::CVector3(1.0f, 0.0f, 0.0f);
	m_StageModel.angles = aqua::DegToRad(90.0f);

	m_StageNum = 0;

	CreateStageObject();
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
	IGameObject::Finalize();

	AQUA_SAFE_DELETE_ARRAY(m_RandStage);

	m_StageMap.clear();
	m_StageModel.Delete();
}

/*
 *  �X�e�[�W����
 */
void CStage::CreateStageObject()
{
	LodaStage();

	aqua::CPoint stage_half_size = m_StageSize;
	stage_half_size.x = stage_half_size.x / 2;
	stage_half_size.y = stage_half_size.y / 2;

	aqua::CPoint map;
	aqua::CPoint map_reference;

	do //���@��@�̏����ʒu
	{
		map.x = aqua::Rand(m_StageSize.x - 1, 0);
		map.y = aqua::Rand(m_StageSize.y - 1, 0);

		if (m_StageMap[map.y][map.x] != 0)break;

		for (int i = -1; i <= 1; i += 2)
		{
			map_reference.x = map.x + i;
			if (map_reference.x < 0 || map_reference.x > m_StageSize.x)break;
			if (m_StageMap[map.y][map_reference.x] == 1)
			{
				map.x = map_reference.x;
				break;
			}
			else
				map_reference.x = map.x;
		}
		if (map.x != map_reference.x)
		{
			for (int j = -1; j <= 1; j += 2)
			{
				map_reference.y = map.y + j;
				if (map_reference.y < 0 || map_reference.y > m_StageSize.y)break;
				if (m_StageMap[map_reference.y][map.x] == 1)
				{
					map.y = map_reference.y;
					break;
				}
				else
					map_reference.y = map.y;
			}
		}
	} while (map != map_reference);

	m_StageMap[map.y][map.x] = 0;

	for (int i = 0; i < m_StageSize.y; ++i)
		for (int j = 0; j < m_StageSize.x; ++j)
			if (m_StageMap[i][j] == 1)
			{
				aqua::CVector3 pos;
				pos = aqua::CVector3(j, 0, i) - aqua::CVector3(stage_half_size.x, 0, stage_half_size.y);
				pos = pos * (float)m_StageObjectSize;
				pos.y = 5;

				aqua::CreateGameObject<IObject>(this)->Initialize(pos);
			}
}

void CStage::LodaStage()
{
	aqua::CCSVLoader m_TemplateStage;
	int num = 1;//aqua::Rand(m_max_template_stage, 0);

	m_TemplateStage.Load(m_stage_commn_name + std::to_string(num) + ".csv");

	m_StageMap.clear();

	if (m_StageObjectSize != m_TemplateStage.GetInteger(0, 0))
		m_StageObjectSize = m_TemplateStage.GetInteger(0, 0);

	if (m_StageSize.x != m_TemplateStage.GetInteger(1, 0))
		m_StageSize.x = m_TemplateStage.GetInteger(1, 0);

	if (m_StageSize.y != m_TemplateStage.GetInteger(2, 0))
		m_StageSize.y = m_TemplateStage.GetInteger(2, 0);


	std::vector<int> c;
	for (int rows = 0; rows < m_StageSize.y; rows++)
	{
		for (int cols = m_StageSize.x - 1; cols >= 0; cols--)
		{
			int map_data = m_TemplateStage.GetInteger(rows + 3, cols);

			c.push_back(map_data);
		}

		m_StageMap.push_back(c);
		c.clear();
	}

	m_TemplateStage.Unload();
}