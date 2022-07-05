#pragma once
#include "BaseGameObject.h"
#include"Object3d.h"

class BackGroundObject :
    public BaseGameObject
{
private:

	std::unique_ptr<Object3d>tank;//戦車のオブジェクト
	std::unique_ptr<Object3d>line;
	bool right = true;
	bool lineFlag = false;
	float a = 73.0f;

public:
	BackGroundObject();
	~BackGroundObject();

	void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, UINT texNum) override;

	void Update()override;

	void Draw(DirectXCommon* dxCommon)override;

	void SetRightFlag(const bool& right) { this->right = right; }

	void SetLineFlag(const bool& lineFlag) { this->lineFlag = lineFlag; }
};

