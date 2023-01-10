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
	*  @brief      バックの中に登録
	* 
	* @param[in] bag_num バックの中身
	* @param[in] state　 武器のステータス
	*/
	void SetWeapon(int bag_num,WEAPON_STATE state);

	/*!
	*  @brief      バックの中に登録
	* 
	* @param[in] bag_num バックの中身
	* @param[in] id　     　　武器のID
	* @param[in] attack　 　　武器の攻撃力
	* @param[in] durability　 武器の耐久度
	*/
	void SetWeapon(int const bag_num,WEAPON_ID id, float attack,float durability);

	/*!
	*  @brief      バックの選択した枠番号を登録
	*
	* @param[in] bag_num バックの中身
	*/
	void SetSelectBagNumber(int select_bag_num);

	/*!
	*  @brief      預金残高の加減
	* 
	*  @param[in] add_money
	*/
	void AddToDepositBalance(int add_to_deposit_balance);

	// バックの容量
	int GetBagCapacity();   
	// バックの選択した枠番号
	int GetSelectBagNumber();
	// お金の預金残高取得
	int GetDepositBalance();
	// バックの開閉フラグ
	bool GetBagFlag();			
	// バックの中身の情報
	WEAPON_STATE GetWeaponData(int const bag_num);  

private:
	static const int m_max_item;             //! アイテムの最大数
	static const int m_bag_capacity;         //! バックの容量
	static const int m_max_deposit_balance;  //! 預金残高の上限
										     
	WEAPON_STATE* m_BagInventory;            //! バックの中身
										         
	bool m_BagFlag;					         //! バックのフラグ
	int  m_SelectBagNumber;                  //! バックの番号
										     
	int m_DepositBalance;                    //! 預金残高
};