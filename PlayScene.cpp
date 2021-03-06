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
	//初期設定
	BaseScene::Initialize(dxCommon, textureManager, input, camera);

	//マップ関連
	map = std::make_unique<Map>();
	map->Initialize();
	mapnum = 0;

	//ポストエフェクト用テクスチャの読み込み
	textureManager->LoadTexture(100, L"Resources/sprite.png");

	//プレイヤー関連
	player = std::make_unique<Player>();
	player->Initialize(dxCommon, textureManager, 3);//初期化

	//エネミー関連
	enemySize = 2;
	enemies.resize(enemySize);//サイズ指定
	enemyDead.resize(enemySize);//サイズ指定
	eSize = enemies.size();
	for (int i = 0; i < eSize; ++i)
	{
		enemies[i] = std::make_unique<Enemy>();;
		enemies[i]->Initialize(dxCommon, textureManager, 3);//初期化
		enemyDead[i] = enemies[i]->GetLiveFlag();//flagの状態を保存
	}
	//マップ関連
	//床関連
	floor.resize(map->GetFloorMax());//サイズ指定
	fSize = floor.size();
	for (int i = 0; i < fSize; ++i)
	{
		floor[i] = std::make_unique<Floor>();
		floor[i]->Initialize(dxCommon, textureManager, 5);//初期化
	}
	//天井関連
	ceiling.resize(map->GetCeilingMax());//サイズ指定
	cSize = ceiling.size();
	for (int i = 0; i < cSize; ++i)
	{
		ceiling[i] = std::make_unique<Ceiling>();
		ceiling[i]->Initialize(dxCommon, textureManager, 4);//初期化
	}
	//壁関連
	wall.resize(map->GetWallMax());//サイズ指定
	wSize = wall.size();
	for (int i = 0; i < wSize; ++i)
	{
		wall[i] = std::make_unique<Wall>();
		wall[i]->Initialize(dxCommon, textureManager, 4);//初期化
	}

	//ポーズ関連
	pauseResume = std::make_unique<PauseResume>();
	pauseResume->Initialize(dxCommon, textureManager, 3);
	pauseRestart = std::make_unique<PauseRestart>();
	pauseRestart->Initialize(dxCommon, textureManager, 3);
	pauseTitle = std::make_unique<PauseTitle>();
	pauseTitle->Initialize(dxCommon, textureManager, 3);

	//マップ読み込み
	MapLoad();

	//カメラのポジションとアングル
	camera->SetTarget(Vector3(0.0f, 0.0f, 0.0f));//注視点
	camera->SetEye(Vector3(0.0f, 0.0f, -10.0f));//視点

	ShowCursor(FALSE);
}

