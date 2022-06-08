#include "SceneManager.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
	delete scene;
}

void SceneManager::Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, Input* input, Camera* camera)
{
	this->dxCommon = dxCommon;
	this->textureManager = textureManager;
	this->input = input;
	this->camera = camera;

	//最初はタイトル
	scene = new TitleScene(this);
	scene->Initialize(dxCommon, textureManager,input, camera);
}

void SceneManager::Update()
{
	//シーンのUpdate
	scene->Update();
}

void SceneManager::Draw(DirectXCommon* dxCommon)
{
	scene->Draw(dxCommon);
}

void SceneManager::SetNextScene(BaseScene* nextScene)
{
	//今のシーン削除
	delete scene;
	//再利用
	scene = nullptr;
	//次のシーンを代入
	scene = nextScene;
	scene->Initialize(dxCommon, textureManager, input, camera);
}
