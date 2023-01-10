#pragma once
#include "aqua.h"
#include "../weapon/weapon_id.h"

class CBagData : public aqua::IGameObject
{
public:

	CBagData(aqua::IGameObject* parent);
	~CBagData() = default;

	void Initialize() override;
	void Update() override;
	void Finalize() override;

	/*!
	*  @brief      �o�b�N�̒��ɓo�^
	* 
	* @param[in] bag_num �o�b�N�̒��g
	* @param[in] state�@ ����̃X�e�[�^�X
	*/
	void SetWeapon(int bag_num,WEAPON_STATE state);

	/*!
	*  @brief      �o�b�N�̒��ɓo�^
	* 
	* @param[in] bag_num �o�b�N�̒��g
	* @param[in] id�@     �@�@�����ID
	* @param[in] attack�@ �@�@����̍U����
	* @param[in] durability�@ ����̑ϋv�x
	*/
	void SetWeapon(int const bag_num,WEAPON_ID id, float attack,float durability);

	/*!
	*  @brief      �o�b�N�̑I�������g�ԍ���o�^
	*
	* @param[in] bag_num �o�b�N�̒��g
	*/
	void SetSelectBagNumber(int select_bag_num);

	/*!
	*  @brief      �a���c���̉���
	* 
	*  @param[in] add_money
	*/
	void AddToDepositBalance(int add_to_deposit_balance);

	// �o�b�N�̗e��
	int GetBagCapacity();   
	// �o�b�N�̑I�������g�ԍ�
	int GetSelectBagNumber();
	// �����̗a���c���擾
	int GetDepositBalance();
	// �o�b�N�̊J�t���O
	bool GetBagFlag();			
	// �o�b�N�̒��g�̏��
	WEAPON_STATE GetWeaponData(int const bag_num);  

private:
	static const int m_max_item;             //! �A�C�e���̍ő吔
	static const int m_bag_capacity;         //! �o�b�N�̗e��
	static const int m_max_deposit_balance;  //! �a���c���̏��
										     
	WEAPON_STATE* m_BagInventory;            //! �o�b�N�̒��g
										         
	bool m_BagFlag;					         //! �o�b�N�̃t���O
	int  m_SelectBagNumber;                  //! �o�b�N�̔ԍ�
										     
	int m_DepositBalance;                    //! �a���c��
};