#include "select_system.h"
#include "../../../../common_data/common_data.h"

const aqua::CVector2 CSelectSystem::m_object_space = { 50.0f,35.0f };
const int CSelectSystem::m_max_animetion = 3;
CSelectSystem::CSelectSystem(IGameObject* parent)
	:aqua::IGameObject(parent, "SelectSystem")
{
}

void CSelectSystem::Initialize()
{
	m_CommonData = (CCommonData*)aqua::FindGameObject("CommonData");
	int count_model = m_CommonData->GetData().selct_max_mode;
	m_SelectModel = AQUA_NEW aqua::CModel[count_model];

	for (int m_i = 0; m_i < count_model; m_i++)
	{
		m_SelectModel[m_i].Create("data\\model\\select\\magic_stone pedestal", 0);
		m_SelectModel[m_i].axis.y = 1.0f;
		m_SelectModel[m_i].scale = aqua::CVector3::ONE * 0.1f;
		m_SelectModel[m_i].position.x = (m_i - int(count_model / 2)) * m_object_space.x;
		m_SelectModel[m_i].position.z = (m_i % 2 - 1) * m_object_space.y;
	}

	m_SelectPointer.Create("data\\model\\Bot", m_max_animetion);
	m_SelectPointer.axis.y = 1.0f;
	m_SelectPointer.angles = aqua::DegToRad(180);
	m_SelectPointer.scale = aqua::CVector3::ONE * 0.1f;
	m_SelectPointer.position.y += 1.0f;
	m_SelectPointer.AttachAnimation(2);
}

void CSelectSystem::Update()
{

	m_SelectPointer.AnimationUpdata();
}

void CSelectSystem::Finalize()
{
	int count_model = m_CommonData->GetData().selct_max_mode;
	for (int m_i = 0; m_i < count_model; m_i++)
		m_SelectModel[m_i].Delete();

	AQUA_SAFE_DELETE_ARRAY(m_SelectModel);

	m_SelectPointer.Delete();
}
