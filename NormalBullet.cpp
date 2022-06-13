#include "NormalBullet.h"

NormalBullet::NormalBullet(int size)
{
	this->size = size;//弾のサイズ
	for (int i = 0; i < size; ++i)
	{
		object.emplace_back(new Bullet());
	}
}

NormalBullet::~NormalBullet()
{
	oSize = object.size();
	for (int i = 0; i < oSize; ++i)
	{
		delete object[i];
	}
}

void NormalBullet::Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, UINT texNum)
{
	oSize = object.size();
	for (int i = 0; i < oSize; ++i)
	{
		object[i]->Initialize(dxCommon, textureManager, texNum);//初期化
		object[i]->GetObj()->SetColor(Vector3(0.7f, 0.13f, 0.13f));
		object[i]->GetSmoke()->SetRedFlag(true);
		object[i]->SetReverseCount(2);//反射できる回数
	}
	bulletCount = 0;
}

void NormalBullet::Update(const Vector3& position, const Vector3& velocity)
{
	for (int i = 0; i < oSize; ++i)
	{
		if (!object[i]->GetLiveFlag())
		{
			//弾の速さをセット
			object[i]->SetVelocity(velocity);
			//指定したポジションに待機
			object[i]->SetPosition(position);
		}
		else
		{
			//弾の向き計算
			float direction = atan2f(object[i]->GetVelocity().z, object[i]->GetVelocity().x);
			
			object[i]->SetRotation(Vector3(0.0f, direction * -57.325f - 90.0f, 0.0f));
		}
		object[i]->Update();


		//反射できる回数が0を下回ったら消える
		if (object[i]->GetReverseCount() < 0)
		{
			object[i]->SetLiveFlag(false);
			object[i]->SetReverseCount(2);
		}
	}
}

void NormalBullet::Draw(DirectXCommon* dxCommon)
{
	for (int i = 0; i < oSize; ++i)
	{
		object[i]->Draw(dxCommon);
	}
}

void NormalBullet::Fire()
{
	//要素数超えたらカウント初期化
	if (bulletCount >= size)
	{
		bulletCount = 0;
	}
	//順番に発射
	object[bulletCount]->SetLiveFlag(true);
	bulletCount++;
}

void NormalBullet::Reset()
{
	for (int i = 0; i < oSize; ++i)
	{
		object[i]->SetLiveFlag(false);
	}
}
