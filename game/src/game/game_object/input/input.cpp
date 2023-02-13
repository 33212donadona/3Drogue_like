#include "input.h"

namespace key = aqua::keyboard;		//! キーボード
namespace mou = aqua::mouse;		//! マウス
namespace con = aqua::controller;	//! コントローラ


/*更新*/

void Input::Updata()
{
	for (int i = 0; i < m_max_key; i++)
		m_PrevInputKey[i] = m_InputKey[i];

	m_InputKey[(int)BUTTON_ID::A] =
		key::Button(key::KEY_ID::V) ||
		con::Button(con::DEVICE_ID::P1, con::BUTTON_ID::A);

	m_InputKey[(int)BUTTON_ID::B] =
		mou::Button(mou::BUTTON_ID::LEFT) ||
		con::Button(con::DEVICE_ID::P1, con::BUTTON_ID::B);

	m_InputKey[(int)BUTTON_ID::X] =
		key::Button(key::KEY_ID::C) ||
		con::Button(con::DEVICE_ID::P1, con::BUTTON_ID::X);

	m_InputKey[(int)BUTTON_ID::Y] =
		mou::Button(mou::BUTTON_ID::RIGHT) ||
		con::Button(con::DEVICE_ID::P1, con::BUTTON_ID::Y);

	m_InputKey[(int)BUTTON_ID::R] =
		key::Button(key::KEY_ID::RIGHT) ||
		con::Button(con::DEVICE_ID::P1, con::BUTTON_ID::RIGHT_SHOULDER);

	m_InputKey[(int)BUTTON_ID::ZR] =
		key::Button(key::KEY_ID::A) ||
		con::GetTriggerRight(con::DEVICE_ID::P1);

	m_InputKey[(int)BUTTON_ID::L] =
		key::Button(key::KEY_ID::LEFT) ||
		con::Button(con::DEVICE_ID::P1, con::BUTTON_ID::LEFT_SHOULDER);

	m_InputKey[(int)BUTTON_ID::ZL] =
		key::Button(key::KEY_ID::D) ||
		con::GetTriggerLeft(con::DEVICE_ID::P1);

	m_LeftStick.x = float(key::Button(key::KEY_ID::D) - key::Button(key::KEY_ID::A));
	m_LeftStick.y = float(key::Button(key::KEY_ID::S) - key::Button(key::KEY_ID::W));

	if (con::GetAnalogStickLeft(con::DEVICE_ID::P1).x || con::GetAnalogStickLeft(con::DEVICE_ID::P1).y)
	{
		m_LeftStick = con::GetAnalogStickLeft(con::DEVICE_ID::P1);
	}
	
	if (
		con::Button(con::DEVICE_ID::P1, con::BUTTON_ID::RIGHT) ||
		con::Button(con::DEVICE_ID::P1, con::BUTTON_ID::LEFT)  ||
		con::Button(con::DEVICE_ID::P1, con::BUTTON_ID::UP)    ||
		con::Button(con::DEVICE_ID::P1, con::BUTTON_ID::DOWN))
	{
		m_LeftStick.x = 
			con::Button(con::DEVICE_ID::P1, con::BUTTON_ID::RIGHT) -
			con::Button(con::DEVICE_ID::P1, con::BUTTON_ID::LEFT);
		m_LeftStick.y = 
			con::Button(con::DEVICE_ID::P1, con::BUTTON_ID::UP) -
			con::Button(con::DEVICE_ID::P1, con::BUTTON_ID::DOWN);
	}

	m_LeftStick.x = aqua::Limit(m_LeftStick.x,-1.0f, 1.0f);

	if (key::Button(key::KEY_ID::LSHIFT))
	{
		if (key::Button(key::KEY_ID::A) || key::Button(key::KEY_ID::D) || key::Button(key::KEY_ID::W) || key::Button(key::KEY_ID::S))
		{
			m_RightStick.x = float(key::Button(key::KEY_ID::D) - key::Button(key::KEY_ID::A));
			m_RightStick.y = float(key::Button(key::KEY_ID::S) - key::Button(key::KEY_ID::W));
		}
	}
	else if (con::GetAnalogStickRight(con::DEVICE_ID::P1).x || con::GetAnalogStickRight(con::DEVICE_ID::P1).y)
		m_RightStick = con::GetAnalogStickRight(con::DEVICE_ID::P1);
}

/*押された時のみの出力*/

bool Input::In(BUTTON_ID key_id)
{
	return m_InputKey[(int)key_id] && !m_PrevInputKey[(int)key_id];
}

/*離された時のみの出力*/

bool Input::Out(BUTTON_ID key_id)
{
	return !m_InputKey[(int)key_id] && m_PrevInputKey[(int)key_id];
}

/*入力中の出力*/

bool Input::Button(BUTTON_ID key_id)
{
	return m_InputKey[(int)key_id];
}

/*水平入力*/

float Input::Horizotal(ANALOG_STICK_ID stick_id)
{
	int ded = 0;

	stick_id == ANALOG_STICK_ID::LEFT ?
		ded = int(m_LeftStick.x * 10.0f) :
		ded = int(m_RightStick.x * 10.0f);



	return ded / 10.0f;
}

/*垂直入力*/

float Input::Vertical(ANALOG_STICK_ID stick_id)
{
	int ded = 0;

	stick_id == ANALOG_STICK_ID::LEFT ?
		ded = int(m_LeftStick.y * 10.0f) :
		ded = int(m_RightStick.y * 10.0f);

	return ded / 10.0f;
}
