#pragma once
#include "BaseScene.h"
#include"SceneManager.h"
#include"Object3d.h"
#include"Model.h"

//オーバーシーン
class OverScene :
    public BaseScene
{
private:

    std::unique_ptr<Object3d>over;
    std::unique_ptr<Object3d>enter;

    float angle;

public:
    OverScene(SceneManager* sceneManager);
    ~OverScene();

    void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, Input* input, Camera* camera) override;

    void Update() override;

    void Draw(DirectXCommon* dxCommon) override;
};

