#pragma once
#include "BaseGameObject.h"
#include "Model.h"
#include <DirectXMath.h>
#include "Object3d.h"

class Laser :
	public BaseGameObject
{
private:

	std::unique_ptr<Object3d>object;

public:
	Laser();
	~Laser();
	void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, UINT texNum) override;
	void Update()override;
	void Draw(DirectXCommon* dxCommon)override;

	void SetParent(Object3d* obj) { object->SetParent(obj); }
};