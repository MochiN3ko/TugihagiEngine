#pragma once
#include "BaseScene.h"
#include"SceneManager.h"
#include"Object3d.h"
#include"Model.h"
#include<vector>

//タイトルシーン
class TitleScene :
    public BaseScene
{
private:

    std::unique_ptr<Object3d>title;
    std::unique_ptr<Object3d>enter;

    std::unique_ptr<Object3d>turret;
    std::unique_ptr<Object3d>body;

    std::unique_ptr<Object3d>turret2;
    std::unique_ptr<Object3d>body2;

    float angle;

public:
    TitleScene(SceneManager* sceneManager);
    ~TitleScene();

    void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, Input* input, Camera* camera) override;

    void Update() override;

    void Draw(DirectXCommon* dxCommon) override;
};

