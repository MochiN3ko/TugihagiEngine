#pragma once
#include "Model.h"
#include <DirectXMath.h>
#include "Object3d.h"
#include"Particle.h"

class SmokeParticle
{
private:
	static const int size = 20;
	std::vector<Particle*> object;
	bool spawn;
	int a;

	size_t oSize = 0;
public:
	SmokeParticle();
	~SmokeParticle();
	void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, UINT texNum);
	void Update(Vector3 p);
	void Draw(DirectXCommon* dxCommon);

	void SetPosition(const Vector3& position) { for (int i = 0; i < object.size(); ++i) { object[i]->SetPosition(Vector3(position.x, position.y, position.z)); } }
	void SetLiveFlag(bool b) { for (auto& o : object) { o->SetLiveFlag(b); } }
	void SetSpawnFlag(bool b) { spawn = b; }
};


