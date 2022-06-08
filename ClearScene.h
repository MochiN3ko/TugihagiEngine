#pragma once
#include "BaseScene.h"
#include"SceneManager.h"
#include"Object3d.h"
#include"Model.h"

//クリアシーン
class ClearScene :
    public BaseScene
{
private:
    std::unique_ptr<Object3d>object;

    float angle;

public:
    ClearScene(SceneManager* sceneManager);
    ~ClearScene();

    void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, Input* input, Camera* camera) override;

    void Update() override;

    void Draw(DirectXCommon* dxCommon) override;
};

