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
	for (int i = 0; i < object.size(); i++)
	{
		object[i]->Initialize(dxCommon, textureManager, texNum);
		//サイズをランダムで設定
		float rs = rand() % 10 + 5;
		object[i]->SetScale(Vector3(rs / 15, rs / 15, rs / 15));
		object[i]->SetRotation(Vector3(0,0,10*i));

		object[i]->SetLiveFlag(false);
	}
	a = 0;
	spawn = false;
}

void HitParticle::Update(Vector3 p)
{
	for (int i = 0; i < object.size(); i++)
	{
		object[i]->Update();
		if (object[i]->GetLiveFlag())
		{
			object[i]->SetColor(Vector3(object[i]->GetTime() / 25.0f, 0,0));
			object[i]->SetVelocity(object[i]->GetVelocity() * 0.8f);//速度を減速
		}
		else
		{
			//ポジション指定
			float rndx = rand() % 20 - 10;
			float rndy = rand() % 20 - 10;
			float rndz = rand() % 20 - 10;
			object[i]->SetPosition(p+ Vector3(rndx / 50, rndy / 50, rndz / 50));
			object[i]->SetVelocity(Vector3(rndx / 30, rndy/30 , rndz / 30));
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



