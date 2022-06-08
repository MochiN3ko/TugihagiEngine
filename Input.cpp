#include "Input.h"
#include <iostream>

DIMOUSESTATE Input::currentMouse;
DIMOUSESTATE Input::prevMouse;
IDirectInputDevice8* Input::devmouse = nullptr;

Input::Input()
{

}
Input::~Input()
{

}
void Input::Initialize(HWND hwnd)
{
	HRESULT result;
	//DirectInput �I�u�W�F�N�g�̐���
	IDirectInput8* dinput = nullptr;
	HINSTANCE hInstance = GetModuleHandle(nullptr);
	result = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dinput, nullptr);
	
	result = dinput->CreateDevice(GUID_SysKeyboard, &devkeyboard, NULL);
	//���̓f�[�^�`���̃Z�b�g
	result = devkeyboard->SetDataFormat(&c_dfDIKeyboard); // �W���`��
	//�r�����䃌�x���̃Z�b�g
	result = devkeyboard->SetCooperativeLevel(
		hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);

	//�}�E�X�f�o�C�X�̐���
	result = dinput->CreateDevice(GUID_SysMouse, &devmouse, NULL);
	result = devmouse->SetDataFormat(&c_dfDIMouse);
	result = devmouse->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);

	//�Q�[���p�b�h�̏�����
	ZeroMemory(&currentPadState, sizeof(XINPUT_STATE));
	ZeroMemory(&previousPadState, sizeof(XINPUT_STATE));
}

void Input::Update()
{
	HRESULT result;
	//�L�[�{�[�h���̎擾�J�n
	result = devkeyboard->Acquire();

	//�O��̓��͏����R�s�[
	for (int i = 0; i < 256; i++)
	{
		key2[i] = key[i];
	}

	result = devkeyboard->GetDeviceState(sizeof(key), key);

	//�}�E�X
	devmouse->Acquire();
	memcpy(&prevMouse, &currentMouse, sizeof(currentMouse));
	devmouse->GetDeviceState(sizeof(currentMouse), &currentMouse);

	//�p�b�h�̓��͏��̍X�V
	previousPadState = currentPadState;
	XInputGetState(0, &currentPadState);
}

void Input::Finalize()
{
	devmouse->Release();
}

bool Input::PushKey(const int& keyNum)
{
	if (keyNum < 0x00)return false;
	if (keyNum > 0xff)return false;

	if (key[keyNum])
	{
		return true;
	}
	return false;
}

bool Input::TriggerKey(const int& keyNum)
{
	if (keyNum < 0x00)return false;
	if (keyNum > 0xff)return false;
	//�O�񉟂���Ă��Ȃ��A����������Ă���
	if (!key2[keyNum]&&key[keyNum])
	{
		return true;
	}
	return false;
}

bool Input::MouseButtonPress(const int& keyNum)
{
	return (currentMouse.rgbButtons[keyNum]);
}

bool Input::MouseButtonTrigger(const int& keyNum)
{
	return (currentMouse.rgbButtons[keyNum] && !prevMouse.rgbButtons[keyNum]);
}

bool Input::MouseButtonHold(const int& keyNum)
{
	return (currentMouse.rgbButtons[keyNum] && prevMouse.rgbButtons[keyNum]);
}

bool Input::MouseButtonRelease(const int& keyNum)
{
	return (!currentMouse.rgbButtons[keyNum] && prevMouse.rgbButtons[keyNum]);
}

int Input::MouseXMove()
{
	return currentMouse.lX;
}

int Input::MouseYMove()
{
	return currentMouse.lY;
}

int Input::MouseWheelMove()
{
	return currentMouse.lZ;
}

bool Input::PadButtonPress(const int& keyNum)
{
	return currentPadState.Gamepad.wButtons & keyNum;
}

bool Input::PadButtonTrigger(const int& keyNum)
{
	return (currentPadState.Gamepad.wButtons & keyNum) && !(previousPadState.Gamepad.wButtons & keyNum);
}

bool Input::PadButtonRelease(const int& keyNum)
{
	return !(currentPadState.Gamepad.wButtons & keyNum) && (previousPadState.Gamepad.wButtons & keyNum);
}

bool Input::PadLeftTriggerState()
{
	return currentPadState.Gamepad.bLeftTrigger;
}

bool Input::PadRightTriggerState()
{
	return currentPadState.Gamepad.bRightTrigger;
}

bool Input::PadLeftStickRight()
{
	return currentPadState.Gamepad.sThumbLX >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
}

bool Input::PadLeftStickLeft()
{
	return currentPadState.Gamepad.sThumbLX <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
}

bool Input::PadLeftStickUp()
{
	return currentPadState.Gamepad.sThumbLY >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
}

bool Input::PadLeftStickDown()
{
	return currentPadState.Gamepad.sThumbLY <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
}

bool Input::PadRightStickRight()
{
	return currentPadState.Gamepad.sThumbRX >= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;
}

bool Input::PadRightStickLeft()
{
	return currentPadState.Gamepad.sThumbRX <= -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;
}

bool Input::PadRightStickUp()
{
	return currentPadState.Gamepad.sThumbRY >= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;
}

bool Input::PadRightStickDown()
{
	return currentPadState.Gamepad.sThumbRY <= -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;

}