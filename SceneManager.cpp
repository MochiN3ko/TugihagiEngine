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

	//�ŏ��̓^�C�g��
	scene = new TitleScene(this);
	scene->Initialize(dxCommon, textureManager,input, camera);
}

void SceneManager::Update()
{
	//�V�[����Update
	scene->Update();
}

void SceneManager::Draw(DirectXCommon* dxCommon)
{
	scene->Draw(dxCommon);
}

void SceneManager::SetNextScene(BaseScene* nextScene)
{
	//���̃V�[���폜
	delete scene;
	//�ė��p
	scene = nullptr;
	//���̃V�[������
	scene = nextScene;
	scene->Initialize(dxCommon, textureManager, input, camera);
}
