#pragma once
#include "BaseScene.h"
#include"SceneManager.h"
#include"Object3d.h"
#include<vector>

//�^�C�g���V�[��
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

    //�I�u�W�F�N�g�p
    Vector3 position = Vector3::Zero;//���W
    Vector3 rotation = Vector3::Zero;//��]
    Vector3 scale = Vector3::Zero;//�X�P�[��
    Vector3 velocity = Vector3::Zero;//�����x
    float angle;

public:
    TitleScene(SceneManager* sceneManager);
    ~TitleScene();

    void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, Input* input, Camera* camera) override;

    void Update() override;

    void Draw(DirectXCommon* dxCommon) override;
};

