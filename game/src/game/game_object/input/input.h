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
	*  @brief �X�V
	*/
	void Updata();

	/*
	*  @brief   �����ꂽ���݂̂̏o��
	*
	*  @param[in]   key_id   ���͏��
	*
	*  @return     ���͏��
	* 
	*  @retval     true    �����ꂽ
	*  @retval     false   ������Ă��Ȃ�
	*/
	bool In(KEY_ID key_id);
	/*
	*  @brief   �����ꂽ���݂̂̏o��
	*
	*  @param[in]   key_id   ���͏��
	*
	*  @return     ���͏��
	* 
	*  @retval     true    �����ꂽ
	*  @retval     false   ������Ă��Ȃ�
	*/
	bool Out(KEY_ID key_id);
	/*
	*  @brief   ���͒��̏o��
	*
	*  @param[in]   key_id   ���͏��
	*
	*  @return     ���͏��
	*
	*  @retval     true    �����ꂽ
	*  @retval     false   ������Ă��Ȃ�
	*/
	bool Button(KEY_ID key_id);

	/*
	*  @brief   ��������
	*
	*  @param[in]   stick_id   ���͏��
	* 
	*  @return     ���͏��
	*/
	float Horizotal(ANALOG_STICK_ID stick_id = ANALOG_STICK_ID::LEFT);

	/*
	*  @brief   ��������
	*
	*  @param[in]   stick_id   ���͏��
	* 
	*  @return     ���͏��
	*/
	float Vertical(ANALOG_STICK_ID stick_id = ANALOG_STICK_ID::LEFT);

	static const int m_max_key = (int)KEY_ID::MAX;
	static bool m_InputKey[m_max_key];
	static bool m_PrevInputKey[m_max_key];
	static aqua::CVector2 m_LeftStick;
	static aqua::CVector2 m_RightStick;
}