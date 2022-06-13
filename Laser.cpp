#include "Laser.h"

Laser::Laser()
{
	object = std::make_unique<Object3d>();
}

Laser::~Laser()
{
}

void Laser::Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, UINT texNum)
{
	object->Initialize(loader->GetModel(Loader::ModelIndex::LASER));
	object->SetColor(Vector3(0.7f, 0.13f, 0.13f));
	scale = Vector3(1, 1, 1);
	rotation = Vector3();
	liveFlag = true;
	
}

void Laser::Update()
{
	object->SetPosition(position);
	object->SetRotation(rotation);
	object->SetScale(scale);
	object->Update();

}

void Laser::Draw(DirectXCommon* dxCommon)
{
	if (liveFlag)
	{
		object->Draw(dxCommon->GetCommandList());
	}
}




