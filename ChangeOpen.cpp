#include "ChangeOpen.h"

ChangeOpen::ChangeOpen()
{
	for(int i = 0; i < TANK_SIZE; ++i)
	{
		redTanks.emplace_back(std::make_unique<BackGroundObject>());
		blueTanks.emplace_back(std::make_unique<BackGroundObject>());
	}
}

ChangeOpen::~ChangeOpen()
{
}

void ChangeOpen::Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, UINT texNum)
{
	redTanks.resize(TANK_SIZE);
	rtSize = redTanks.size();
	for (int i = 0; i < rtSize; ++i)
	{
		redTanks[i]->Initialize(dxCommon, textureManager, 3);
		redTanks[i]->SetPosition(Vector3(-50.0f, 11.0f - (i * 19), 10.0f));
		redTanks[i]->SetColor(Vector3(0.7f, 0.13f, 0.13f));
		redTanks[i]->SetLineFlag(true);
	}

	blueTanks.resize(TANK_SIZE);
	btSize = blueTanks.size();
	for (int i = 0; i < btSize; ++i)
	{
		blueTanks[i]->Initialize(dxCommon, textureManager, 3);
		blueTanks[i]->SetPosition(Vector3(50.0f, 1.0f - (i * 19), 10.0f));
		blueTanks[i]->SetRotation(Vector3::Zero);
		blueTanks[i]->SetColor(Vector3(0.13f, 0.13f, 0.7f));
		blueTanks[i]->SetRightFlag(false);
		blueTanks[i]->SetLineFlag(true);
	}
}

void ChangeOpen::Update()
{
	for (int i = 0; i < rtSize; ++i)
	{
		redTanks[i]->Update();
		//redTanks[i]->SetVelocity(Vector3::Zero);
	}

	for (int i = 0; i < btSize; ++i)
	{
		blueTanks[i]->Update();
		//blueTanks[i]->SetVelocity(Vector3::Zero);
	}
}

void ChangeOpen::Draw(DirectXCommon* dxCommon)
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
