#include "PlayScene.h"

using namespace DirectX;

PlayScene::PlayScene(SceneManager* sceneManager)
	:BaseScene(sceneManager)
{
}

PlayScene::~PlayScene()
{
	
}

void PlayScene::Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, Input* input, Camera* camera)
{
	//�����ݒ�
	BaseScene::Initialize(dxCommon, textureManager, input, camera);

	//�}�b�v�֘A
	map = std::make_unique<Map>();
	map->Initialize();
	mapnum = 0;

	//�|�X�g�G�t�F�N�g�p�e�N�X�`���̓ǂݍ���
	textureManager->LoadTexture(100, L"Resources/sprite.png");

	//�v���C���[�֘A
	player = std::make_unique<Player>();
	player->Initialize(dxCommon, textureManager, 1);//������

	//�G�l�~�[�֘A
	enemySize = 2;
	enemies.resize(enemySize);//�T�C�Y�w��
	enemyDead.resize(enemySize);//�T�C�Y�w��
	eSize = enemies.size();
	for (int i = 0; i < eSize; ++i)
	{
		enemies[i] = std::make_unique<Enemy>();
		enemies[i]->Initialize(dxCommon, textureManager, 6);//������
		enemyDead[i] = enemies[i]->GetLiveFlag();//flag�̏�Ԃ�ۑ�
	}
	//�}�b�v�֘A
	//���֘A
	floor.resize(map->GetFloorMax());//�T�C�Y�w��
	fSize = floor.size();
	for (int i = 0; i < fSize; ++i)
	{
		floor[i] = std::make_unique<Floor>();
		floor[i]->Initialize(dxCommon, textureManager, 5);//������
	}
	//�V��֘A
	ceiling.resize(map->GetCeilingMax());//�T�C�Y�w��
	cSize = ceiling.size();
	for (int i = 0; i < cSize; ++i)
	{
		ceiling[i] = std::make_unique<Ceiling>();
		ceiling[i]->Initialize(dxCommon, textureManager, 4);//������
	}
	//�Ǌ֘A
	wall.resize(map->GetWallMax());//�T�C�Y�w��
	wSize = wall.size();
	for (int i = 0; i < wSize; ++i)
	{
		wall[i] = std::make_unique<Wall>();
		wall[i]->Initialize(dxCommon, textureManager, 4);//������
	}

	//�}�b�v�ǂݍ���
	MapLoad();

	//�J�����̃|�W�V�����ƃA���O��
	camera->SetTarget(Vector3(0.0f, 0.0f, 0.0f));//�����_
	camera->SetEye(Vector3(0.0f, 0.0f, -10.0f));//���_

	ShowCursor(FALSE);
}

