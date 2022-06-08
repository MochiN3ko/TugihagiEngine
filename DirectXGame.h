#pragma once
#include "BaseGame.h"
#include"PostEffect.h"
#include"SceneManager.h"

#include<memory>
#include <algorithm>

class DirectXGame :
    public BaseGame
{
public:
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Finalize() override;
    
private:

    //ポストエフェクト
    std::unique_ptr<PostEffect>postEffect;

    D3D12_GPU_DESCRIPTOR_HANDLE gpuDescHandleCBV;
    D3D12_GPU_DESCRIPTOR_HANDLE gpuDescHandleSRV;
   
    //シーン
    std::unique_ptr<SceneManager>sceneManager;
   
};

