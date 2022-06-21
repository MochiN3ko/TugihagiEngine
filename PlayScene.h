#pragma once
#include "BaseScene.h"
#include"SceneManager.h"

#include"Player.h"
#include"Enemy.h"
#include"PauseResume.h"
#include"PauseRestart.h"
#include"PauseTitle.h"
#include"Floor.h"
#include"Ceiling.h"
#include"Wall.h"
#include"Map.h"

//プレイシーン
class PlayScene :
    public BaseScene
{
private:
    //ポーズのswitch文に使うenum
    enum PauseMenu
    {
        RESUME,
        RESTART,
        TITLE,
    };

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

    //ポーズ関連
    std::unique_ptr<PauseResume>pauseResume;//ポーズの再開オブジェクト
    std::unique_ptr<PauseRestart>pauseRestart;//ポーズのやり直しオブジェクト
    std::unique_ptr<PauseTitle>pauseTitle;//ポーズのタイトルに戻るオブジェクト
    bool pause = false;//ポーズのON/OFF切り替え変数
    int pauseNum = 0;//ポーズメニューの切り替え変数

public:
    PlayScene(SceneManager* sceneManager);
    ~PlayScene();

    void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, Input* input, Camera* camera) override;

    void Update() override;

    void Draw(DirectXCommon* dxCommon) override;

    void MapLoad();
};