//void PlayScene::Update()
//{
//	//�J�[�\���̈ʒu�Œ�
//	SetCursorPos(1280.0f / 2, 720.0f / 2);
//
//#pragma region �v���C���[�֘A
//
//	//input�����ʉ�
//	Player::SetInput(input);
//	//�v���C���[�̍X�V����
//	player->Update();
//
//#pragma endregion
//
//#pragma region �G�l�~�[�֘A
//
//	//�v���C���[�����ʉ�
//	Enemy::SetPlayer(player.get());
//	//�v���C���[�̒e�����ʉ�
//	Enemy::SetNormalBullet(player->GetNormalBullet()->GetBullet());
//	//�G�l�~�[�̃T�C�Y���J��Ԃ�
//	eSize = enemies.size();
//	for (int i = 0; i < eSize; ++i)
//	{
//		//�G�l�~�[�̍X�V����
//		enemies[i]->Update();
//		//�t���O�z��ɃG�l�~�[�̃t���O����
//		enemyDead[i] = enemies[i]->GetLiveFlag();
//	}
//	//�G�l�~�[������ł��邩����
//	bool result = std::all_of(enemyDead.begin(), enemyDead.end(), [](bool flag) { return flag == false; });
//	
//#pragma endregion
//
//#pragma region �}�b�v�֘A
//	//��
//	//�v���C���[�����ʉ�
//	Floor::SetPlayer(player.get());
//	fSize = map->GetFloor().size();
//	for (int i = 0; i < fSize; ++i)
//	{
//		//���̍X�V����
//		floor[i]->Update();
//	}
//	//�V��
//	//�v���C���[�����ʉ�
//	Ceiling::SetPlayer(player.get());
//	cSize = map->GetCeiling().size();
//	for (int i = 0; i < cSize; ++i)
//	{
//		//�V��̍X�V����
//		ceiling[i]->Update();
//	}
//	//��
//	//�v���C���[�����ʉ�
//	Wall::SetPlayer(player.get());
//	//�v���C���[�̒e�����ʉ�
//	Wall::SetNormalBullet(player->GetNormalBullet()->GetBullet());
//	wSize = map->GetWall().size();
//	eSize = enemies.size();
//	for (int i = 0; i < wSize; ++i)
//	{
//		//�e�̋��ʉ�
//		for (int j = 0; j < eSize; ++j)
//		{
//			wall[i]->WallBulletHit(enemies[j]->GetNEnemyBullet()->GetBullet());
//		}
//		//�ǂ̍X�V����
//		wall[i]->Update();
//	}
//
//#pragma endregion
//
//	//�J�����̃|�W�V�����ƃA���O��
//	camera->SetTarget(Vector3(player->GetPlayerTarget().x, player->GetPlayerTarget().y, player->GetPlayerTarget().z));//�����_
//	camera->SetEye(Vector3(player->GetPlayerEye().x, player->GetPlayerEye().y, player->GetPlayerEye().z));//���_
//
//	//�v���C���[�����񂾂�Q�[���I�[�o�[
//	if (!player->GetLiveFlag())
//	{
//		sceneManager_->SetNextScene(new OverScene(sceneManager_));
//	}
//	//�G�l�~�[���S������ł�����N���A
//	else if (result)
//	{
//		sceneManager_->SetNextScene(new ClearScene(sceneManager_));
//	}
//	//�G�X�P�[�v�Ń^�C�g��
//	else if (input->TriggerKey(DIK_ESCAPE))
//	{
//		sceneManager_->SetNextScene(new TitleScene(sceneManager_));
//	}
//}

void PlayScene::Update()
{
	//�J�[�\���̈ʒu�Œ�
	SetCursorPos(1280.0f / 2, 720.0f / 2);
	if (!pause)
	{
#pragma region �v���C���[�֘A

		//input�����ʉ�
		Player::SetInput(input);
		//�v���C���[�̍X�V����
		player->Update();

#pragma endregion

#pragma region �G�l�~�[�֘A

		//�v���C���[�����ʉ�
		Enemy::SetPlayer(player.get());
		//�v���C���[�̒e�����ʉ�
		Enemy::SetNormalBullet(player->GetNormalBullet()->GetBullet());
		//�G�l�~�[�̃T�C�Y���J��Ԃ�
		eSize = enemies.size();
		for (int i = 0; i < eSize; ++i)
		{
			//�G�l�~�[�̍X�V����
			enemies[i]->Update();
			//�t���O�z��ɃG�l�~�[�̃t���O����
			enemyDead[i] = enemies[i]->GetLiveFlag();
		}
		//�G�l�~�[������ł��邩����
		bool result = std::all_of(enemyDead.begin(), enemyDead.end(), [](bool flag) { return flag == false; });

#pragma endregion

#pragma region �}�b�v�֘A
		//��
		//�v���C���[�����ʉ�
		Floor::SetPlayer(player.get());
		fSize = map->GetFloor().size();
		for (int i = 0; i < fSize; ++i)
		{
			//���̍X�V����
			floor[i]->Update();
		}
		//�V��
		//�v���C���[�����ʉ�
		Ceiling::SetPlayer(player.get());
		cSize = map->GetCeiling().size();
		for (int i = 0; i < cSize; ++i)
		{
			//�V��̍X�V����
			ceiling[i]->Update();
		}
		//��
		//�v���C���[�����ʉ�
		Wall::SetPlayer(player.get());
		//�v���C���[�̒e�����ʉ�
		Wall::SetNormalBullet(player->GetNormalBullet()->GetBullet());
		wSize = map->GetWall().size();
		eSize = enemies.size();
		for (int i = 0; i < wSize; ++i)
		{
			//�e�̋��ʉ�
			for (int j = 0; j < eSize; ++j)
			{
				wall[i]->WallBulletHit(enemies[j]->GetNEnemyBullet()->GetBullet());
			}
			//�ǂ̍X�V����
			wall[i]->Update();
		}

#pragma endregion

		//�J�����̃|�W�V�����ƃA���O��
		camera->SetTarget(Vector3(player->GetPlayerTarget().x, player->GetPlayerTarget().y, player->GetPlayerTarget().z));//�����_
		camera->SetEye(Vector3(player->GetPlayerEye().x, player->GetPlayerEye().y, player->GetPlayerEye().z));//���_

		if (input->TriggerKey(DIK_SPACE))
		{
			if (!pause)
			{
				pause = true;
			}
		}

		//�v���C���[�����񂾂�Q�[���I�[�o�[
		if (!player->GetLiveFlag())
		{
			sceneManager_->SetNextScene(new OverScene(sceneManager_));
		}
		//�G�l�~�[���S������ł�����N���A
		else if (result)
		{
			sceneManager_->SetNextScene(new ClearScene(sceneManager_));
		}
		//�G�X�P�[�v�Ń^�C�g��
		else if (input->TriggerKey(DIK_ESCAPE))
		{
			sceneManager_->SetNextScene(new TitleScene(sceneManager_));
		}
	}
	else
	{
		if (input->TriggerKey(DIK_SPACE))
		{
			if (pause)
			{
				pause = false;
			}
		}
	}

}

