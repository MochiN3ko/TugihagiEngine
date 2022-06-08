#pragma once

#include"WinApp.h"
#include"DirectXCommon.h"
#include"Input.h"
#include"TextureManager.h"
#include"Sprite.h"
#include"SoundManager.h"
#include"Model.h"
#include"Object3d.h"
#include"Camera.h"
#include"Light.h"
#include"Loader.h"

#include<mmsystem.h>

class BaseGame
{
public:

	virtual void Run();
	/// <summary>
	/// ������
	/// </summary>
	virtual void Initialize();
	/// <summary>
	/// �X�V
	/// </summary>
	virtual void Update();
	/// <summary>
	/// �`��
	/// </summary>
	virtual void Draw() = 0;
	/// <summary>
	/// �㏈��
	/// </summary>
	virtual void Finalize();

private:
	/// <summary>
	/// �t���[�����[�g�̌Œ�
	/// </summary>
	void FrameRate();

	//�Œ�t���[��
	const float MinFrameTime = 60.0f;
	float frameTime = 0.0f;
	LARGE_INTEGER startTime;
	LARGE_INTEGER endTime;
	LARGE_INTEGER freqTime;
	int count = 0;
	float fps = 0.0f;
protected:
	//�I���t���O
	bool endFlag = false;

	std::unique_ptr<WinApp>winApp;
	//DirectX���
	std::unique_ptr<DirectXCommon>dxCommon;
	//����
	std::unique_ptr<Input>input;
	//�e�N�X�`���[�}�l�[�W���[
	std::unique_ptr<TextureManager>textureManager;
	//�X�v���C�g
	std::unique_ptr<Sprite>sprite;
	//�T�E���h�}�l�[�W���[
	std::unique_ptr<SoundManager>soundManager;
	//�J����
	std::unique_ptr<Camera>camera;
	//���C�g
	std::unique_ptr<Light>light;

	static std::unique_ptr<Loader>loader;

};

