#pragma once
#include "BaseScene.h"
#include"SceneManager.h"
#include"Object3d.h"
#include"BackGroundObject.h"
#include<vector>

//タイトルシーン
class TitleScene :
    public BaseScene
{
private:
    std::unique_ptr<Object3d>title;
    std::unique_ptr<Object3d>click;

    std::unique_ptr<BackGroundObject>leftBgTank;
    std::unique_ptr<BackGroundObject>rightBgTank;

    std::unique_ptr<ChangeOpen>open;
    std::unique_ptr<ChangeClose>close;

    //オブジェクト用
    Vector3 position = Vector3::Zero;//座標
    Vector3 rotation = Vector3::Zero;//回転
    Vector3 scale = Vector3::Zero;//スケール
    Vector3 velocity = Vector3::Zero;//加速度
    float angle;

public:
    TitleScene(SceneManager* sceneManager);
    ~TitleScene();

    void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, Input* input, Camera* camera) override;

    void Update() override;

    void Draw(DirectXCommon* dxCommon) override;
};

