#include "OverScene.h"

OverScene::OverScene(SceneManager* sceneManager)
	:BaseScene(sceneManager)
{
	object = std::make_unique<Object3d>();
}

OverScene::~OverScene()
{
}

void OverScene::Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, Input* input, Camera* camera)
{
	//�����ݒ�
	BaseScene::Initialize(dxCommon, textureManager, input, camera);

	object->Initialize(loader->GetModel(Loader::ModelIndex::OVER));
	object->SetColor(Vector3(1.0f, 1.0f, 0.0f));

	position = Vector3(0.0f, 0.0f, 50.0f);
	scale = Vector3(10.0f, 10.0f, 10.0f);

	angle = 0.0f;

	//�J�����̃|�W�V�����ƃA���O��
	camera->SetTarget(Vector3(0, 0, 0));//�����_
	camera->SetEye(Vector3(0, 0, -10));//���_
}

void OverScene::Update()
{

	object->SetPosition(position);
	object->SetRotation(rotation);
	object->SetScale(scale);
	object->Update();

	if (input->TriggerKey(DIK_RETURN))
	{
		//���̃V�[����
		sceneManager_->SetNextScene(new TitleScene(sceneManager_));
	}
}

void OverScene::Draw(DirectXCommon* dxCommon)
{
	object->Draw(dxCommon->GetCommandList());
}
