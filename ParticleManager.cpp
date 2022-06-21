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
	oSize = object.size();
	for (int i = 0; i < oSize; ++i)
	{
		object[i]->Initialize(dxCommon, textureManager, texNum);
		float b = 360 / size * i;
		Vector3 a = Vector3(sin(b), cos(b), 0);
		object[i]->SetVelocity(a);
	}
}

void ParticleManager::Update()
{
	oSize = object.size();
	for (int i = 0; i < oSize; ++i)
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

void ParticleManager::SetPosition(const Vector3& position)
{
	oSize = object.size();
	for (int i = 0; i < oSize; ++i)
	{
		object[i]->SetPosition(Vector3(position.x, position.y, position.z));
	}
}

void ParticleManager::SetLiveFlag(const bool& b)
{
	for (auto& o : object)
	{
		o->SetLiveFlag(b);
	}
}



