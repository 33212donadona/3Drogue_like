#pragma once
#include "aqua.h"

namespace Input
{

	enum class KEY_ID
	{
		A,
		B,
		X,
		Y,

		R,
		ZR,
		L,
		ZL,

		MAX
	};

	enum class STICK_BUTTON_ID
	{
		UP,
		DOWN,
		LEFT,
		RIGHT,

		MAX
	};

	enum class ANALOG_STICK_ID
	{
		LEFT,
		RIGHT,

		MAX
	};

	/*
	*  @brief 更新
	*/
	void Updata();

	/*
	*  @brief   押された時のみの出力
	*
	*  @param[in]   key_id   入力情報
	*
	*  @return     入力状態
	* 
	*  @retval     true    離された
	*  @retval     false   離されていない
	*/
	bool In(KEY_ID key_id);
	/*
	*  @brief   離された時のみの出力
	*
	*  @param[in]   key_id   入力情報
	*
	*  @return     入力状態
	* 
	*  @retval     true    離された
	*  @retval     false   離されていない
	*/
	bool Out(KEY_ID key_id);
	/*
	*  @brief   入力中の出力
	*
	*  @param[in]   key_id   入力情報
	*
	*  @return     入力状態
	*
	*  @retval     true    離された
	*  @retval     false   離されていない
	*/
	bool Button(KEY_ID key_id);

	/*
	*  @brief   水平入力
	*
	*  @param[in]   stick_id   入力情報
	* 
	*  @return     入力状態
	*/
	float Horizotal(ANALOG_STICK_ID stick_id = ANALOG_STICK_ID::LEFT);

	/*
	*  @brief   垂直入力
	*
	*  @param[in]   stick_id   入力情報
	* 
	*  @return     入力状態
	*/
	float Vertical(ANALOG_STICK_ID stick_id = ANALOG_STICK_ID::LEFT);

	static const int m_max_key = (int)KEY_ID::MAX;
	static bool m_InputKey[m_max_key];
	static bool m_PrevInputKey[m_max_key];
	static aqua::CVector2 m_LeftStick;
	static aqua::CVector2 m_RightStick;
}