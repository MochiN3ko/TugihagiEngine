#pragma once
#include "BaseScene.h"
#include"SceneManager.h"

#include"Player.h"
#include"Enemy.h"
#include"Floor.h"
#include"Ceiling.h"
#include"Wall.h"
#include"Map.h"

//プレイシーン
class PlayScene :
    public BaseScene
{
private:

    std::unique_ptr<Player> player;//プレイヤー

    //エネミー関連
    std::vector<std::unique_ptr<Enemy>>enemies;//エネミー
    std::vector<bool>enemyDead;//エネミーが死んでいるかのフラグ
    int enemySize = 2;//エネミーの要素数

    //マップ関連
    std::unique_ptr<Map>map;//マップ
    int mapnum = 0;//現在のマップ番号
    std::vector<std::unique_ptr<Floor>>floor;//床
    std::vector<std::unique_ptr<Ceiling>>ceiling;//天井
    std::vector<std::unique_ptr<Wall>> wall;//壁

    //各オブジェクトのsize保存用変数
    size_t eSize = 0;//エネミー
    size_t fSize = 0;//マップの床
    size_t cSize = 0;//マップの天井
    size_t wSize = 0;//マップの壁

    bool pause = false;

public:
    PlayScene(SceneManager* sceneManager);
    ~PlayScene();

    void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, Input* input, Camera* camera) override;

    void Update() override;

    void Draw(DirectXCommon* dxCommon) override;

    void MapLoad();
};

