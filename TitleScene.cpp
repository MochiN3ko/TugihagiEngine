#include "TitleScene.h"

TitleScene::TitleScene(SceneManager* sceneManager)
	:BaseScene(sceneManager)
{
	title = std::make_unique<Object3d>();
	enter = std::make_unique<Object3d>();
}

TitleScene::~TitleScene()
{
}

void TitleScene::Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, Input* input, Camera* camera)
{
	//初期設定
	BaseScene::Initialize(dxCommon, textureManager, input, camera);

	title->Initialize(loader->GetModel(Loader::ModelIndex::TANKTANK));
	title->SetColor(Vector3(0.8f, 0.0f, 0.4f));

	enter->Initialize(loader->GetModel(Loader::ModelIndex::ENTER));
	enter->SetColor(Vector3(0.8f, 0.0f, 0.4f));

	position = Vector3(0.0f, -5.0f, 30.0f);
	scale = Vector3(10.0f, 10.0f, 10.0f);

	angle = 0.0f;

	//カメラのポジションとアングル
	camera->SetTarget(Vector3(0, 0, 0));//注視点
	camera->SetEye(Vector3(0, 0, -10));//視点
}

void TitleScene::Update()
{
	//ホバリングの幅
	float range = 0.15f;
	//ホバリングの速さ
	angle += 0.06f;
	position += Vector3(0, sin(angle) * range, 0);
	rotation.y++;

	//Title
	title->SetPosition(position);
	title->SetRotation(rotation);
	title->SetScale(scale);
	title->Update();

	enter->SetPosition(Vector3(0, -15, 30));
	enter->SetRotation(Vector3::Zero);
	enter->SetScale(Vector3(5,5,5));
	enter->Update();

	if (input->TriggerKey(DIK_RETURN))
	{
		sceneManager_->SetNextScene(new PlayScene(sceneManager_));
	}
	
}

void TitleScene::Draw(DirectXCommon* dxCommon)
{
	title->Draw(dxCommon->GetCommandList());
	enter->Draw(dxCommon->GetCommandList());
}
