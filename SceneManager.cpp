#include "SceneManager.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
	delete mainScene;
}

void SceneManager::Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, Input* input, Camera* camera)
{
	this->dxCommon = dxCommon;
	this->textureManager = textureManager;
	this->input = input;
	this->camera = camera;

	//最初はタイトル
	mainScene = new TitleScene(this);
	mainScene->Initialize(dxCommon, textureManager,input, camera);

	open = std::make_unique<ChangeOpen>();
	open->Initialize(dxCommon, textureManager, 3);
	close = std::make_unique<ChangeClose>();
	close->Initialize(dxCommon, textureManager, 3);
}

void SceneManager::Update()
{
	mainScene->Update();
}

void SceneManager::Draw(DirectXCommon* dxCommon)
{
	mainScene->Draw(dxCommon);
}

void SceneManager::SetNextScene(BaseScene* nextScene)
{
	//今のシーン削除
	delete mainScene;
	//再利用
	mainScene = nullptr;
	//次のシーンを代入
	mainScene = nextScene;
	mainScene->Initialize(dxCommon, textureManager, input, camera);

}

void SceneManager::Closing()
{
	changeSceneCount++;
	if (changeSceneCount >= 120)
	{
		close->Update();
	}
	else
	{
		changeSceneCount = 0;
		changeSceneNum = (int)ChangeScene::PLAYING;
	}
}

void SceneManager::Opening()
{
	changeSceneCount++;
	if (changeSceneCount > 120)
	{
		open->Update();
	}
	else
	{
		changeSceneCount = 0;
		changeSceneNum = (int)ChangeScene::CLOSING;
	}
}

