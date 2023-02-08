#include "stage.h"
#include "stage_id.h"

const int CStage::m_max_stage = 2;
const int CStage::m_max_template_stage = 4;
const int CStage::m_map_object_space = 9;
const aqua::CPoint CStage::m_map_size = aqua::CPoint(22, 22);
const std::string CStage::m_stage_commn_name = "data\\stage\\template_stage_";

/*
 *  コンストラクタ
 */
CStage::CStage(aqua::IGameObject* parent)
	:aqua::IGameObject(parent, "Stage")
	, m_RandStage(nullptr)
{
}

/*
 *  初期化
 */
void CStage::Initialize()
{
	m_RandStage = AQUA_NEW aqua::CModel[m_max_stage];

	m_StageModel.Create("data\\stage\\stage_w", 0);
	m_StageModel.scale = aqua::CVector3::ONE * 10;

	m_StageModel.axis = aqua::CVector3(0.0f, 1.0f, 0.0f);

	m_StageNum = 0;

	CreateStageObject();
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
	IGameObject::Finalize();

	AQUA_SAFE_DELETE_ARRAY(m_RandStage);

	m_StageMap.clear();
	m_StageModel.Delete();
}

aqua::CVector3 CStage::GetArePosition(aqua::CPoint stage_data)
{
	aqua::CPoint area = stage_data;

	area.x = aqua::Limit(area.x, 0, m_StageSize.x - 1);
	area.y = aqua::Limit(area.y, 0, m_StageSize.y - 1);

	if (m_StageMap[area.y][area.x] != 0)return aqua::CVector3::ZERO;

	aqua::CVector3 pos(area.x, 0, area.y);
	pos -= aqua::CVector3(m_StageSize.x / 2, 0, m_StageSize.y / 2);
	pos = pos * (float)m_StageObjectSize;
	pos.y = 5.0f;

	return pos;
}

bool CStage::CheckObject(aqua::CVector3 position)
{
	aqua::CPoint area;

	area.x = (int)(position.x / m_StageObjectSize + m_StageSize.x / 2);
	area.y = (int)(position.z / m_StageObjectSize + m_StageSize.y / 2);

	area.x = aqua::Limit(area.x, 0, m_StageSize.x - 1);
	area.y = aqua::Limit(area.y, 0, m_StageSize.y - 1);

	return m_StageMap[area.y][area.x] != 0;
}

/*
 *  ステージ生成
 */
void CStage::CreateStageObject()
{
	//if (aqua::Rand(true, false))
	//	LodaStageMap();
	//else
		AutoMapCreate();

	aqua::CPoint stage_half_size = m_StageSize;
	stage_half_size.x = stage_half_size.x / 2;
	stage_half_size.y = stage_half_size.y / 2;

	// オブジェクトの設置
	for (int i = 0; i < m_StageSize.y; ++i)
	{
		for (int j = 0; j < m_StageSize.x; ++j)
		{
			if (m_StageMap[i][j] != (int)STAGE_OBJECT::ARE)
			{
				aqua::CVector3 pos;
				pos = (aqua::CVector3(j, 0, i) - aqua::CVector3(stage_half_size.x, 0, stage_half_size.y)) * (float)m_StageObjectSize;
				pos.y = 5.0f;

				if (m_StageMap[i][j] == (int)STAGE_OBJECT::ROCK)
					aqua::CreateGameObject<CObjectRock>(this)->Initialize(pos);
				if (m_StageMap[i][j] == (int)STAGE_OBJECT::TREE)
					aqua::CreateGameObject<CObjectTree>(this)->Initialize(pos);
				if (m_StageMap[i][j] == (int)STAGE_OBJECT::TOWER)
					aqua::CreateGameObject<CObjectTower>(this)->Initialize(pos);
			}
		}
	}
}

