#include "bag.h"
#include "bag_data.h"
#include "../weapon_manager/weapon/weapon_id.h"

const int CBag::m_max_item = 3;
const int CBag::m_flash_speed = 3;
const int CBag::m_back_ground_alpha = 200;
const float CBag::m_scale_time = 0.5f;
const float CBag::m_scale_bag_sprite = 2.0f;
const float CBag::m_bag_sprite_space = 100.0f;
const std::string CBag::m_file_name[] =
{
	"data\\game_graph\\sword.png",
	"data\\game_graph\\magic.png",
	"data\\game_graph\\money.png"
};

/*
 *  �R���X�g���N�^
 */
CBag::CBag(aqua::IGameObject* parent)
	:aqua::IGameObject(parent, "Bag")
	, m_SelectTime(0)
	, m_SelectNumber(-1)
	, m_BagCapacity(1)
	, m_KeybordFlag(false)
{
}
/*
 *  ������
 */
void CBag::Initialize()
{
	m_BagData = (CBagData*)aqua::FindGameObject("BagData");

	if (m_BagData)
		m_BagCapacity = m_BagData->GetBagCapacity();

	std::vector<aqua::CSprite> vs;

	for (int item_i = 0; item_i < m_max_item; ++item_i)
	{
		aqua::CSprite s;

		s.Create(m_file_name[item_i]);

		vs.push_back(s);
	}

	m_ItemSprite.assign(m_BagCapacity, vs);

	m_BagSprite = AQUA_NEW aqua::CSprite[m_BagCapacity];
	m_ItemData  = AQUA_NEW WEAPON_STATE[m_BagCapacity];

	aqua::CVector2 center = aqua::GetWindowSize() / 2;

	for (int i = 0; i < m_BagCapacity; ++i)
	{

		m_BagSprite[i].Create("data\\game_graph\\�C���x���g��.png");

		m_BagSprite[i].scale = aqua::CVector2::ONE * m_scale_bag_sprite;

		m_BagSprite[i].anchor = aqua::CVector2(m_BagSprite[i].GetTextureWidth(), m_BagSprite[i].GetTextureHeight()) / 2.0f;

		m_BagSprite[i].position = center - m_BagSprite[i].anchor;
		m_BagSprite[i].position.x -= (m_BagSprite[i].GetTextureWidth() / 2 + m_bag_sprite_space * (i - 1)) * m_scale_bag_sprite;

		for (int item_j = 0; item_j < m_max_item; ++item_j)
		{
			m_ItemSprite[i][item_j].position = m_BagSprite[i].position;
			m_ItemSprite[i][item_j].anchor = m_BagSprite[i].anchor;
		}
	}

	m_BackGraund.Setup(aqua::CVector2::ZERO, (float)aqua::GetWindowWidth(), (float)aqua::GetWindowHeight());
	m_BackGraund.color = aqua::CColor::BLACK;
	m_BackGraund.color.alpha = m_back_ground_alpha;

	m_BagSpriteSize.x = m_BagSprite[0].GetTextureWidth() * m_scale_bag_sprite;
	m_BagSpriteSize.y = m_BagSprite[0].GetTextureHeight() * m_scale_bag_sprite;

	m_SelectBox.Setup(m_BagSprite[0].position, m_BagSpriteSize.x, m_BagSpriteSize.y);
	m_SelectBox.color = aqua::CColor::YELLOW;
	m_SelectBox.color.alpha = 0;

	m_EsingTime.Setup(m_scale_time);
}
/*
 *  �X�V
 */
void CBag::Update()
{
	SelectInventory();

	for (int i = 0; i < m_BagCapacity; ++i)
		m_ItemData[i] = m_BagData->GetWeaponData(i);

	for (int item_i = 0; item_i < m_BagCapacity; ++item_i)
		for (int item_j = 0; item_j < m_max_item; ++item_j)
			m_ItemSprite[item_i][item_j].scale = m_BagSprite[item_i].scale;
}
/*
 *  �`��
 */
void CBag::Draw()
{
	if (m_BagData && m_BagData->GetBagFlag())
	{
		m_BackGraund.Draw();

		for (int i = 0; i < m_BagCapacity; ++i)
		{
			int item_id = aqua::Limit((int)m_ItemData[i].id - 1, 0, 2);

			m_BagSprite[i].Draw();

			if ((int)m_ItemData[i].id != 0)
				m_ItemSprite[i][item_id].Draw();
		}
		m_SelectBox.Draw();
	}
}
/*
 *  ���
 */
