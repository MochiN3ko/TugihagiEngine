#include "EnemyBullet.h"

EnemyBullet::EnemyBullet(int a)
{
	size = a;//サイズ
	for (int i = 0; i < size; ++i)
	{
		object.emplace_back(new Bullet());
	}
}

EnemyBullet::~EnemyBullet()
{
	for (int i = 0, size = object.size(); i < size; i++)
	{
		delete object[i];
	}
}

void EnemyBullet::Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, UINT texNum)
{
	for (int i = 0, size = object.size(); i < size; i++)
	{
		object[i]->Initialize(dxCommon, textureManager, texNum);//初期化
		object[i]->SetReverseCount(1);//反射回数設定
	}
	a = 0;//発射レート用のカウント
	b = 0;//弾のカウント

	speed = 0.2f;//弾の速度

}

void EnemyBullet::Update(Vector3 p, Player* player)
{
	for (int i = 0, size = object.size(); i < size; i++)
	{
		if (!object[i]->GetLiveFlag())
		{
			//プレイヤーとエネミーの向きを調べる
			Vector3 direction = player->GetPosition() - p;
			Vector3 directionRot = player->GetPosition() - p;
			//正規化
			direction.Normalize();
			//向きを代入
			object[i]->SetVelocity(direction * speed);
			//LiveFlagがFalseの場合は描画しないで指定したポジションに待機
			object[i]->SetPosition(p);
		}
		else
		{
			//弾の向き計算
			float direction = atan2f(object[i]->GetVelocity().z, object[i]->GetVelocity().x);

			object[i]->SetRotation(Vector3(0.0f, direction * -57.325f - 90.0f, 0.0f));
		}
		
		
		object[i]->Update();//オブジェクトの更新処理
		//反射できる回数が0を下回ったら消える
		if (object[i]->GetReverseCount() < 0)
		{
			object[i]->SetLiveFlag(false);//死亡フラグ
			object[i]->SetReverseCount(1);//反射回数リセット
		}
	}
	a++;
	//弾の発射間隔
	b = a / 100;
	//順番に弾を発射する
	if (b < size)
	{
		object[b]->SetLiveFlag(true);
	}
	else
	{
		//bが要素数を超えたらカウントを初期化
		a = 0;
	}

}

void EnemyBullet::Draw(DirectXCommon* dxCommon)
{
	for (int i = 0, size = object.size(); i < size; i++)
	{
		object[i]->Draw(dxCommon);//描画処理
	}
}

void EnemyBullet::Reset()
{
	for (int i = 0, size = object.size(); i < size; i++)
	{
		object[i]->SetLiveFlag(false);//フラグリセット
	}
}
