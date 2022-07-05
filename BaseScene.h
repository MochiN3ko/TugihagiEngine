#pragma once
#include "DirectXCommon.h"
#include "TextureManager.h"
#include"SoundManager.h"
#include"Input.h"
#include"Camera.h"
#include"Sprite.h"
#include"Vector2.h"
#include"Vector3.h"
#include"Loader.h"
#include"ChangeOpen.h"
#include"ChangeClose.h"
#include <DirectXMath.h>
#include<memory>

class SceneManager;

//シーン基底クラス
class BaseScene
{
protected:

	SceneManager* sceneManager_ = nullptr;
	DirectXCommon* dxCommon = nullptr;
	TextureManager* textureManager = nullptr;
	Input* input = nullptr;
	Camera* camera = nullptr;

	static Loader* loader;

public:

	BaseScene(SceneManager* sceneManager);
	~BaseScene();

	virtual void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, Input* input, Camera* camera);

	virtual void Update() = 0;

	virtual void Draw(DirectXCommon* dxCommon) = 0;

	static void SetModelLoad(Loader* loader_) { loader = loader_; }

};

