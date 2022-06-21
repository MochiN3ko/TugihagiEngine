#include "FireParticle.h"

FireParticle::FireParticle()
{
	for (int i = 0; i < size; ++i)
	{
		object.emplace_back(new Particle());
	}
}

FireParticle::~FireParticle()
{
	for (const auto& x : object)
	{
		delete x;
	}
}

void FireParticle::Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, UINT texNum)
{
	size_t size = object.size();
	for (int i = 0; i < size; ++i)
	{
		object[i]->Initialize(dxCommon, textureManager, texNum);
		//サイズをランダムで設定
		//float rs = rand() % 10 + 5;
		object[i]->SetScale(Vector3(0.1f, 0.1f, 0.1f));
		object[i]->SetRotation(Vector3(0, 0, 10 * i));

		object[i]->SetLiveFlag(false);
	}
	a = 0;
	spawn = false;
}

void FireParticle::Update(const Vector3& p)
{
	size_t size = object.size();
	for (int i = 0; i < size; ++i)
	{
		object[i]->Update();
		if (object[i]->GetLiveFlag())
		{
			object[i]->SetColor(Vector3(object[i]->GetTime() / 25.0f, object[i]->GetTime() / 25.0f, object[i]->GetTime() / 25.0f));
		}
		else
		{
			//ポジション指定
			float rndx = rand() % 20 - 10;
			float rndy = rand() % 20 - 10;
			//float rndz = rand() % 20 - 10;
			object[i]->SetPosition(p /*+ Vector3(rndx / 50, rndy / 50, 0)*/);
			object[i]->SetVelocity(Vector3(rndx / 30, rndy / 30, 0));
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

void FireParticle::Draw(DirectXCommon* dxCommon)
{
	for (auto& o : object)
	{
		o->Draw(dxCommon);
	}
}