/*
*   ステージマップの読み込み
*/
void CStage::LodaStageMap()
{
	aqua::CCSVLoader m_TemplateStage;
	int num = aqua::Rand(m_max_template_stage, 0);

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

/*
*   ステージマップの空間アルゴリズム
*/
void CStage::SpaceAlgorithms()
{
	aqua::CPoint map;
	aqua::CPoint map_reference;

	//穴掘り法の初期位置
	do
	{
		//　乱数
		map.x = aqua::Rand(m_StageSize.x - 1, 0);
		map.y = aqua::Rand(m_StageSize.y - 1, 0);

		map_reference = map;

		// 参照した情報
		if (m_StageMap[map.y][map.x] == 0)
		{
			// 左右
			for (int i = -1; i <= 1; i += 2)
			{
				map_reference.x = map.x + i;

				if (map_reference.x > 0 && map_reference.x < m_StageSize.x)
					if (m_StageMap[map.y][map_reference.x] == 1)
						break;

				map_reference.x = map.x;
			}
			// 左右になかったら次
			if (map.x == map_reference.x)
			{// 上下
				for (int j = -1; j <= 1; j += 2)
				{
					map_reference.y = map.y + j;

					if (map_reference.y > 0 && map_reference.y < m_StageSize.y)
						if (m_StageMap[map_reference.y][map.x] == 1)
							break;

					map_reference.y = map.y;
				}
			}
		}
	} while (map == map_reference);

	m_StageMap[map_reference.y][map_reference.x] = 2;

	// ステージに空間を作る


}

/*
*  マップ自動生成
*/
void CStage::AutoMapCreate()
{
	// ステージマップをオブジェクトで埋める
	m_StageMap.assign(m_map_size.y, std::vector<int>(m_map_size.x, (int)STAGE_OBJECT::ROCK));

	if (m_StageObjectSize != m_map_object_space)
		m_StageObjectSize = m_map_object_space;

	if (m_StageSize.x != m_map_size.x)
		m_StageSize.x = m_map_size.x;

	if (m_StageSize.y != m_map_size.y)
		m_StageSize.y = m_map_size.y;


	MapPartition(aqua::CPoint(0, 0), m_StageSize, aqua::Rand(10, 3));

	int vector_size = (int)m_FirstPosition.size();

	// マップに道を作る
	for (int i = 1; i < vector_size; i++)
	{
		int back = i - 1;

		if (m_FirstPosition[back].x < m_FirstPosition[i].x)
		{
			for (int x = m_FirstPosition[back].x; x <= m_FirstPosition[i].x; x++)
			{
				if (m_StageMap[m_FirstPosition[back].y][x] != (int)STAGE_OBJECT::ARE)
					m_StageMap[m_FirstPosition[back].y][x] = (int)STAGE_OBJECT::ARE;
			}
		}
		else
		{
			for (int x = m_FirstPosition[i].x; x <= m_FirstPosition[back].x; x++)
			{
				if (m_StageMap[m_FirstPosition[i].y][x] != (int)STAGE_OBJECT::ARE)
					m_StageMap[m_FirstPosition[i].y][x] = (int)STAGE_OBJECT::ARE;
			}
		}

		if (m_FirstPosition[back].y < m_FirstPosition[i].y)
		{
			for (int y = m_FirstPosition[back].y; y <= m_FirstPosition[i].y + 1; y++)
			{
				if (m_StageMap[y][m_FirstPosition[back].x] != (int)STAGE_OBJECT::ARE)
					m_StageMap[y][m_FirstPosition[back].x] = (int)STAGE_OBJECT::ARE;
			}
		}
		else
		{
			for (int y = m_FirstPosition[i].y; y <= m_FirstPosition[back].y + 1; y++)
			{
				if (m_StageMap[y][m_FirstPosition[i].x] != (int)STAGE_OBJECT::ARE)
					m_StageMap[y][m_FirstPosition[i].x] = (int)STAGE_OBJECT::ARE;
			}
		}
	}
}

void CStage::MapPartition(aqua::CPoint stage_size_first, aqua::CPoint stage_size_end, int max_partition)
{
	if (max_partition <= 0)return;

	aqua::CPoint s = stage_size_end - stage_size_first;
	if (s.x < 5 || s.y < 5)return;

	bool width_flag = aqua::Rand(1, 0);

	// 始点
	aqua::CPoint first = stage_size_first;
	// 終点
	aqua::CPoint end2 = stage_size_end;

	// 横に分割
	if (width_flag)
	{
		first.y = aqua::Rand(stage_size_end.y / 4, 0) + stage_size_end.y / 2;
		end2.y = first.y - 1;
	}
	// 縦に分割
	else
	{
		first.x = aqua::Rand(stage_size_end.x / 4, 0) + stage_size_end.x / 2;
		end2.x = first.x - 1;
	}


	for (int y = first.y; y < stage_size_end.y; y++)
		for (int x = first.x; x < stage_size_end.x; x++)
			m_StageMap[y][x] = (int)STAGE_OBJECT::ROCK;

	aqua::CPoint rand = aqua::CPoint(aqua::Rand(2, 1), aqua::Rand(2, 1));

	for (int y = first.y + rand.y; y < stage_size_end.y - rand.y; y++)
		for (int x = first.x + rand.x; x < stage_size_end.x - rand.x; x++)
			m_StageMap[y][x] = (int)STAGE_OBJECT::ARE;

	m_FirstPosition.push_back(first + rand);


	MapPartition(first, stage_size_end, max_partition - 1);
	MapPartition(stage_size_first, end2, max_partition - 1);
}