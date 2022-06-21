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

	void Initialize(HWND hwnd);

	void Update();

	static void Finalize();

	bool PushKey(const int& keyNum);

	bool TriggerKey(const int& keyNum);

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
	//�L�[�{�[�h�f�o�C�X�̐���
	IDirectInputDevice8* devkeyboard = nullptr;
	//�S�L�[�̓��͏�Ԃ��擾����
	BYTE key[256] = {};
	BYTE key2[256] = {};

	//�}�E�X
	static DIMOUSESTATE currentMouse;
	static DIMOUSESTATE prevMouse;
	static IDirectInputDevice8* devmouse;

	//�Q�[���p�b�h�̓��͏����i�[����
	XINPUT_STATE currentPadState;//����

	XINPUT_STATE previousPadState;//1�t���[���O
};

