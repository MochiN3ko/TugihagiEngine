#include "PauseTitle.h"

PauseTitle::PauseTitle()
{
	object = std::make_unique<Object3d>();
}

PauseTitle::~PauseTitle()
{
}

void PauseTitle::Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, UINT texNum)
{
	object->Initialize(loader->GetModel(Loader::ModelIndex::TITLE));

	object->SetColor(black);

	scale = Vector3(0.5f, 0.5f, 0.5f);
}

void PauseTitle::Update()
{
	object->Update();
	object->SetPosition(position);
	object->SetRotation(rotation);
	object->SetScale(scale);
	if (move)
	{
		object->SetColor(red);
		angle += 0.05f;
		scale += Vector3(sinf(angle) * range, sinf(angle) * range, 0.0f);
	}
	else
	{
		object->SetColor(black);
		angle = 0.0f;
		scale = Vector3(0.5f, 0.5f, 0.5f);
	}
}

void PauseTitle::Draw(DirectXCommon* dxCommon)
{
	object->Draw(dxCommon->GetCommandList());
}

