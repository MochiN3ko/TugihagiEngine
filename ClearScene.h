#pragma once
#include "BaseScene.h"
#include"SceneManager.h"
#include"Object3d.h"

//クリアシーン
class ClearScene :
    public BaseScene
{
private:
    std::unique_ptr<Object3d>clear;
    std::unique_ptr<Object3d>enter;

    //オブジェクト用
    Vector3 position = Vector3::Zero;//座標
    Vector3 rotation = Vector3::Zero;//回転
    Vector3 scale = Vector3::Zero;//スケール
    Vector3 velocity = Vector3::Zero;//加速度
    float angle;

public:
    ClearScene(SceneManager* sceneManager);
    ~ClearScene();

    void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, Input* input, Camera* camera) override;

    void Update() override;

    void Draw(DirectXCommon* dxCommon) override;
};

