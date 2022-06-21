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
        TANKTANK,
        TITLE,
        CLEAR,
        OVER,
        CONTINUE,
        RESUME,
        RESTART,
        ENTER,
    };

private:

    std::vector<std::unique_ptr<Model>> model;
    TextureManager* textureManager;

    void AddModel(const ModelIndex& m, std::string filename);

public:
    Loader(TextureManager* textureManager);
    ~Loader();
    void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager);
    Model* GetModel(const ModelIndex& modelIndex);

};

