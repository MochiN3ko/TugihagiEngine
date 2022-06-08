#include "Back.h"

Model* Back::model = nullptr;
Back::Back()
{
	model = new Model();
	object = new Object3d();
}
Back::~Back()
{
	delete object;
}
void Back::StaticLoad(std::string filename)
{
	model->LoadModel(filename, false);
}
void Back::StaticFinalize()
{
	delete model;
}
void Back::Load(std::string filename)
{
}
void Back::Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, UINT texNum)
{
	model->Initialize(dxCommon, textureManager, texNum);

	object->Initialize(model);

	scale = Vector3(1, 1, 1);
}

void Back::Update()
{
	if (liveFlag)
	{
		object->Update();
#pragma region

#pragma endregion

		object->SetPosition(position);
		object->SetRotation(rotation);
		object->SetScale(scale);
	}
}
void Back::Draw(DirectXCommon* dxCommon)
{
	if (liveFlag)
	{
		object->Draw(dxCommon->GetCommandList());
	}
}