void CBag::Finalize()
{
	for (int i = 0; i < m_BagCapacity; ++i)
		for (int item_j = 0; item_j < m_max_item; ++item_j)
			m_ItemSprite[i][item_j].Delete();

	for (int i = 0; i < m_BagCapacity; ++i)
		m_BagSprite[i].Delete();

	AQUA_SAFE_DELETE_ARRAY(m_ItemData);
	AQUA_SAFE_DELETE_ARRAY(m_BagSprite);
	m_BagData = nullptr;
	m_ItemSprite.clear();;
}

/*
 *  �o�b�N�̒��g��I��
 */
void CBag::SelectInventory()
{

	if (aqua::keyboard::Button(aqua::keyboard::KEY_ID::LEFT) || aqua::keyboard::Button(aqua::keyboard::KEY_ID::RIGHT))
		m_KeybordFlag = true;
	if (aqua::mouse::GetCursorMovement().x || aqua::mouse::GetCursorMovement().y)
		m_KeybordFlag = false;

	SelectNumber();

	if (m_SelectNumber != -1)
	{
		m_SelectTime = (m_SelectTime + m_flash_speed) % 180;
		m_SelectBox.color.alpha = (unsigned char)aqua::easing::InOutQuintic(sin(aqua::DegToRad((float)m_SelectTime)), 1.0f, 0.0f, 100.0f);

		for (int i = 1; i < m_BagCapacity; ++i)
			m_BagSprite[(i + m_SelectNumber) % m_BagCapacity].scale = aqua::CVector2::ONE * m_scale_bag_sprite;

		ScaleInventoryScale(m_SelectNumber);
	}

	if (m_SelectNumber == -1 || aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::LEFT) || aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::RIGHT))
	{
		m_SelectBox.color.alpha = 0;
		m_SelectTime = 0;
		m_EsingTime.Reset();

		for (int i = 0; i < m_BagCapacity; ++i)
			m_BagSprite[i].scale = aqua::CVector2::ONE * m_scale_bag_sprite;
	}
}
/*
 *  �I�𒆂̃o�b�N�̘g�ԍ�����
 */
void CBag::SelectNumber()
{
	if (m_KeybordFlag)
		m_SelectNumber = m_BagData->GetSelectBagNumber();
	else
	{
		aqua::CVector2 mouse = aqua::mouse::GetCursorPos();

		for (int i = 0; i < m_BagCapacity; ++i)
		{
			if (m_BagSprite[i].position.x - m_BagSprite[i].anchor.x< mouse.x &&
				m_BagSprite[i].position.y - m_BagSprite[i].anchor.y< mouse.y &&
				m_BagSprite[i].position.x + m_BagSprite[i].GetTextureWidth() * m_BagSprite[i].scale.x - m_BagSprite[i].anchor.x > mouse.x &&
				m_BagSprite[i].position.y + m_BagSprite[i].GetTextureHeight() * m_BagSprite[i].scale.y - m_BagSprite[i].anchor.y > mouse.y)
			{
				m_SelectNumber = i;
				m_BagData->SetSelectBagNumber(i);
				break;
			}
			else
				m_SelectNumber = -1;
		}
	}
}
/*
 *  �I�����Ɋg��
 */
void CBag::ScaleInventoryScale(int bag_num)
{
	if (m_EsingTime.Finished())m_EsingTime.SetTime(m_EsingTime.GetLimit());

	m_EsingScale = aqua::easing::OutBounce(m_EsingTime.GetTime(), m_EsingTime.GetLimit(), 1.0f, 1.125f);
	float bag_scale = 1.0f + m_EsingScale;

	m_BagSprite[bag_num].scale = aqua::CVector2(bag_scale, bag_scale);
	m_SelectBox.position = m_BagSprite[bag_num].position - m_BagSprite[bag_num].anchor * m_EsingScale;

	m_SelectBox.width = m_BagSprite[bag_num].GetTextureWidth() * m_BagSprite[bag_num].scale.x;
	m_SelectBox.height = m_BagSprite[bag_num].GetTextureHeight() * m_BagSprite[bag_num].scale.y;

	m_EsingTime.Update();
}