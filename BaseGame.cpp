#include "BaseGame.h"

#pragma comment(lib,"winmm.lib")

std::unique_ptr<Loader> BaseGame::loader;

void BaseGame::Run()
{
	//初期化
	Initialize(); 
	
	while (true)
	{
		if (endFlag) {
			break;
		}

		//更新
		Update();
		
		//描画
		Draw();

		FrameRate();
	}
	Finalize();
}

void BaseGame::Initialize()
{
	//WindowsAPI初期化
	winApp = std::make_unique<WinApp>();
	winApp->Initialize();

	//DirectX初期化処理ここから
	dxCommon = std::make_unique<DirectXCommon>();
	dxCommon->Initialize(winApp.get());

	//TextureManagerの初期化
	textureManager = std::make_unique<TextureManager>();
	textureManager->Initialize(dxCommon.get());

	//Inputの初期化
	input = std::make_unique<Input>();
	input->Initialize(winApp->GetHwnd());

	//SoundManagerの初期化
	soundManager = std::make_unique<SoundManager>();
	soundManager->Initialize();

	//Cameraの初期化
	camera = std::make_unique<Camera>();
	camera->Initialize();

	//Loaderの初期化
	loader = std::make_unique<Loader>(textureManager.get());
	loader->Initialize(dxCommon.get(), textureManager.get());

	//スプライトの静的初期化
	Sprite::StaticInitialize(dxCommon.get(), textureManager.get());
	//3Dオブジェクトの静的初期化
	Object3d::StaticInitialize(dxCommon.get(), camera.get());

	//フレームレートの初期化
	QueryPerformanceFrequency(&freqTime);
	QueryPerformanceCounter(&startTime);
}

void BaseGame::Update()
{
#pragma region ウィンドウメッセージ処理
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
		//1ミリ秒
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
