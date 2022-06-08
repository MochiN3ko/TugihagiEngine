#include "Wall.h"

Player* Wall::player;
std::vector<Bullet*> Wall::pBullet;

Wall::Wall()
{
	object = std::make_unique<Object3d>();
}

Wall::~Wall()
{
}

void Wall::Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, UINT texNum)
{
	object->Initialize(loader->GetModel(Loader::ModelIndex::WALL));

	scale = Vector3(3.0f, 6.0f, 3.0f);
}

void Wall::Update()
{
	if (liveFlag)
	{
		object->Update();
		object->SetPosition(position);
		object->SetRotation(rotation);
		object->SetScale(scale);

		//壁とプレイヤーの当たり判定
		if (RectangleAndSphere2D(position - scale, position + scale, player->GetPosition() + player->GetVelocity(), player->GetScale().z))
		{
			player->SetPosition(Vector3(player->GetPosition().x - player->GetVelocity().x, player->GetPosition().y, player->GetPosition().z - player->GetVelocity().z));
		}
		//壁とプレイヤーの普通の弾の当たり判定
		WallBulletHit(pBullet);
	}
}

void Wall::WallBulletHit(const std::vector<Bullet*> bullet)
{
	//壁と弾の当たり判定
	for (int i = 0, size = bullet.size(); i < size; i++)
	{
		if (bullet[i]->GetLiveFlag())
		{
			//弾の右側の当たり判定
			if (RectangleAndSphere2D(position - scale, position + scale, bullet[i]->GetRightPoint() + bullet[i]->GetVelocity(), bullet[i]->GetPointSize()))
			{
				//バウンド
				bullet[i]->SetVelocity(Vector3(bullet[i]->GetVelocity().x * -1.0f, bullet[i]->GetVelocity().y, bullet[i]->GetVelocity().z));
				//反射できる回数を減らす
				bullet[i]->Counting();
			}
			//弾の左側の当たり判定
			if (RectangleAndSphere2D(position - scale, position + scale, bullet[i]->GetLeftPoint() + bullet[i]->GetVelocity(), bullet[i]->GetPointSize()))
			{
				//バウンド
				bullet[i]->SetVelocity(Vector3(bullet[i]->GetVelocity().x * -1.0f, bullet[i]->GetVelocity().y, bullet[i]->GetVelocity().z));
				//反射できる回数を減らす
				bullet[i]->Counting();
			}
			//弾の前側の当たり判定
			if (RectangleAndSphere2D(position - scale, position + scale, bullet[i]->GetFrontPoint() + bullet[i]->GetVelocity(), bullet[i]->GetPointSize()))
			{
				//バウンド
				bullet[i]->SetVelocity(Vector3(bullet[i]->GetVelocity().x, bullet[i]->GetVelocity().y, bullet[i]->GetVelocity().z * -1.0f));
				//反射できる回数を減らす
				bullet[i]->Counting();
			}
			//弾の後ろ側の当たり判定
			if (RectangleAndSphere2D(position - scale, position + scale, bullet[i]->GetBehindPoint() + bullet[i]->GetVelocity(), bullet[i]->GetPointSize()))
			{
				//バウンド
				bullet[i]->SetVelocity(Vector3(bullet[i]->GetVelocity().x, bullet[i]->GetVelocity().y, bullet[i]->GetVelocity().z * -1.0f));
				//反射できる回数を減らす
				bullet[i]->Counting();
			}
		}
	}
}

void Wall::Draw(DirectXCommon* dxCommon)
{
	if (liveFlag)
	{
		object->Draw(dxCommon->GetCommandList());
	}
}

