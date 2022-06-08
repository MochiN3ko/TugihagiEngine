#include "ParticleManager.h"

ParticleManager::ParticleManager()
{
	for (int i = 0; i < size; ++i)
	{
		object.emplace_back(new Particle());
	}
}

ParticleManager::~ParticleManager()
{
	for (const auto& x : object)
	{
		delete x;
	}
}

void ParticleManager::Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, UINT texNum)
{
	for (int i = 0; i < object.size(); i++)
	{
		object[i]->Initialize(dxCommon, textureManager, texNum);
		float b = 360 / size * i;
		Vector3 a = Vector3(sin(b), cos(b), 0);
		object[i]->SetVelocity(a);
	}
}

void ParticleManager::Update()
{
	for (int i = 0; i < object.size(); i++)
	{
		object[i]->Update();
		//object[i]->SetScale(object[i]->GetScale()-);
	}
}

void ParticleManager::Draw(DirectXCommon* dxCommon)
{
	for (auto& o : object)
	{
		o->Draw(dxCommon);
	}
}

void ParticleManager::SetPosition(Vector3 position)
{
	for (int i = 0; i < object.size(); ++i)
	{
		object[i]->SetPosition(Vector3(position.x, position.y, position.z));
	}
}

void ParticleManager::SetLiveFlag(bool b)
{
	for (auto& o : object)
	{
		o->SetLiveFlag(b);
	}
}

//void ParticleManager::SetTarget(Vector3 p)
//{
//	for (auto& o : object)
//	{
//		o->SetTarget(p);
//	}
//}


