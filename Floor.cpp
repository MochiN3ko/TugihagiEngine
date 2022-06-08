#include "Floor.h"

Player* Floor::player;
std::vector<Bullet*> Floor::pBullet;

Floor::Floor()
{
	object = std::make_unique<Object3d>();
}

Floor::~Floor()
{
}

void Floor::Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, UINT texNum)
{
	object->Initialize(loader->GetModel(Loader::ModelIndex::WALL));

	scale = Vector3(3.0f, 0.1f, 3.0f);
}

void Floor::Update()
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

void Floor::Draw(DirectXCommon* dxCommon)
{
	if (liveFlag)
	{
		object->Draw(dxCommon->GetCommandList());
	}
}


