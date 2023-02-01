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
	*  @brief �����̕ϓ�����
	*/
	void DepositFluctuation();

	/*
	*  @brief �a���c���v�Z
	*/
	void DepositBalanceCalculation();

private:
	static const std::string    m_money_box_name;
	static const int            m_font_size;
	static const float          m_easing_speed;
	static const aqua::CVector2 m_font_space;

	aqua::CSprite m_MoneyBoxSprite;      //! �a����
	aqua::CLabel  m_Deposit;             //! �a���c��
	aqua::CLabel  m_DepositFluctuation;  //! �a���ϓ�
	aqua::CTimer  m_EasingTimer;         //! �C�[�W���O����
	CBagData*     m_BagData;             //! �o�b�N�̃f�[�^
	int			  m_PrevDeposit;         //! �a���c���L�^
};