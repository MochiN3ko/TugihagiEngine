#include "BaseGame.h"

#pragma comment(lib,"winmm.lib")

std::unique_ptr<Loader> BaseGame::loader;

void BaseGame::Run()
{
	//������
	Initialize(); 
	
	while (true)
	{
		if (endFlag) {
			break;
		}

		//�X�V
		Update();
		
		//�`��
		Draw();

		FrameRate();
	}
	Finalize();
}

void BaseGame::Initialize()
{
	//WindowsAPI������
	winApp = std::make_unique<WinApp>();
	winApp->Initialize();

	//DirectX������������������
	dxCommon = std::make_unique<DirectXCommon>();
	dxCommon->Initialize(winApp.get());

	//TextureManager�̏�����
	textureManager = std::make_unique<TextureManager>();
	textureManager->Initialize(dxCommon.get());

	//Input�̏�����
	input = std::make_unique<Input>();
	input->Initialize(winApp->GetHwnd());

	//SoundManager�̏�����
	soundManager = std::make_unique<SoundManager>();
	soundManager->Initialize();

	//Camera�̏�����
	camera = std::make_unique<Camera>();
	camera->Initialize();

	//Loader�̏�����
	loader = std::make_unique<Loader>(textureManager.get());
	loader->Initialize(dxCommon.get(), textureManager.get());

	//�X�v���C�g�̐ÓI������
	Sprite::StaticInitialize(dxCommon.get(), textureManager.get());
	//3D�I�u�W�F�N�g�̐ÓI������
	Object3d::StaticInitialize(dxCommon.get(), camera.get());

	//�t���[�����[�g�̏�����
	QueryPerformanceFrequency(&freqTime);
	QueryPerformanceCounter(&startTime);
}

void BaseGame::Update()
{
#pragma region �E�B���h�E���b�Z�[�W����
	if (winApp->Update()) {
		endFlag = true;
	}
#pragma endregion

	input->Update();
	camera->Update();
}

void BaseGame::Finalize()
{
	Sprite::StaticFinalize();
	Object3d::StaticFinalize();
}

void BaseGame::FrameRate()
{
	if (count == MinFrameTime)
	{
		QueryPerformanceCounter(&endTime);
		fps = 1000.0f / (static_cast<float>((endTime.QuadPart - startTime.QuadPart) * 1000.0f / freqTime.QuadPart) / MinFrameTime);
		count = 0;
		startTime = endTime;
	}
	count++;
	QueryPerformanceCounter(&endTime);
	{
		//1�~���b
		DWORD sleepTime = static_cast<DWORD>((1000.0f / MinFrameTime) * count - (endTime.QuadPart - startTime.QuadPart) * 1000.0f / freqTime.QuadPart);

		if (sleepTime < 18 && sleepTime>0)
		{
			timeBeginPeriod(1);
			Sleep(sleepTime);
			timeEndPeriod(1);
		}
		else
		{
			timeBeginPeriod(1);
			Sleep(1);
			timeEndPeriod(1);
		}
	}
}
