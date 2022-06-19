#include "TitleScene.h"

TitleScene::TitleScene(SceneManager* sceneManager)
	:BaseScene(sceneManager)
{
	title = std::make_unique<Object3d>();
	enter = std::make_unique<Object3d>();

	turret = std::make_unique<Object3d>();
	body = std::make_unique<Object3d>();

	turret2 = std::make_unique<Object3d>();
	body2 = std::make_unique<Object3d>();

}

TitleScene::~TitleScene()
{
}

void TitleScene::Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, Input* input, Camera* camera)
{
	//初期設定
	BaseScene::Initialize(dxCommon, textureManager, input, camera);

	//タイトルオブジェクト
	title->Initialize(loader->GetModel(Loader::ModelIndex::TANKTANK));
	title->SetColor(Vector3(0.15f, 1.0f, 0.15f));

	//エンターオブジェクト
	enter->Initialize(loader->GetModel(Loader::ModelIndex::ENTER));
	enter->SetColor(Vector3(0.15f, 1.0f, 0.15f));

	//タレットオブジェクト
	turret->Initialize(loader->GetModel(Loader::ModelIndex::TURRET));
	turret->SetColor(Vector3(0.0f, 0.0f, 0.0f));
	turret2->Initialize(loader->GetModel(Loader::ModelIndex::TURRET));
	turret2->SetColor(Vector3(0.0f, 0.0f, 0.0f));

	//ボディオブジェクト
	body->Initialize(loader->GetModel(Loader::ModelIndex::BODY));
	body->SetColor(Vector3(0.0f, 0.0f, 0.0f));
	body2->Initialize(loader->GetModel(Loader::ModelIndex::BODY));
	body2->SetColor(Vector3(0.0f, 0.0f, 0.0f));

	position = Vector3(0.0f, -5.0f, 30.0f);
	scale = Vector3(10.0f, 10.0f, 10.0f);

	angle = 0.0f;

	//カメラのポジションとアングル
	camera->SetTarget(Vector3(0, 0, 0));//注視点
	camera->SetEye(Vector3(0, 0, -10));//視点

	//ShowCursor(TRUE);
}

void TitleScene::Update()
{
	//タイトル
	//ホバリングの幅
	float range = 0.1f;
	//ホバリングの速さ
	angle += 0.06f;
	position += Vector3(0.0f, sinf(angle) * range, 0.0f);
	rotation.y++;

	//タイトルオブジェクト
	title->SetPosition(position);
	title->SetRotation(rotation);
	title->SetScale(scale);
	title->Update();

	enter->SetPosition(Vector3(0.0f, -15.0f, 30.0f));
	enter->SetRotation(Vector3::Zero);
	enter->SetScale(Vector3(5.0f,5.0f,5.0f));
	enter->Update();

	turret->SetPosition(Vector3(35.0f, -18.0f, 40.0f));
	turret->SetRotation(Vector3(0.0f, 0.0f, 0.0f));
	turret->SetScale(Vector3(5.0f, 5.0f, 0.0f));
	turret->Update();

	body->SetPosition(Vector3(35.0f, -18.0f, 40.0f));
	body->SetRotation(Vector3(0.0f,0.0f,0.0f));
	body->SetScale(Vector3(5.0f, 5.0f, 0.0f));
	body->Update();

	turret2->SetPosition(Vector3(-35.0f, -18.0f, 40.0f));
	turret2->SetRotation(Vector3(0.0f, 180.0f, 0.0f));
	turret2->SetScale(Vector3(5.0f, 5.0f, 0.0f));
	turret2->Update();

	body2->SetPosition(Vector3(-35.0f, -18.0f, 40.0f));
	body2->SetRotation(Vector3(0.0f, 180.0f, 0.0f));
	body2->SetScale(Vector3(5.0f, 5.0f, 0.0f));
	body2->Update();

	if (input->TriggerKey(DIK_RETURN))
	{
		sceneManager_->SetNextScene(new PlayScene(sceneManager_));
	}
}

void TitleScene::Draw(DirectXCommon* dxCommon)
{
	title->Draw(dxCommon->GetCommandList());
	enter->Draw(dxCommon->GetCommandList());

	turret->Draw(dxCommon->GetCommandList());
	body->Draw(dxCommon->GetCommandList());

	turret2->Draw(dxCommon->GetCommandList());
	body2->Draw(dxCommon->GetCommandList());
}
