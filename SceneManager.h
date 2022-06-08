#pragma once
#include"BaseScene.h"
#include"TitleScene.h"
#include"PlayScene.h"
#include"ClearScene.h"
#include"OverScene.h"

//シーン切り替えクラス
class SceneManager
{
private:
	DirectXCommon* dxCommon = nullptr;
	TextureManager* textureManager = nullptr;
	Input* input = nullptr;
	Camera* camera = nullptr;

	BaseScene* scene = nullptr;

public:
	SceneManager();
	~SceneManager();

	void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, Input* input, Camera* camera);

	void Update();

	void Draw(DirectXCommon* dxCommon);

	void SetNextScene(BaseScene* nextScene);
};

