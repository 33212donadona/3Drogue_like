#include "aqua.h"

class CBagData;

class CMoneyManager : public aqua::IGameObject
{
public:

	CMoneyManager(aqua::IGameObject* parent);
	~CMoneyManager() = default;

	void Initialize() override;
	void Update() override;
	void Draw()override;
	void Finalize() override;

private:
	/*
	*  @brief お金の変動処理
	*/
	void DepositFluctuation();

	/*
	*  @brief 預金残高計算
	*/
	void DepositBalanceCalculation();

private:
	static const std::string    m_money_box_name;
	static const int            m_font_size;
	static const float          m_easing_speed;
	static const aqua::CVector2 m_font_space;

	aqua::CSprite m_MoneyBoxSprite;      //! 預金欄
	aqua::CLabel  m_Deposit;             //! 預金残高
	aqua::CLabel  m_DepositFluctuation;  //! 預金変動
	aqua::CTimer  m_EasingTimer;         //! イージング時間
	CBagData*     m_BagData;             //! バックのデータ
	int			  m_PrevDeposit;         //! 預金残高記録
};