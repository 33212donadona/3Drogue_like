#include "input.h"

namespace key = aqua::keyboard;		//! �L�[�{�[�h
namespace mou = aqua::mouse;		//! �}�E�X
namespace con = aqua::controller;	//! �R���g���[��


/*�X�V*/

void Input::Updata()
{
	for (int i = 0; i < m_max_key; i++)
		m_PrevInputKey[i] = m_InputKey[i];

	m_InputKey[(int)KEY_ID::A] =
		key::Button(key::KEY_ID::RETURN) || 
		con::Button(con::DEVICE_ID::P1,con::BUTTON_ID::A);

	m_InputKey[(int)KEY_ID::B] =
		key::Button(key::KEY_ID::RETURN) ||
		con::Button(con::DEVICE_ID::P1, con::BUTTON_ID::B);

	m_InputKey[(int)KEY_ID::X] =
		key::Button(key::KEY_ID::RETURN) ||
		con::Button(con::DEVICE_ID::P1, con::BUTTON_ID::X);

	m_InputKey[(int)KEY_ID::Y] =
		key::Button(key::KEY_ID::RETURN) ||
		con::Button(con::DEVICE_ID::P1, con::BUTTON_ID::Y);

	m_InputKey[(int)KEY_ID::R] =
		key::Button(key::KEY_ID::RETURN) ||
		con::Button(con::DEVICE_ID::P1, con::BUTTON_ID::RIGHT_SHOULDER);

	m_InputKey[(int)KEY_ID::ZR] =
		key::Button(key::KEY_ID::RETURN) ||
		con::GetTriggerRight(con::DEVICE_ID::P1);

	m_InputKey[(int)KEY_ID::L] =
		key::Button(key::KEY_ID::RETURN) ||
		con::Button(con::DEVICE_ID::P1, con::BUTTON_ID::LEFT_SHOULDER);

	m_InputKey[(int)KEY_ID::ZL] =
		key::Button(key::KEY_ID::RETURN) ||
		con::GetTriggerLeft(con::DEVICE_ID::P1);

	m_LeftStick = con::GetAnalogStickLeft(con::DEVICE_ID::P1);
	m_RightStick = con::GetAnalogStickRight(con::DEVICE_ID::P1);
}

/*�����ꂽ���݂̂̏o��*/

bool Input::In(KEY_ID key_id)
{
	return m_InputKey[(int)key_id] && !m_PrevInputKey[(int)key_id];
}

/*�����ꂽ���݂̂̏o��*/

bool Input::Out(KEY_ID key_id)
{
	return !m_InputKey[(int)key_id] && m_PrevInputKey[(int)key_id];
}

/*���͒��̏o��*/

bool Input::Keep(KEY_ID key_id)
{
	return m_InputKey[(int)key_id];
}

/*��������*/

float Input::Horizotal(ANALOG_STICK_ID stick_id)
{
	int ded = 0;

	stick_id == ANALOG_STICK_ID::LEFT ?
		ded = m_LeftStick.x * 1000 :
		ded = m_RightStick.x * 1000;

	return ded / 1000.0f;
}

/*��������*/

float Input::Vertical(ANALOG_STICK_ID stick_id)
{
	int ded = 0;

	stick_id == ANALOG_STICK_ID::LEFT ?
		ded = m_LeftStick.y * 1000 :
		ded = m_RightStick.y * 1000;

	return ded / 1000.0f;
}
