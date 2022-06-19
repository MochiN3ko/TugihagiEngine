#pragma once
#include "BaseScene.h"
#include"SceneManager.h"

#include"Player.h"
#include"Enemy.h"
#include"Floor.h"
#include"Ceiling.h"
#include"Wall.h"
#include"Map.h"

//�v���C�V�[��
class PlayScene :
    public BaseScene
{
private:

    std::unique_ptr<Player> player;//�v���C���[

    //�G�l�~�[�֘A
    std::vector<std::unique_ptr<Enemy>>enemies;//�G�l�~�[
    std::vector<bool>enemyDead;//�G�l�~�[������ł��邩�̃t���O
    int enemySize = 2;//�G�l�~�[�̗v�f��

    //�}�b�v�֘A
    std::unique_ptr<Map>map;//�}�b�v
    int mapnum = 0;//���݂̃}�b�v�ԍ�
    std::vector<std::unique_ptr<Floor>>floor;//��
    std::vector<std::unique_ptr<Ceiling>>ceiling;//�V��
    std::vector<std::unique_ptr<Wall>> wall;//��

    //�e�I�u�W�F�N�g��size�ۑ��p�ϐ�
    size_t eSize = 0;//�G�l�~�[
    size_t fSize = 0;//�}�b�v�̏�
    size_t cSize = 0;//�}�b�v�̓V��
    size_t wSize = 0;//�}�b�v�̕�

    bool pause = false;

public:
    PlayScene(SceneManager* sceneManager);
    ~PlayScene();

    void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, Input* input, Camera* camera) override;

    void Update() override;

    void Draw(DirectXCommon* dxCommon) override;

    void MapLoad();
};

