#include "Input.h"
#include <iostream>

IDirectInput8* Input::dinput = nullptr;
IDirectInputDevice8* Input::devKeyboard = nullptr;
IDirectInputDevice8* Input::devMouse = nullptr;
BYTE Input::currentKey[256] = {};
BYTE Input::previousKey[256] = {};
DIMOUSESTATE Input::currentMouse = {};
DIMOUSESTATE Input::previousMouse = {};
XINPUT_STATE Input::currentPadState = {};
XINPUT_STATE Input::previousPadState = {};

Input::Input()
{

}

Input::~Input()
{

}

void Input::Initialize(const HWND& hwnd)
{
	//DirectInput オブジェクトの生成
	DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dinput, nullptr);
	
	//キーボードデバイスの生成
	dinput->CreateDevice(GUID_SysKeyboard, &devKeyboard, NULL);
	//入力データ形式のセット
	devKeyboard->SetDataFormat(&c_dfDIKeyboard); // 標準形式
	//排他制御レベルのセット
	devKeyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);

	//マウスデバイスの生成
	dinput->CreateDevice(GUID_SysMouse, &devMouse, NULL);
	devMouse->SetDataFormat(&c_dfDIMouse);
	devMouse->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);

	//ゲームパッドの初期化
	ZeroMemory(&currentPadState, sizeof(XINPUT_STATE));
	ZeroMemory(&previousPadState, sizeof(XINPUT_STATE));
}

void Input::Update()
{
	//キーボード情報の取得開始
	devKeyboard->Acquire();

	//前回の入力情報をコピー
	for (int i = 0; i < 256; ++i)
	{
		previousKey[i] = currentKey[i];
	}

	devKeyboard->GetDeviceState(sizeof(currentKey), currentKey);

	//マウス
	devMouse->Acquire();
	memcpy(&previousMouse, &currentMouse, sizeof(currentMouse));
	devMouse->GetDeviceState(sizeof(currentMouse), &currentMouse);

	//パッドの入力情報の更新
	previousPadState = currentPadState;
	XInputGetState(0, &currentPadState);
}

void Input::Finalize()
{
	dinput->Release();
	devKeyboard->Release();
	devMouse->Release();
}

bool Input::KeyPress(const int& keyNum)
{
	return (currentKey[keyNum]);
}

bool Input::KeyTrigger(const int& keyNum)
{
	return (currentKey[keyNum] && !previousKey[keyNum]);
}

bool Input::KeyHold(const int& keyNum)
{
	return (currentKey[keyNum] && previousKey[keyNum]);
}

bool Input::KeyRelease(const int& keyNum)
{
	return (!currentKey[keyNum] && !previousKey[keyNum]);
}

bool Input::MouseButtonPress(const int& keyNum)
{
	return (currentMouse.rgbButtons[keyNum]);
}

bool Input::MouseButtonTrigger(const int& keyNum)
{
	return (currentMouse.rgbButtons[keyNum] && !previousMouse.rgbButtons[keyNum]);
}

bool Input::MouseButtonHold(const int& keyNum)
{
	return (currentMouse.rgbButtons[keyNum] && previousMouse.rgbButtons[keyNum]);
}

bool Input::MouseButtonRelease(const int& keyNum)
{
	return (!currentMouse.rgbButtons[keyNum] && previousMouse.rgbButtons[keyNum]);
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
	return (currentPadState.Gamepad.wButtons & keyNum);
}

bool Input::PadButtonTrigger(const int& keyNum)
{
	return (currentPadState.Gamepad.wButtons & keyNum) && !(previousPadState.Gamepad.wButtons & keyNum);
}

bool Input::PadButtonHold(const int& keyNum)
{
	return (currentPadState.Gamepad.wButtons & keyNum) && (previousPadState.Gamepad.wButtons & keyNum);
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