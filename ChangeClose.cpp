#include "ChangeClose.h"

ChangeClose::ChangeClose()
{
	for (int i = 0; i < TANK_SIZE; ++i)
	{
		redTanks.emplace_back(std::make_unique<BackGroundObject>());
		blueTanks.emplace_back(std::make_unique<BackGroundObject>());
	}
}

ChangeClose::~ChangeClose()
{
}

void ChangeClose::Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, UINT texNum)
{
	redTanks.resize(TANK_SIZE);
	rtSize = redTanks.size();
	for (int i = 0; i < rtSize; ++i)
	{
		redTanks[i]->Initialize(dxCommon, textureManager, 3);
		redTanks[i]->SetPosition(Vector3(50.0f, 11.0f - (i * 19), 30.0f));
		redTanks[i]->SetRotation(Vector3::Zero);
		redTanks[i]->SetColor(Vector3(0.7f, 0.13f, 0.13f));
		redTanks[i]->SetRightFlag(false);
	}

	blueTanks.resize(TANK_SIZE);
	btSize = blueTanks.size();
	for (int i = 0; i < btSize; ++i)
	{
		blueTanks[i]->Initialize(dxCommon, textureManager, 3);
		blueTanks[i]->SetPosition(Vector3(-50.0f, 1.0f - (i * 19), 30.0f));
		blueTanks[i]->SetColor(Vector3(0.13f, 0.13f, 0.7f));
	}
}

void ChangeClose::Update()
{
	for (int i = 0; i < rtSize; ++i)
	{
		redTanks[i]->Update();
	}

	for (int i = 0; i < btSize; ++i)
	{
		blueTanks[i]->Update();
	}
}

void ChangeClose::Draw(DirectXCommon* dxCommon)
{
	for (int i = 0; i < rtSize; ++i)
	{
		redTanks[i]->Draw(dxCommon);
	}

	for (int i = 0; i < btSize; ++i)
	{
		blueTanks[i]->Draw(dxCommon);
	}
}

