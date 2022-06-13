#include "ClearScene.h"

ClearScene::ClearScene(SceneManager* sceneManager)
	:BaseScene(sceneManager)
{
	clear = std::make_unique<Object3d>();
	enter = std::make_unique<Object3d>();
}

ClearScene::~ClearScene()
{
}

void ClearScene::Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, Input* input, Camera* camera)
{
	//�����ݒ�
	BaseScene::Initialize(dxCommon, textureManager, input, camera);

	clear->Initialize(loader->GetModel(Loader::ModelIndex::CLEAR));
	clear->SetColor(Vector3(1.0f, 0.84f, 0.0f));

	enter->Initialize(loader->GetModel(Loader::ModelIndex::ENTER));
	enter->SetColor(Vector3(1.0f, 0.84f, 0.0f));

	position = Vector3(0.0f, -7.0f, 50.0f);
	scale = Vector3(30.0f, 30.0f, 30.0f);

	//�J�����̃|�W�V�����ƃA���O��
	camera->SetTarget(Vector3(0, 0, 0));//�����_
	camera->SetEye(Vector3(0, 0, -10));//���_

	ShowCursor(TRUE);
}

void ClearScene::Update()
{
	if (scale.x > 10 && scale.y > 10 && scale.z > 10)
	{
		scale.x -= 0.4f;
		scale.y -= 0.4f;
		scale.z -= 0.4f;
		rotation.z -= 35.8f;
	}
	else
	{
		scale.x = 10.0f;
		scale.y = 10.0f;
		scale.z = 10.0f;
		rotation = Vector3::Zero;
	}

	clear->SetPosition(position);
	clear->SetRotation(rotation);
	clear->SetScale(scale);
	clear->Update();

	enter->SetPosition(Vector3(0, -15, 30));
	enter->SetRotation(Vector3::Zero);
	enter->SetScale(Vector3(5, 5, 5));
	enter->Update();

	if (input->TriggerKey(DIK_RETURN))
	{
		//���̃V�[����
		sceneManager_->SetNextScene(new TitleScene(sceneManager_));
	}
}

void ClearScene::Draw(DirectXCommon* dxCommon)
{
	clear->Draw(dxCommon->GetCommandList());
	enter->Draw(dxCommon->GetCommandList());

}
