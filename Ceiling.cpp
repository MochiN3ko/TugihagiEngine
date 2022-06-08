#include "Ceiling.h"

Player* Ceiling::player;
std::vector<Bullet*> Ceiling::pBullet;

Ceiling::Ceiling()
{
	object = std::make_unique<Object3d>();
}

Ceiling::~Ceiling()
{
	
}

void Ceiling::Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, UINT texNum)
{

	object->Initialize(loader->GetModel(Loader::ModelIndex::WALL));

	scale = Vector3(3.0f, 0.1f, 3.0f);
}

void Ceiling::Update()
{
	if (liveFlag)
	{
		object->Update();

		for (int i = 0, size = pBullet.size(); i < size; i++)
		{
			if (RectangleAndSphere2D(position - scale, position + scale, pBullet[i]->GetPosition() + pBullet[i]->GetVelocity(), pBullet[i]->GetScale().z))
			{
				//ƒoƒEƒ“ƒh
				pBullet[i]->SetVelocity(Vector3(pBullet[i]->GetVelocity().x, pBullet[i]->GetVelocity().y * -1.0f, pBullet[i]->GetVelocity().z));
			}
		}

		object->SetPosition(position);
		object->SetRotation(rotation);
		object->SetScale(scale);
	}
}

void Ceiling::Draw(DirectXCommon* dxCommon)
{
	if (liveFlag)
	{
		object->Draw(dxCommon->GetCommandList());
	}
}



