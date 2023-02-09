#include "select_system.h"
#include "../../../../common_data/common_data.h"
#include "../../../../input/input.h"

const aqua::CVector2 CSelectSystem::m_object_space = { 50.0f,35.0f };
const int CSelectSystem::m_max_animetion = 3;
const float CSelectSystem::m_max_easing_time = 2.0f;

CSelectSystem::CSelectSystem(IGameObject* parent)
	:aqua::IGameObject(parent, "SelectSystem")
	, m_SelsectLevel(0)
	, m_PrevSelsectLevel(0)
{
}

void CSelectSystem::Initialize()
{
	m_CommonData = (CCommonData*)aqua::FindGameObject("CommonData");
	m_CountModel = m_CommonData->GetSelectMaxCreaTarget();
	m_SelectModel = AQUA_NEW aqua::CModel[m_CountModel];

	for (int m_i = 0; m_i < m_CountModel; m_i++)
	{
		m_SelectModel[m_i].Create("data\\model\\select\\magic_stone pedestal", 0);
		m_SelectModel[m_i].axis.y = 1.0f;
		m_SelectModel[m_i].scale = aqua::CVector3::ONE * 0.1f;
		m_SelectModel[m_i].position.x = (m_i - int(m_CountModel / 2) + m_SelsectLevel - 1) * m_object_space.x;
		m_SelectModel[m_i].position.z = (m_i % 2 - 1) * m_object_space.y;
	}

	m_SelectPointer.Create("data\\model\\Bot", m_max_animetion);
	m_SelectPointer.axis.y = 1.0f;
	m_SelectPointer.angles = aqua::DegToRad(180);
	m_SelectPointer.scale = aqua::CVector3::ONE * 0.1f;
	m_SelectPointer.position = m_SelectModel[m_SelsectLevel].position;
	m_SelectPointer.position.y += 1.0f;
	m_SelectPointer.AttachAnimation(2);

	m_EasingTimer.Setup(m_max_easing_time);
}

void CSelectSystem::Update()
{
	if(m_SelsectLevel == m_PrevSelsectLevel)
	{
		m_SelsectLevel += Input::In(Input::BUTTON_ID::ZR) - Input::In(Input::BUTTON_ID::ZL);
		m_SelsectLevel += (int)Input::Horizotal();
		m_SelsectLevel = aqua::Limit(m_SelsectLevel, 0, 2);
	}

	if (!m_EasingTimer.Finished() && m_PrevSelsectLevel != m_SelsectLevel)
	{
		if (m_EasingTimer.Finished())
			m_EasingTimer.SetTime(m_max_easing_time);

		m_SelectPointer.position.x = aqua::easing::OutBack
		(
			m_EasingTimer.GetTime(),
			m_EasingTimer.GetLimit(),
			m_SelectModel[2 - m_PrevSelsectLevel].position.x,
			m_SelectModel[2 - m_SelsectLevel].position.x
		);

		m_SelectPointer.position.z = aqua::easing::OutBack
		(
			m_EasingTimer.GetTime(),
			m_EasingTimer.GetLimit(),
			m_SelectModel[2 - m_PrevSelsectLevel].position.z,
			m_SelectModel[2 - m_SelsectLevel].position.z
		);

		m_EasingTimer.Update();
	}
	else
	{
		m_PrevSelsectLevel = m_SelsectLevel;
		m_EasingTimer.Reset();
	}

	m_SelectPointer.AnimationUpdata();
}

void CSelectSystem::Finalize()
{
	for (int m_i = 0; m_i < m_CountModel; m_i++)
		m_SelectModel[m_i].Delete();

	AQUA_SAFE_DELETE_ARRAY(m_SelectModel);

	m_SelectPointer.Delete();
}

bool CSelectSystem::GetDecisionSelsectLavel()
{
	bool sl = Input::In(Input::BUTTON_ID::B);

	if (sl)
	{
		CommonDataInfo cd = m_CommonData->GetData();
		cd.crea_target = (m_SelsectLevel + 1) * 10;
		m_CommonData->SetData(cd);
	}

	return sl;
}

int CSelectSystem::GetNowLavel()
{
	return m_SelsectLevel;
}

int CSelectSystem::GetPrevLavel()
{
	return m_PrevSelsectLevel;
}

aqua::CVector3 CSelectSystem::GetTargetPosition()
{
	return m_SelectPointer.position;
}
