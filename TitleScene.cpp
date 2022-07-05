#include "TitleScene.h"

TitleScene::TitleScene(SceneManager* sceneManager)
	:BaseScene(sceneManager)
{
	title = std::make_unique<Object3d>();
	click = std::make_unique<Object3d>();
	leftBgTank = std::make_unique<BackGroundObject>();
	rightBgTank = std::make_unique<BackGroundObject>();

	open = std::make_unique<ChangeOpen>();
	close = std::make_unique<ChangeClose>();
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

	//クリックオブジェクト
	click->Initialize(loader->GetModel(Loader::ModelIndex::LEFTCLICK));
	click->SetColor(Vector3(0.15f, 1.0f, 0.15f));

	leftBgTank->Initialize(dxCommon, textureManager, 3);
	leftBgTank->SetPosition(Vector3(-35.0f, -19.0f, 40.0f));
	leftBgTank->SetVelocity(Vector3::Zero);

	rightBgTank->Initialize(dxCommon, textureManager, 3);
	rightBgTank->SetPosition(Vector3(35.0f, -19.0f, 40.0f));
	rightBgTank->SetRotation(Vector3::Zero);
	rightBgTank->SetVelocity(Vector3::Zero);

	open->Initialize(dxCommon, textureManager, 3);
	close->Initialize(dxCommon, textureManager, 3);

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

	click->SetPosition(Vector3(0.0f, -15.0f, 30.0f));
	click->SetRotation(Vector3::Zero);
	click->SetScale(Vector3(5.0f,5.0f,5.0f));
	click->Update();

	leftBgTank->Update();
	rightBgTank->Update();

	open->Update();

	/*if (input->MouseButtonTrigger(0))
	{
		sceneManager_->SetNextScene(new PlayScene(sceneManager_));
	}*/
}

void TitleScene::Draw(DirectXCommon* dxCommon)
{
	title->Draw(dxCommon->GetCommandList());

	click->Draw(dxCommon->GetCommandList());

	leftBgTank->Draw(dxCommon);

	rightBgTank->Draw(dxCommon);

	open->Draw(dxCommon);
}
