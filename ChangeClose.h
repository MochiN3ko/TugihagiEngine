#pragma once
#include "BaseGameObject.h"
#include "Object3d.h"
#include"BackGroundObject.h"
#include <DirectXMath.h>

class ChangeClose :
    public BaseGameObject
{
private:
	std::vector<std::unique_ptr<BackGroundObject>>redTanks;
	std::vector<std::unique_ptr<BackGroundObject>>blueTanks;

	const int TANK_SIZE = 2;

	size_t rtSize = 0;
	size_t btSize = 0;

public:
	ChangeClose();
	~ChangeClose();
	void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, UINT texNum) override;
	void Update()override;
	void Draw(DirectXCommon* dxCommon)override;

};

