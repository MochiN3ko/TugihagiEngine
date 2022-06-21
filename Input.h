#pragma once
#define DIRECTINPUT_VERSION 0x0800 //DirectInputのバージョン指定
#include <dinput.h>
#include<Windows.h>
#include <wrl.h>


#include<Xinput.h>
#include<stdio.h>

#pragma comment(lib, "dinput8.lib")
#pragma comment (lib, "xinput.lib")

class Input
{
public:
	Input();
	~Input();

	void Initialize(HWND hwnd);

	void Update();

	static void Finalize();

	bool PushKey(const int& keyNum);

	bool TriggerKey(const int& keyNum);

	//マウス
	bool MouseButtonPress(const int& keyNum);
	bool MouseButtonTrigger(const int& keyNum);
	bool MouseButtonHold(const int& keyNum);
	bool MouseButtonRelease(const int& keyNum);

	int MouseXMove();
	int MouseYMove();
	int MouseWheelMove();

	//ゲームパッドのボタンの入力状況
	bool PadButtonPress(const int& keyNum);//押していたら

	bool PadButtonTrigger(const int& keyNum);//押した瞬間のみ

	bool PadButtonRelease(const int& keyNum);//離した瞬間のみ

	 //左右トリガーの入力
	bool PadLeftTriggerState();//左トリガー

	bool PadRightTriggerState();//右トリガー

	//左スティックの上下左右の入力状況
	bool PadLeftStickRight();//右

	bool PadLeftStickLeft();//左

	bool PadLeftStickUp();//上

	bool PadLeftStickDown();//下

	//右スティックの上下左右の入力状況
	bool PadRightStickRight();//右

	bool PadRightStickLeft();//左

	bool PadRightStickUp();//上

	bool PadRightStickDown();//下

private:
	//キーボードデバイスの生成
	IDirectInputDevice8* devkeyboard = nullptr;
	//全キーの入力状態を取得する
	BYTE key[256] = {};
	BYTE key2[256] = {};

	//マウス
	static DIMOUSESTATE currentMouse;
	static DIMOUSESTATE prevMouse;
	static IDirectInputDevice8* devmouse;

	//ゲームパッドの入力情報を格納する
	XINPUT_STATE currentPadState;//現在

	XINPUT_STATE previousPadState;//1フレーム前
};

