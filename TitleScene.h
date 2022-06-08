#pragma once
#include "BaseScene.h"
#include"SceneManager.h"
#include"Object3d.h"
#include"Model.h"

//タイトルシーン
class TitleScene :
    public BaseScene
{
private:

    std::unique_ptr<Object3d>title;
    std::unique_ptr<Object3d>enter;

    float angle;

public:
    TitleScene(SceneManager* sceneManager);
    ~TitleScene();

    void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, Input* input, Camera* camera) override;

    void Update() override;

    void Draw(DirectXCommon* dxCommon) override;
};

