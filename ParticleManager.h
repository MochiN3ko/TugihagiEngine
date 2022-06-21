#pragma once
#include "Object3d.h"
#include"Particle.h"
#include <DirectXMath.h>

class ParticleManager
{
private:
	static const int size = 30;
	std::vector<Particle*>object;

	size_t oSize = 0;

public:
	ParticleManager();
	~ParticleManager();
	void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, UINT texNum);
	void Update();
	void Draw(DirectXCommon* dxCommon);

	void SetPosition(const Vector3& position);
	void SetLiveFlag(const bool& b);
};

