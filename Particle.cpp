#include "Particle.h"


Particle::Particle()
{
	object = std::make_unique<Object3d>();
}

Particle::~Particle()
{
}

void Particle::Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, UINT texNum)
{
	object->Initialize(loader->GetModel(Loader::ModelIndex::CUBE));
	scale = Vector3(2, 2, 2);
	liveFlag = true;
	ptime = 0;
}

void Particle::Update()
{
	if (liveFlag)
	{		
		//velocity *= 0.8f;
		position += velocity;
		if (scale.x < 0.0f)
		{
			liveFlag = false;
		}
		ptime++;
	}
	else
	{
		ptime = 0;
	}
	object->Update();
	object->SetPosition(position);
	object->SetRotation(rotation);
	object->SetScale(scale);
}

void Particle::Draw(DirectXCommon* dxCommon)
{
	if (liveFlag)
	{
		object->Draw(dxCommon->GetCommandList());
	}
}
