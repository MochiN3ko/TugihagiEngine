#include "OverScene.h"

OverScene::OverScene(SceneManager* sceneManager)
	:BaseScene(sceneManager)
{
	over = std::make_unique<Object3d>();
	enter = std::make_unique<Object3d>();
}

OverScene::~OverScene()
{
}

void OverScene::Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, Input* input, Camera* camera)
{
	//初期設定
	BaseScene::Initialize(dxCommon, textureManager, input, camera);

	over->Initialize(loader->GetModel(Loader::ModelIndex::OVER));
	over->SetColor(Vector3(0.8f, 0.15f, 0.15f));

	enter->Initialize(loader->GetModel(Loader::ModelIndex::ENTER));
	enter->SetColor(Vector3(0.8f, 0.15f, 0.15f));

	position = Vector3(0.0f, -7.0f, 50.0f);
	scale = Vector3(10.0f, 10.0f, 10.0f);

	angle = 0.0f;

	//カメラのポジションとアングル
	camera->SetTarget(Vector3(0.0f, 0.0f, 0.0f));//注視点
	camera->SetEye(Vector3(0.0f, 0.0f, -10.0f));//視点

	ShowCursor(TRUE);
}

void OverScene::Update()
{
	//タイトル
	//ホバリングの幅
	float range = 0.1f;
	//ホバリングの速さ
	angle += 0.042f;
	scale += Vector3(sinf(angle) * range, sinf(angle) * range, sinf(angle) * range);

	over->SetPosition(position);
	over->SetRotation(rotation);
	over->SetScale(scale);
	over->Update();

	enter->SetPosition(Vector3(0.0f, -15.0f, 30.0f));
	enter->SetRotation(Vector3::Zero);
	enter->SetScale(Vector3(5.0f, 5.0f, 5.0f));
	enter->Update();

	if (input->TriggerKey(DIK_RETURN))
	{
		//次のシーンへ
		sceneManager_->SetNextScene(new TitleScene(sceneManager_));
	}
}

void OverScene::Draw(DirectXCommon* dxCommon)
{
	over->Draw(dxCommon->GetCommandList());
	enter->Draw(dxCommon->GetCommandList());
}
