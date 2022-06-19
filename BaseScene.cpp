#include "BaseScene.h"

Loader* BaseScene::loader = nullptr;

BaseScene::BaseScene(SceneManager* sceneManager)
	:sceneManager_(sceneManager)
{
}

BaseScene::~BaseScene()
{
}

void BaseScene::Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, Input* input, Camera* camera)
{
	this->dxCommon = dxCommon;
	this->textureManager = textureManager;
	this->input = input;
	this->camera = camera;

}


