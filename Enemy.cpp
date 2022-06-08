#include "Enemy.h"
#include<time.h>

Player* Enemy::player = nullptr;
std::vector<Bullet*> Enemy::pBullet;

Enemy::Enemy()
{
	turretObj = std::make_unique<Object3d>();
	bodyObj = std::make_unique<Object3d>();
	eBullet = std::make_unique<EnemyBullet>(5);
	hitParticle = std::make_unique<HitParticle>();
}

Enemy::~Enemy()
{
}

void Enemy::Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, UINT texNum)
{
	turretObj->Initialize(loader->GetModel(Loader::ModelIndex::TURRET));//戦車の砲塔のオブジェクトの初期化
	turretObj->SetColor(Vector3(0.0f, 0.0f, 1.0f));

	bodyObj->Initialize(loader->GetModel(Loader::ModelIndex::BODY));//戦車の車体のオブジェクトの初期化
	bodyObj->SetColor(Vector3(0.0f, 0.0f, 1.0f));

	scale = Vector3(0.6f, 0.6f, 0.6f);//オブジェクトのサイズ
	adjustment = Vector3(0.0f, -0.4f, 0.0f);//位置調整
	reverseCount = 0;

	position = Vector3::Zero;//位置設定
	velocity = Vector3(0.05f, 0.0f, 0.0f);//移動速度の初期値
	eBullet->Initialize(dxCommon, textureManager, texNum);//弾の初期化
	hitParticle->Initialize(dxCommon, textureManager, texNum);//当たった際のパーティクルの初期化
}

void Enemy::Update()
{
	if (liveFlag)
	{
		Vector3 direction = player->GetPosition() - position;
		rotation.y = rotation.y = atan2f(direction.z, direction.x) * (-57.325f) + 180.0f;
		//戦車の砲塔の処理
		turretObj->Update();//更新処理
		turretObj->SetPosition(position + adjustment);//位置の更新
		turretObj->SetRotation(rotation);//回転の更新
		turretObj->SetScale(scale);//サイズの更新
		//戦車の車体の処理
		bodyObj->Update();//更新処理
		bodyObj->SetPosition(position + adjustment);//位置の更新
		bodyObj->SetRotation(Vector3(0.0f, 0.0f, 0.0f));//回転の更新
		bodyObj->SetScale(scale);//サイズの更新

		Hit();//当たり判定関数
		position += velocity;//移動処理
		reverseCount++;
		//カウントが一定数たったら反転
		if (reverseCount >= 150)
		{
			velocity.x *= -1.0f;
			reverseCount = 0;
		}
		
		eBullet->Update(position, player);//弾の更新処理
	}
	hitParticle->Update(position);//当たった際のパーティクルの更新処理
}

void Enemy::Draw(DirectXCommon* dxCommon)
{
	if (liveFlag)
	{
		turretObj->Draw(dxCommon->GetCommandList());//戦車の砲塔の描画
		bodyObj->Draw(dxCommon->GetCommandList());//戦車の車体の描画
		eBullet->Draw(dxCommon);//弾の描画
	}
	hitParticle->Draw(dxCommon);//当たった際のパーティクルの描画
}

void Enemy::Hit()
{
	//敵とプレイヤーの普通の弾の当たり判定
	for (int i = 0, size = pBullet.size(); i < size; i++)
	{
		if (pBullet[i]->GetLiveFlag())
		{
			if (SphereAndSphere(position, pBullet[i]->GetPosition(), scale.z, pBullet[i]->GetScale().z))
			{
				//soundManager->PlayWave("Resources/sound/hit2.wav");

				//当たった玉を消す
				pBullet[i]->SetLiveFlag(false);
				//エフェクト
				hitParticle->SetSpawnFlag(true);
				//敵が消える
				liveFlag = false;
			}
		}
	}
	//敵の弾とプレイヤー
	for (int i = 0, size = eBullet->GetBullet().size(); i < size; i++)
	{
		if (eBullet->GetBullet()[i]->GetLiveFlag())
		{
			if (SphereAndSphere(player->GetPosition(), eBullet->GetBullet()[i]->GetPosition(), player->GetScale().x, eBullet->GetBullet()[i]->GetScale().y))
			{
				//soundManager->PlayWave("Resources/sound/hit2.wav");

				//当たった玉を消す
				eBullet->GetBullet()[i]->SetLiveFlag(false);
				eBullet->GetBullet()[i]->SetPosition(position);
				//プレイヤーの体力を減らす
				//player->SetHp(player->GetHp() - 1);
				player->Damage();
			}
		}
	}
}

void Enemy::Reset()
{
	eBullet->Reset();
}