void PlayScene::Update()
{
	//カーソルの位置固定
	SetCursorPos(1280.0f / 2, 720.0f / 2);
	if (!pause)
	{
#pragma region プレイヤー関連

		//inputを共通化
		Player::SetInput(input);
		//プレイヤーの更新処理
		player->Update();

#pragma endregion

#pragma region エネミー関連

		//プレイヤーを共通化
		Enemy::SetPlayer(player.get());
		//プレイヤーの弾を共通化
		Enemy::SetNormalBullet(player->GetNormalBullet()->GetBullet());
		//エネミーのサイズ分繰り返す
		eSize = enemies.size();
		for (int i = 0; i < eSize; ++i)
		{
			//エネミーの更新処理
			enemies[i]->Update();
			//フラグ配列にエネミーのフラグを代入
			enemyDead[i] = enemies[i]->GetLiveFlag();
		}

#pragma endregion

#pragma region マップ関連
		//床
		//プレイヤーを共通化
		Floor::SetPlayer(player.get());
		fSize = map->GetFloor().size();
		for (int i = 0; i < fSize; ++i)
		{
			//床の更新処理
			floor[i]->Update();
		}
		//天井
		//プレイヤーを共通化
		Ceiling::SetPlayer(player.get());
		cSize = map->GetCeiling().size();
		for (int i = 0; i < cSize; ++i)
		{
			//天井の更新処理
			ceiling[i]->Update();
		}
		//壁
		//プレイヤーを共通化
		Wall::SetPlayer(player.get());
		//プレイヤーの弾を共通化
		Wall::SetNormalBullet(player->GetNormalBullet()->GetBullet());
		wSize = map->GetWall().size();
		eSize = enemies.size();
		for (int i = 0; i < wSize; ++i)
		{
			//弾の共通化
			for (int j = 0; j < eSize; ++j)
			{
				wall[i]->WallBulletHit(enemies[j]->GetNEnemyBullet()->GetBullet());
			}
			//壁の更新処理
			wall[i]->Update();
		}

#pragma endregion

		//カメラのポジションとアングル
		camera->SetTarget(Vector3(player->GetPlayerTarget().x, player->GetPlayerTarget().y, player->GetPlayerTarget().z));//注視点
		camera->SetEye(Vector3(player->GetPlayerEye().x, player->GetPlayerEye().y, player->GetPlayerEye().z));//視点

		//ポーズメニューの数値の初期化
		pauseNum = 0;

		//エスケープでポーズ
		if (input->TriggerKey(DIK_ESCAPE))
		{
			if (!pause)
			{
				pause = true;
			}
		}
	}
	//ポーズ中
	else
	{
		pauseResume->Update();
		pauseRestart->Update();
		pauseTitle->Update();

		pauseResume->SetPosition(Vector3(player->GetPosition().x, player->GetPosition().y + 0.7f, player->GetPosition().z - 1.0f));
		pauseRestart->SetPosition(Vector3(player->GetPosition().x, player->GetPosition().y + 0.3f, player->GetPosition().z - 1.0f));
		pauseTitle->SetPosition(Vector3(player->GetPosition().x, player->GetPosition().y - 0.1f, player->GetPosition().z - 1.0f));

		//ポーズメニューの選択処理
		if (input->TriggerKey(DIK_UP))
		{
			pauseNum--;
		}
		else if (input->TriggerKey(DIK_DOWN))
		{
			pauseNum++;
		}

		//範囲指定
		if (pauseNum > 2)
		{
			pauseNum = 0;
		}
		else if (pauseNum < 0)
		{
			pauseNum = 2;
		}

		//ポーズ切り替え
		switch (pauseNum)
		{
		case RESUME://再開
			
			pauseResume->SetMoveFlag(true);
			pauseRestart->SetMoveFlag(false);
			pauseTitle->SetMoveFlag(false);

			//Enterでポーズ解除
			if (input->TriggerKey(DIK_RETURN))
			{
				pause = false;
			}

			break;
		case RESTART://やり直し

			pauseResume->SetMoveFlag(false);
			pauseRestart->SetMoveFlag(true);
			pauseTitle->SetMoveFlag(false);

			break;
		case TITLE://タイトルに戻る

			pauseResume->SetMoveFlag(false);
			pauseRestart->SetMoveFlag(false);
			pauseTitle->SetMoveFlag(true);

			break;
		default:
			break;
		}

		//ポーズ解除
		if (input->TriggerKey(DIK_SPACE))
		{
			if (pause)
			{
				pause = false;
			}
		}
	}
	//エネミーが全滅しているか走査
	bool result = std::all_of(enemyDead.begin(), enemyDead.end(), [](bool flag) { return flag == false; });

	//シーン切り替え
	//プレイヤーが死んだらゲームオーバー
	if (!player->GetLiveFlag())
	{
		sceneManager_->SetNextScene(new OverScene(sceneManager_));
	}
	//エネミーが全部死んでいたらゲームクリア
	else if (result)
	{
		sceneManager_->SetNextScene(new ClearScene(sceneManager_));
	}
	//ポーズ時のシーン切り替え
	switch (pauseNum)
	{
	case RESUME://再開
		break;
	case RESTART://やり直し
		if (input->TriggerKey(DIK_RETURN))
		{
			sceneManager_->SetNextScene(new PlayScene(sceneManager_));
		}
		break;
	case TITLE://タイトルに戻る
		if (input->TriggerKey(DIK_RETURN))
		{
			sceneManager_->SetNextScene(new TitleScene(sceneManager_));
		}
		break;
	default:
		break;
	}

}

void PlayScene::Draw(DirectXCommon* dxCommon)
{
	//床
	fSize = floor.size();
	for (int i = 0; i < fSize; ++i)
	{
		floor[i]->Draw(dxCommon);
	}
	//天井
	cSize = ceiling.size();
	for (int i = 0; i < cSize; ++i)
	{
		ceiling[i]->Draw(dxCommon);
	}
	//壁
	wSize = wall.size();
	for (int i = 0; i < wSize; ++i)
	{
		wall[i]->Draw(dxCommon);
	}
	//エネミー
	eSize = enemies.size();
	for (int i = 0; i < eSize; ++i)
	{
		enemies[i]->Draw(dxCommon);
	}
	//プレイヤー
	player->Draw(dxCommon);

	if (pause)
	{
		pauseResume->Draw(dxCommon);
		pauseRestart->Draw(dxCommon);
		pauseTitle->Draw(dxCommon);
	}
}

void PlayScene::MapLoad()
{
	//マップ読み込み
	map->SetNowMap(mapnum);

#pragma region オブジェクトのポジション指定

	//プレイヤー
	player->SetPosition(map->GetPlayerPosition());
	player->SetLiveFlag(true);
	player->SetVelocity(Vector3::Zero);
	player->Reset();

	//エネミー
	//ノーマルエネミー
	eSize = map->GetNEnemy().size();
	for (int i = 0; i < eSize; ++i)
	{
		enemies[i]->SetPosition(map->GetNEnemy()[i]);
		enemies[i]->SetLiveFlag(true);
		enemies[i]->Reset();
		enemyDead[i] = enemies[i]->GetLiveFlag();//flagの状態を保存
	}
	//床
	fSize = map->GetFloor().size();
	for (int i = 0; i < fSize; ++i)
	{
		floor[i]->SetLiveFlag(true);
		floor[i]->SetPosition(map->GetFloor()[i]);
	}
	//天井
	cSize = map->GetCeiling().size();
	for (int i = 0; i < cSize; ++i)
	{
		ceiling[i]->SetLiveFlag(true);
		ceiling[i]->SetPosition(map->GetCeiling()[i]);
	}
	//壁
	wSize = map->GetWall().size();
	for (int i = 0; i < wSize; ++i)
	{
		wall[i]->SetLiveFlag(true);
		wall[i]->SetPosition(map->GetWall()[i]);
	}

#pragma endregion
}
