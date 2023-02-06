#include "bag_data.h"
#include "../weapon_manager/weapon/weapon_id.h"
#include "../input/input.h"

const int CBagData::m_max_item = 2;
const int CBagData::m_bag_capacity = 3;
const int CBagData::m_max_deposit_balance = 99999;

namespace KEY = aqua::keyboard;

/*
 *  �R���X�g���N�^
 */
CBagData::CBagData(aqua::IGameObject* parent)
	: aqua::IGameObject(parent,"BagData")
	, m_BagFlag(false)
	, m_SelectBagNumber(0)
	, m_DepositBalance(0)
{
}

/*
 *  ������
 */
void CBagData::Initialize()
{
	m_BagInventory = AQUA_NEW WEAPON_STATE[m_bag_capacity];
}

/*
 *  �X�V
 */
void CBagData::Update()
{
	if (Input::In(Input::KEY_ID::Y))
		m_BagFlag = !m_BagFlag;

	if (m_BagFlag)
	{
		m_SelectBagNumber += KEY::Trigger(KEY::KEY_ID::LEFT) - KEY::Trigger(KEY::KEY_ID::RIGHT);
		
		if (m_SelectBagNumber < 0)
			m_SelectBagNumber = 2;

		m_SelectBagNumber = m_SelectBagNumber % m_bag_capacity;
	}
	
}

/*
 *  ���
 */
void CBagData::Finalize()
{
	AQUA_SAFE_DELETE_ARRAY(m_BagInventory);
}

/*
 *  ����o�^
 */
void CBagData::SetWeapon(int bag_num,WEAPON_STATE state)
{
	int num = aqua::Limit(bag_num, 0, m_bag_capacity - 1);

	WEAPON_STATE ws = state;

	ws.id = WEAPON_ID((int)state.id % (int)WEAPON_ID::MONEY);

	m_BagInventory[num] = state;
}

/*
 *  ����o�^
 */
void CBagData::SetWeapon(int const bag_num, WEAPON_ID id, float attack, float durability)
{
	WEAPON_STATE w;

	w.id = WEAPON_ID((int)id % (int)WEAPON_ID::MONEY);
	w.attack = attack;
	w.durability = durability;

	SetWeapon(bag_num, w);
}

/*
 *  �I�𒆂̘g�ԍ���o�^
 */
void CBagData::SetSelectBagNumber(int select_bag_num)
{
	int sbn = aqua::Limit(select_bag_num, 0, m_bag_capacity - 1);

	m_SelectBagNumber = sbn;
}

/*
*   �a���c���̉���
*/
void CBagData::AddToDepositBalance(int add_to_deposit_balance)
{
	m_DepositBalance = aqua::Limit(m_DepositBalance + add_to_deposit_balance, 0, m_max_deposit_balance);
}

/*
 *  �o�b�N�̍ő�e��
 */
int CBagData::GetBagCapacity()
{
	return m_bag_capacity;
}

/*
 *  �I�𒆂̘g�ԍ��̎擾
 */
int CBagData::GetSelectBagNumber()
{
	return m_SelectBagNumber;
}

/*
*   �����̗a���c���擾
*/
int CBagData::GetDepositBalance()
{
	return m_DepositBalance;
}

/*
 *  �o�b�N�̊J�t���O
 */
bool CBagData::GetBagFlag()
{
	return m_BagFlag;
}

/*
 *  ����̏��擾
 */
WEAPON_STATE CBagData::GetWeaponData(int const select_bag_num)
{
	int sbn = aqua::Limit(select_bag_num, 0, m_bag_capacity - 1);

	return m_BagInventory[sbn];
}