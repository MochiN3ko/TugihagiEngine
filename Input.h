#pragma once
#define DIRECTINPUT_VERSION 0x0800 //DirectInput�̃o�[�W�����w��
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

	void Initialize(const HWND& hwnd);

	void Update();

	static void Finalize();

	bool KeyPress(const int& keyNum);

	bool KeyTrigger(const int& keyNum);

	bool KeyHold(const int& keyNum);

	bool KeyRelease(const int& keyNum);

	//�}�E�X
	bool MouseButtonPress(const int& keyNum);

	bool MouseButtonTrigger(const int& keyNum);

	bool MouseButtonHold(const int& keyNum);

	bool MouseButtonRelease(const int& keyNum);

	int MouseXMove();

	int MouseYMove();

	int MouseWheelMove();

	//�Q�[���p�b�h�̃{�^���̓��͏�
	bool PadButtonPress(const int& keyNum);//�����Ă�����

	bool PadButtonTrigger(const int& keyNum);//�������u�Ԃ̂�

	bool PadButtonHold(const int& keyNum);//�������u�Ԃ̂�

	bool PadButtonRelease(const int& keyNum);//�������u�Ԃ̂�

	 //���E�g���K�[�̓���
	bool PadLeftTriggerState();//���g���K�[

	bool PadRightTriggerState();//�E�g���K�[

	//���X�e�B�b�N�̏㉺���E�̓��͏�
	bool PadLeftStickRight();//�E

	bool PadLeftStickLeft();//��

	bool PadLeftStickUp();//��

	bool PadLeftStickDown();//��

	//�E�X�e�B�b�N�̏㉺���E�̓��͏�
	bool PadRightStickRight();//�E

	bool PadRightStickLeft();//��

	bool PadRightStickUp();//��

	bool PadRightStickDown();//��

private:
	//DirectInput�̃f�o�C�X�S�̊Ǘ��N���X
	static IDirectInput8* dinput;

	//�e�f�o�C�X���ƂɊǗ�����N���X
	static IDirectInputDevice8* devKeyboard;

	static IDirectInputDevice8* devMouse;

	//�L�[�����i�[����p
	static BYTE currentKey[256];

	static BYTE previousKey[256];

	//�}�E�X�����i�[����p
	static DIMOUSESTATE currentMouse;

	static DIMOUSESTATE previousMouse;

	//�Q�[���p�b�h�̓��͏����i�[����p
	static XINPUT_STATE currentPadState;

	static XINPUT_STATE previousPadState;
};

