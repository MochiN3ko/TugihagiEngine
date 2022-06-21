#pragma once
#include "BaseGameObject.h"
#include "Object3d.h"
#include <DirectXMath.h>

class PauseResume :
    public BaseGameObject
{
private:

	std::unique_ptr<Object3d>object;
	Vector3 black = { 0.0f, 0.0f, 0.0f };
	Vector3 red = { 1.0f, 0.0f, 0.0f };

	float range = 0.005f;//�I�u�W�F�N�g��������
	float angle = 0.0f;//�I�u�W�F�N�g�̓�������
	bool move = false;

public:
	PauseResume();
	~PauseResume();
	void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, UINT texNum) override;
	void Update()override;
	void Draw(DirectXCommon* dxCommon)override;

	void SetMoveFlag(const bool& move) { this->move = move; }
};