void PlayScene::Draw(DirectXCommon* dxCommon)
{
	//��
	fSize = floor.size();
	for (int i = 0; i < fSize; ++i)
	{
		floor[i]->Draw(dxCommon);
	}
	//�V��
	cSize = ceiling.size();
	for (int i = 0; i < cSize; ++i)
	{
		ceiling[i]->Draw(dxCommon);
	}
	//��
	wSize = wall.size();
	for (int i = 0; i < wSize; ++i)
	{
		wall[i]->Draw(dxCommon);
	}
	//�G�l�~�[
	eSize = enemies.size();
	for (int i = 0; i < eSize; ++i)
	{
		enemies[i]->Draw(dxCommon);
	}
	//�v���C���[
	player->Draw(dxCommon);
}

void PlayScene::MapLoad()
{
	//�}�b�v�ǂݍ���
	map->SetNowMap(mapnum);

#pragma region �I�u�W�F�N�g�̃|�W�V�����w��

	//�v���C���[
	player->SetPosition(map->GetPlayerPosition());
	player->SetLiveFlag(true);
	player->SetVelocity(Vector3::Zero);
	player->Reset();

	//�G�l�~�[
	//�m�[�}���G�l�~�[
	eSize = map->GetNEnemy().size();
	for (int i = 0; i < eSize; ++i)
	{
		enemies[i]->SetPosition(map->GetNEnemy()[i]);
		enemies[i]->SetLiveFlag(true);
		enemies[i]->Reset();
		enemyDead[i] = enemies[i]->GetLiveFlag();//flag�̏�Ԃ�ۑ�
	}
	//��
	fSize = map->GetFloor().size();
	for (int i = 0; i < fSize; ++i)
	{
		floor[i]->SetLiveFlag(true);
		floor[i]->SetPosition(map->GetFloor()[i]);
	}
	//�V��
	cSize = map->GetCeiling().size();
	for (int i = 0; i < cSize; ++i)
	{
		ceiling[i]->SetLiveFlag(true);
		ceiling[i]->SetPosition(map->GetCeiling()[i]);
	}
	//��
	wSize = map->GetWall().size();
	for (int i = 0; i < wSize; ++i)
	{
		wall[i]->SetLiveFlag(true);
		wall[i]->SetPosition(map->GetWall()[i]);
	}

#pragma endregion
}
