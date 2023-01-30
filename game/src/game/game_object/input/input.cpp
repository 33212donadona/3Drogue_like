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
		mou::Button(mou::BUTTON_ID::RIGHT) ||
		con::Button(con::DEVICE_ID::P1, con::BUTTON_ID::A);

	m_InputKey[(int)KEY_ID::B] =
		mou::Button(mou::BUTTON_ID::LEFT) ||
		con::Button(con::DEVICE_ID::P1, con::BUTTON_ID::B);

	m_InputKey[(int)KEY_ID::X] =
		key::Button(key::KEY_ID::C) ||
		con::Button(con::DEVICE_ID::P1, con::BUTTON_ID::X);

	m_InputKey[(int)KEY_ID::Y] =
		key::Button(key::KEY_ID::V) ||
		con::Button(con::DEVICE_ID::P1, con::BUTTON_ID::Y);

	m_InputKey[(int)KEY_ID::R] =
		key::Button(key::KEY_ID::RIGHT) ||
		con::Button(con::DEVICE_ID::P1, con::BUTTON_ID::RIGHT_SHOULDER);

	m_InputKey[(int)KEY_ID::ZR] =
		key::Button(key::KEY_ID::A) ||
		con::GetTriggerRight(con::DEVICE_ID::P1);

	m_InputKey[(int)KEY_ID::L] =
		key::Button(key::KEY_ID::LEFT) ||
		con::Button(con::DEVICE_ID::P1, con::BUTTON_ID::LEFT_SHOULDER);

	m_InputKey[(int)KEY_ID::ZL] =
		key::Button(key::KEY_ID::D) ||
		con::GetTriggerLeft(con::DEVICE_ID::P1);

		m_LeftStick.x = float(key::Button(key::KEY_ID::D) - key::Button(key::KEY_ID::A));
		m_LeftStick.y = float(key::Button(key::KEY_ID::S) - key::Button(key::KEY_ID::W));
	//if (key::Button(key::KEY_ID::A) || key::Button(key::KEY_ID::D) || key::Button(key::KEY_ID::W) || key::Button(key::KEY_ID::S))
	//{
	//}
	if (con::GetAnalogStickLeft(con::DEVICE_ID::P1).x || con::GetAnalogStickLeft(con::DEVICE_ID::P1).y)
		m_LeftStick = con::GetAnalogStickLeft(con::DEVICE_ID::P1);


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

bool Input::Button(KEY_ID key_id)
{
	return m_InputKey[(int)key_id];
}

/*��������*/

float Input::Horizotal(ANALOG_STICK_ID stick_id)
{
	int ded = 0;

	stick_id == ANALOG_STICK_ID::LEFT ?
		ded = m_LeftStick.x * 10 :
		ded = m_RightStick.x * 10;



	return ded / 10.0f;
}

/*��������*/

float Input::Vertical(ANALOG_STICK_ID stick_id)
{
	int ded = 0;

	stick_id == ANALOG_STICK_ID::LEFT ?
		ded = m_LeftStick.y * 10 :
		ded = m_RightStick.y * 10;

	return ded / 10.0f;
}