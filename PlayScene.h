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

//�v���C�V�[��
class PlayScene :
    public BaseScene
{
private:
    //�|�[�Y��switch���Ɏg��enum
    enum PauseMenu
    {
        RESUME,
        RESTART,
        TITLE,
    };

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

    //�|�[�Y�֘A
    std::unique_ptr<PauseResume>pauseResume;//�|�[�Y�̍ĊJ�I�u�W�F�N�g
    std::unique_ptr<PauseRestart>pauseRestart;//�|�[�Y�̂�蒼���I�u�W�F�N�g
    std::unique_ptr<PauseTitle>pauseTitle;//�|�[�Y�̃^�C�g���ɖ߂�I�u�W�F�N�g
    bool pause = false;//�|�[�Y��ON/OFF�؂�ւ��ϐ�
    int pauseNum = 0;//�|�[�Y���j���[�̐؂�ւ��ϐ�

public:
    PlayScene(SceneManager* sceneManager);
    ~PlayScene();

    void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, Input* input, Camera* camera) override;

    void Update() override;

    void Draw(DirectXCommon* dxCommon) override;

    void MapLoad();
};

