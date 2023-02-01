#include "coin_manager.h"
#include "../bag/bag_data.h"

const std::string CCoinManager::m_money_box_name = "data\\game_graph\\マネーバー.png";
const int CCoinManager::m_font_size = 100;
const float CCoinManager::m_easing_speed = 2.5f;
const aqua::CVector2 CCoinManager::m_font_space = aqua::CVector2(25, 75);

/*
 *  コンストラクタ
 */
CCoinManager::CCoinManager(aqua::IGameObject* parent)
	:aqua::IGameObject(parent, "CoinManager")
	, m_PrevDeposit(0)
{
}

/*
 *  初期化
 */
void CCoinManager::Initialize()
{
	m_BagData = (CBagData*)aqua::FindGameObject("BagData");
	m_MoneyBoxSprite.Create(m_money_box_name);
	m_MoneyBoxSprite.position.x = float(aqua::GetWindowWidth() - m_MoneyBoxSprite.GetTextureWidth());

	m_Deposit.Create(m_font_size);
	m_Deposit.text = std::to_string(m_BagData->GetDepositBalance());
	m_Deposit.position.x = float(aqua::GetWindowWidth() - m_MoneyBoxSprite.GetTextureWidth() / 10 - m_Deposit.GetTextWidth());
	m_Deposit.position.y = float(m_MoneyBoxSprite.GetTextureHeight() - m_Deposit.GetFontHeight()) / 2.0f;

	m_DepositFluctuation.Create(m_font_size / 3 * 2);
	m_DepositFluctuation.text = "0";
	m_DepositFluctuation.position.x = m_Deposit.position.x - m_font_space.x - m_DepositFluctuation.GetTextWidth();
	m_DepositFluctuation.position.y = m_Deposit.position.y + m_font_space.y;
	m_DepositFluctuation.color.alpha = 0;

	m_EasingTimer.Setup(m_easing_speed);
	m_EasingTimer.SetTime(m_easing_speed);
}

/*
 *  更新
 */
void CCoinManager::Update()
{
	DepositFluctuation();

	DepositBalanceCalculation();

	if (aqua::keyboard::Button(aqua::keyboard::KEY_ID::J) && m_BagData)
		m_BagData->AddToDepositBalance(100);

	if (aqua::keyboard::Button(aqua::keyboard::KEY_ID::K) && m_BagData)
		m_BagData->AddToDepositBalance(-100);
}

/*
 *  描画
 */
void CCoinManager::Draw()
{
	m_MoneyBoxSprite.Draw();
	m_Deposit.Draw();
	m_DepositFluctuation.Draw();
}

/*
 *  解放
 */
void CCoinManager::Finalize()
{
	m_MoneyBoxSprite.Delete();
	m_Deposit.Delete();
	m_DepositFluctuation.Delete();
	m_BagData = nullptr;
}

/*
*   預金残高計算
*/
void CCoinManager::DepositFluctuation()
{
	if (m_PrevDeposit == m_BagData->GetDepositBalance() && !m_BagData)return;

	std::string sign;
	int d = m_BagData->GetDepositBalance() - m_PrevDeposit;

	if (d < 0)sign = "－ ";
	else sign = "＋ ";

	m_DepositFluctuation.text = sign + std::to_string(std::abs(d));
	m_DepositFluctuation.position.x = m_Deposit.position.x - m_font_space.x - m_DepositFluctuation.GetTextWidth();
	m_DepositFluctuation.position.y = m_Deposit.position.y + m_font_space.y;

	if (m_EasingTimer.Finished())m_EasingTimer.SetTime(m_EasingTimer.GetLimit());

	m_DepositFluctuation.position.y =
		aqua::easing::OutBounce
		(
			m_EasingTimer.GetTime(),
			m_EasingTimer.GetLimit(),
			m_Deposit.position.y + m_font_space.y,
			m_Deposit.position.y - m_font_space.y / 2.0f
		);

	m_DepositFluctuation.color.alpha =
		(unsigned char)aqua::easing::InCubic
		(
			m_EasingTimer.GetTime(),
			m_EasingTimer.GetLimit(),
			255,
			0
		);

	m_EasingTimer.Update();
}

/*
*   預金残高計算
*/
void CCoinManager::DepositBalanceCalculation()
{
	m_Deposit.text = std::to_string(m_BagData->GetDepositBalance());
	m_Deposit.position.x = float(aqua::GetWindowWidth() - m_MoneyBoxSprite.GetTextureWidth() / 10 - m_Deposit.GetTextWidth());
	m_Deposit.position.y = float(m_MoneyBoxSprite.GetTextureHeight() - m_Deposit.GetFontHeight()) / 2.0f;

	if (m_EasingTimer.Finished())
	{
		m_EasingTimer.Reset();
		m_PrevDeposit = m_BagData->GetDepositBalance();
	}
}