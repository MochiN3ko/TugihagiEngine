#pragma once
#include "BaseScene.h"
#include"SceneManager.h"
#include"Object3d.h"

//�N���A�V�[��
class ClearScene :
    public BaseScene
{
private:
    std::unique_ptr<Object3d>clear;
    std::unique_ptr<Object3d>enter;

    //�I�u�W�F�N�g�p
    Vector3 position = Vector3::Zero;//���W
    Vector3 rotation = Vector3::Zero;//��]
    Vector3 scale = Vector3::Zero;//�X�P�[��
    Vector3 velocity = Vector3::Zero;//�����x
    float angle;

public:
    ClearScene(SceneManager* sceneManager);
    ~ClearScene();

    void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, Input* input, Camera* camera) override;

    void Update() override;

    void Draw(DirectXCommon* dxCommon) override;
};

