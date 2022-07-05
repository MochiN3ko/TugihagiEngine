#include "HitParticle.h"

HitParticle::HitParticle()
{
	for (int i = 0; i < size; ++i)
	{
		object.emplace_back(new Particle());
	}
}

HitParticle::~HitParticle()
{
	for (const auto& x : object)
	{
		delete x;
	}
}

void HitParticle::Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, UINT texNum)
{
	size_t size = object.size();
	for (int i = 0; i < size; ++i)
	{
		object[i]->Initialize(dxCommon, textureManager, texNum);
		//サイズをランダムで設定
		float rs = rand() % 5 + 5;
		object[i]->SetScale(Vector3(rs / 20, rs / 20, rs / 20));
		object[i]->SetRotation(Vector3(0.0f, 0.0f, 10.0f * i));

		object[i]->SetLiveFlag(false);
	}
	a = 0;
	spawn = false;
	red = false;
}

void HitParticle::Update(const Vector3& p)
{
	size_t size = object.size();
	for (int i = 0; i < size; ++i)
	{
		object[i]->Update();
		if (object[i]->GetLiveFlag())
		{
			//カラーの移り変わり
			if (red)
			{
				object[i]->SetColor(Vector3(0.7f, 0.13f, 0.13f));
			}
			else
			{
				object[i]->SetColor(Vector3(0.13f, 0.13f, object[i]->GetTime() / 5.0f));
			}
			object[i]->SetVelocity(object[i]->GetVelocity() * 0.8f);//速度を減速
		}
		else
		{
			//ポジション指定
			float rndx = rand() % 20 - 10;
			float rndy = rand() % 20 - 10;
			float rndz = rand() % 20 - 10;
			object[i]->SetPosition(p + Vector3(rndx / 50, rndy / 50, rndz / 50));
			object[i]->SetVelocity(Vector3(rndx / 30, rndy / 30, rndz / 30));
		}
		if (object[i]->GetTime() > 20)
		{
			object[i]->SetLiveFlag(false);
		}
	}

	if (spawn)
	{
		//順番に煙を出す
		if (a < object.size())
		{
			object[a]->SetLiveFlag(true);
		}
		else
		{
			spawn = false;
			a = 0;
		}
		a++;
	}
}

void HitParticle::Draw(DirectXCommon* dxCommon)
{
	for (auto& o : object)
	{
		o->Draw(dxCommon);
	}
}



