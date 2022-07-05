#pragma once
#include "DirectXCommon.h"
#include "TextureManager.h"
#include"Model.h"

class Loader
{
public:

    enum class ModelIndex
    {
        TURRET,
        BODY,
        MISSILE,
        LASER,
        WALL,
        CUBE,
        BGTANK,
        TANKTANK,
        TITLE,
        CLEAR,
        OVER,
        CONTINUE,
        RESUME,
        RESTART,
        ENTER,
        LEFTCLICK,
    };

private:

    std::vector<std::unique_ptr<Model>> model;
    TextureManager* textureManager = nullptr;

    void AddModel(const ModelIndex& m, std::string filename);

public:
    Loader(TextureManager* textureManager);
    ~Loader();
    void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager);
    Model* GetModel(const ModelIndex& modelIndex);

};

