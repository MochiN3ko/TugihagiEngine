#include "BackGroundObject.h"

BackGroundObject::BackGroundObject()
{
	tank = std::make_unique<Object3d>();
	line = std::make_unique<Object3d>();
}

BackGroundObject::~BackGroundObject()
{
}

void BackGroundObject::Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, UINT texNum)
{
	tank->Initialize(loader->GetModel(Loader::ModelIndex::BGTANK));
	tank->SetColor(color);

	line->Initialize(loader->GetModel(Loader::ModelIndex::CUBE));
	line->SetColor(Vector3::Zero);

	position = Vector3::Zero;
	scale = Vector3(5.0f, 5.0f, 0.0f);
	rotation = Vector3(0.0f, 180.0f, 0.0f);
	velocity = Vector3(1.0f, 0.0f, 0.0f);
}

void BackGroundObject::Update()
{
	tank->SetPosition(position);
	tank->SetRotation(rotation);
	tank->SetScale(scale);
	tank->SetColor(color);
	tank->Update();

	if (right)
	{
		position.x += velocity.x;
		line->SetPosition(position - Vector3(a, -4, -2));
	}
	else
	{
		position.x -= velocity.x;
		line->SetPosition(position + Vector3(a, 3, 2));
	}

	if (lineFlag)
	{
		
		line->SetRotation(Vector3::Zero);
		line->SetScale(Vector3(140.0f, 12.0f, 0.0f));
		line->Update();
	}
}

void BackGroundObject::Draw(DirectXCommon* dxCommon)
{
	if (lineFlag)
	{
		line->Draw(dxCommon->GetCommandList());
	}
	tank->Draw(dxCommon->GetCommandList());
}
