#include "Loader.h"
Loader::Loader(TextureManager* textureManager)
{
    this->textureManager = textureManager;
    //モデル読み込み
    AddModel(ModelIndex::TURRET, "tankTurret");
    AddModel(ModelIndex::BODY, "tankBody");
    AddModel(ModelIndex::MISSILE, "missile");
    AddModel(ModelIndex::LASER, "laser");
    AddModel(ModelIndex::WALL, "block1");
    AddModel(ModelIndex::CUBE, "cube");
    AddModel(ModelIndex::BGTANK, "bgTank");
    AddModel(ModelIndex::TANKTANK, "tanktank");
    AddModel(ModelIndex::TITLE, "title");
    AddModel(ModelIndex::CLEAR, "clear");
    AddModel(ModelIndex::OVER, "over");
    AddModel(ModelIndex::CONTINUE, "continue");
    AddModel(ModelIndex::RESUME, "resume");
    AddModel(ModelIndex::RESTART, "restart");
    AddModel(ModelIndex::ENTER, "pushtoenter");
    AddModel(ModelIndex::LEFTCLICK, "leftclick");

    //テクスチャ読み込み
    textureManager->LoadTexture(0, L"Resources/black.png");
    textureManager->LoadTexture(1, L"Resources/sprite.png");
    textureManager->LoadTexture(2, L"Resources/reticle.png");
    textureManager->LoadTexture(3, L"Resources/white.png");
    textureManager->LoadTexture(4, L"Resources/wall.png");
    textureManager->LoadTexture(5, L"Resources/floor.png");
    textureManager->LoadTexture(6, L"Resources/blue.png");
}

Loader::~Loader()
{
}

void Loader::AddModel(const ModelIndex& m, std::string filename)
{
    model.emplace_back(std::make_unique<Model>());
    model[static_cast<int>(m)]->LoadModel(filename, false);
}

void Loader::Initialize(DirectXCommon* dxCommon, TextureManager* textureManager)
{
    model[static_cast<int>(ModelIndex::TURRET)]->Initialize(dxCommon, textureManager, 3);
    model[static_cast<int>(ModelIndex::BODY)]->Initialize(dxCommon, textureManager, 3);
    model[static_cast<int>(ModelIndex::MISSILE)]->Initialize(dxCommon, textureManager, 3);
    model[static_cast<int>(ModelIndex::LASER)]->Initialize(dxCommon, textureManager, 3);
    model[static_cast<int>(ModelIndex::WALL)]->Initialize(dxCommon, textureManager, 4);
    model[static_cast<int>(ModelIndex::CUBE)]->Initialize(dxCommon, textureManager, 3);
    model[static_cast<int>(ModelIndex::BGTANK)]->Initialize(dxCommon, textureManager, 3);
    model[static_cast<int>(ModelIndex::TANKTANK)]->Initialize(dxCommon, textureManager, 3);
    model[static_cast<int>(ModelIndex::TITLE)]->Initialize(dxCommon, textureManager, 3);
    model[static_cast<int>(ModelIndex::CLEAR)]->Initialize(dxCommon, textureManager, 3);
    model[static_cast<int>(ModelIndex::OVER)]->Initialize(dxCommon, textureManager, 3);
    model[static_cast<int>(ModelIndex::CONTINUE)]->Initialize(dxCommon, textureManager, 3);
    model[static_cast<int>(ModelIndex::RESUME)]->Initialize(dxCommon, textureManager, 3);
    model[static_cast<int>(ModelIndex::RESTART)]->Initialize(dxCommon, textureManager, 3);
    model[static_cast<int>(ModelIndex::ENTER)]->Initialize(dxCommon, textureManager, 3);
    model[static_cast<int>(ModelIndex::LEFTCLICK)]->Initialize(dxCommon, textureManager, 3);
}

Model* Loader::GetModel(const ModelIndex& modelIndex)
{
    return model[static_cast<int>(modelIndex)].get();
}