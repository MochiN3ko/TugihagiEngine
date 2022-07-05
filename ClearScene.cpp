#include "ClearScene.h"

ClearScene::ClearScene(SceneManager* sceneManager)
	:BaseScene(sceneManager)
{
	clear = std::make_unique<Object3d>();
	click = std::make_unique<Object3d>();
}

ClearScene::~ClearScene()
{
}

void ClearScene::Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, Input* input, Camera* camera)
{
	//初期設定
	BaseScene::Initialize(dxCommon, textureManager, input, camera);

	clear->Initialize(loader->GetModel(Loader::ModelIndex::CLEAR));
	clear->SetColor(Vector3(1.0f, 0.84f, 0.0f));

	click->Initialize(loader->GetModel(Loader::ModelIndex::LEFTCLICK));
	click->SetColor(Vector3(1.0f, 0.84f, 0.0f));

	position = Vector3(0.0f, -7.0f, 50.0f);
	scale = Vector3(30.0f, 30.0f, 30.0f);

	//カメラのポジションとアングル
	camera->SetTarget(Vector3(0, 0, 0));//注視点
	camera->SetEye(Vector3(0, 0, -10));//視点

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

	click->SetPosition(Vector3(0, -15, 30));
	click->SetRotation(Vector3::Zero);
	click->SetScale(Vector3(5, 5, 5));
	click->Update();

	if (input->MouseButtonTrigger(0))
	{
		//次のシーンへ
		sceneManager_->SetNextScene(new TitleScene(sceneManager_));
	}
}

void ClearScene::Draw(DirectXCommon* dxCommon)
{
	clear->Draw(dxCommon->GetCommandList());
	click->Draw(dxCommon->GetCommandList());

}
