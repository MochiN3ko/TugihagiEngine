#include "ClearScene.h"

ClearScene::ClearScene(SceneManager* sceneManager)
	:BaseScene(sceneManager)
{
	object = std::make_unique<Object3d>();
}

ClearScene::~ClearScene()
{
}

void ClearScene::Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, Input* input, Camera* camera)
{
	//�����ݒ�
	BaseScene::Initialize(dxCommon, textureManager, input, camera);

	object->Initialize(loader->GetModel(Loader::ModelIndex::CLEAR));
	object->SetColor(Vector3(1.0f, 1.0f, 0.0f));

	position = Vector3(0.0f, 0.0f, 50.0f);
	scale = Vector3(30.0f, 30.0f, 30.0f);

	//�J�����̃|�W�V�����ƃA���O��
	camera->SetTarget(Vector3(0, 0, 0));//�����_
	camera->SetEye(Vector3(0, 0, -10));//���_
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

void ClearScene::Draw(DirectXCommon* dxCommon)
{
	object->Draw(dxCommon->GetCommandList());
}
