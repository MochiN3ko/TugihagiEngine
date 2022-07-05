#include "DirectXGame.h"
using namespace DirectX;
using namespace Microsoft::WRL;

void DirectXGame::Initialize()
{
	//基底クラスの初期化
	BaseGame::Initialize();

	//ポストエフェクト用テクスチャの読み込み
	textureManager->LoadTexture(100, L"Resources/sprite.png");
	//ポストエフェクトの初期化
	postEffect = std::make_unique<PostEffect>();
	postEffect->Initialize();
	//postEffect->SetShift(0.2f);

	BaseGameObject::SetModelLoad(loader.get());
	BaseScene::SetModelLoad(loader.get());
	sceneManager = std::make_unique<SceneManager>();
	sceneManager->Initialize(dxCommon.get(), textureManager.get(), input.get(), camera.get());

	sprite = new Sprite(3, Vector2(0, 0), Vector2(1, 1), {1,0,0,0}, Vector2(0, 0),false,false);
	sprite->Initialize(6);
	sprite->SetSize(0.5, 0.5);
	sprite->SetPosition({ 0,0 });
	sprite->SetR(90);

	//カメラのポジションとアングル
	camera->SetTarget(XMFLOAT3(0.0f, 0.0f, 0.0f));//注視点
	camera->SetEye(XMFLOAT3(0.0f, 0.0f, -10.0f));//視点
}

void DirectXGame::Update()
{
	//基底クラスの更新処理
	BaseGame::Update();

	sceneManager->Update();

	float a = sprite->GetPosition().x;
	a++;
	sprite->SetPosition({ a,0 });

}

void DirectXGame::Draw()
{
	//ポストエフェクトの描画
	postEffect->PreDrawScene(dxCommon->GetCommandList());

	sceneManager->Draw(dxCommon.get());

	Sprite::SetPiepelineState(dxCommon->GetCommandList());

	postEffect->PostDrawScene(dxCommon->GetCommandList());

#pragma region postEffect

	dxCommon->BeginDraw();
	//ポストエフェクトのフィルターを通して描画
	postEffect->Draw(dxCommon->GetCommandList());

	sprite->Draw(dxCommon->GetCommandList());

	dxCommon->EndDraw();
}
#pragma endregion

void DirectXGame::Finalize()
{
	BaseGame::Finalize();
}

