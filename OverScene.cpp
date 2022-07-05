#include "OverScene.h"

OverScene::OverScene(SceneManager* sceneManager)
	:BaseScene(sceneManager)
{
	over = std::make_unique<Object3d>();
	click = std::make_unique<Object3d>();
}

OverScene::~OverScene()
{
}

void OverScene::Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, Input* input, Camera* camera)
{
	//�����ݒ�
	BaseScene::Initialize(dxCommon, textureManager, input, camera);

	over->Initialize(loader->GetModel(Loader::ModelIndex::OVER));
	over->SetColor(Vector3(0.8f, 0.15f, 0.15f));

	click->Initialize(loader->GetModel(Loader::ModelIndex::LEFTCLICK));
	click->SetColor(Vector3(0.8f, 0.15f, 0.15f));

	position = Vector3(0.0f, -7.0f, 50.0f);
	scale = Vector3(10.0f, 10.0f, 10.0f);

	angle = 0.0f;

	//�J�����̃|�W�V�����ƃA���O��
	camera->SetTarget(Vector3(0.0f, 0.0f, 0.0f));//�����_
	camera->SetEye(Vector3(0.0f, 0.0f, -10.0f));//���_

	ShowCursor(TRUE);
}

void OverScene::Update()
{
	//�^�C�g��
	//�z�o�����O�̕�
	float range = 0.1f;
	//�z�o�����O�̑���
	angle += 0.042f;
	scale += Vector3(sinf(angle) * range, sinf(angle) * range, sinf(angle) * range);

	over->SetPosition(position);
	over->SetRotation(rotation);
	over->SetScale(scale);
	over->Update();

	click->SetPosition(Vector3(0.0f, -15.0f, 30.0f));
	click->SetRotation(Vector3::Zero);
	click->SetScale(Vector3(5.0f, 5.0f, 5.0f));
	click->Update();

	if (input->MouseButtonTrigger(0))
	{
		//���̃V�[����
		sceneManager_->SetNextScene(new TitleScene(sceneManager_));
	}
}

void OverScene::Draw(DirectXCommon* dxCommon)
{
	over->Draw(dxCommon->GetCommandList());
	click->Draw(dxCommon->GetCommandList());
}
