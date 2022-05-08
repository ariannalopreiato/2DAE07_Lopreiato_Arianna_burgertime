#pragma once
#include <XInput.h>

namespace dae 
{
	enum class ControllerButton
	{
		ButtonA = XINPUT_GAMEPAD_A,
		ButtonB = XINPUT_GAMEPAD_B,
		ButtonX = XINPUT_GAMEPAD_X,
		ButtonY = XINPUT_GAMEPAD_Y,
		ButtonUp = XINPUT_GAMEPAD_DPAD_UP,
		ButtonDown = XINPUT_GAMEPAD_DPAD_DOWN,
		ButtonLeft = XINPUT_GAMEPAD_DPAD_LEFT,
		ButtonRight = XINPUT_GAMEPAD_DPAD_RIGHT
	};
}