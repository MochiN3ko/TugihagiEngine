#pragma once
#include "Model.h"
#include <DirectXMath.h>
#include "Object3d.h"
#include"Particle.h"

class ParticleManager
{
private:
	static const int size = 30;
	std::vector<Particle*> object;

public:
	ParticleManager();
	~ParticleManager();
	void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, UINT texNum);
	void Update();
	void Draw(DirectXCommon* dxCommon);

	void SetPosition(Vector3 position);
	void SetLiveFlag(bool b);
	void SetTarget(Vector3 p);
};

