#include "DirectXGame.h"
using namespace DirectX;
using namespace Microsoft::WRL;

void DirectXGame::Initialize()
{
	//���N���X�̏�����
	BaseGame::Initialize();

	//�|�X�g�G�t�F�N�g�p�e�N�X�`���̓ǂݍ���
	textureManager->LoadTexture(100, L"Resources/sprite.png");
	//�|�X�g�G�t�F�N�g�̏�����
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

	//�J�����̃|�W�V�����ƃA���O��
	camera->SetTarget(XMFLOAT3(0.0f, 0.0f, 0.0f));//�����_
	camera->SetEye(XMFLOAT3(0.0f, 0.0f, -10.0f));//���_
}

void DirectXGame::Update()
{
	//���N���X�̍X�V����
	BaseGame::Update();

	sceneManager->Update();

	float a = sprite->GetPosition().x;
	a++;
	sprite->SetPosition({ a,0 });

}

void DirectXGame::Draw()
{
	//�|�X�g�G�t�F�N�g�̕`��
	postEffect->PreDrawScene(dxCommon->GetCommandList());

	sceneManager->Draw(dxCommon.get());

	Sprite::SetPiepelineState(dxCommon->GetCommandList());

	postEffect->PostDrawScene(dxCommon->GetCommandList());

#pragma region postEffect

	dxCommon->BeginDraw();
	//�|�X�g�G�t�F�N�g�̃t�B���^�[��ʂ��ĕ`��
	postEffect->Draw(dxCommon->GetCommandList());

	sprite->Draw(dxCommon->GetCommandList());

	dxCommon->EndDraw();
}
#pragma endregion

void DirectXGame::Finalize()
{
	BaseGame::Finalize();
}

