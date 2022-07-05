#pragma once
#include"BaseScene.h"
#include"TitleScene.h"
#include"PlayScene.h"
#include"ClearScene.h"
#include"OverScene.h"

//シーン切り替えクラス
class SceneManager
{
public:
	enum class ChangeScene
	{
		CLOSING,
		PLAYING,
		OPENING,
	};

private:
	DirectXCommon* dxCommon = nullptr;
	TextureManager* textureManager = nullptr;
	Input* input = nullptr;
	Camera* camera = nullptr;

	BaseScene* mainScene = nullptr;
	BaseScene* subScene = nullptr;

	std::unique_ptr<ChangeOpen>open;
	std::unique_ptr<ChangeClose>close;

	int changeSceneNum = 1;
	int changeSceneCount = 0;

public:
	SceneManager();
	~SceneManager();

	void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, Input* input, Camera* camera);

	void Update();

	void Draw(DirectXCommon* dxCommon);

	void SetNextScene(BaseScene* nextScene);

	void Closing();

	void Opening();

	void SetChangeSceneNum(const int& num) { changeSceneNum = num; }
};

