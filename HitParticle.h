#pragma once
#include "Model.h"
#include <DirectXMath.h>
#include "Object3d.h"
#include"Particle.h"

class HitParticle
{
private:
	static const int size = 10;
	std::vector<Particle*> object;
	bool spawn;
	int a;

public:
	HitParticle();
	~HitParticle();
	void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, UINT texNum);
	void Update(Vector3 p);
	void Draw(DirectXCommon* dxCommon);

	void SetPosition(Vector3 position) { for (int i = 0; i < object.size(); ++i) { object[i]->SetPosition(Vector3(position.x, position.y, position.z)); } }
	void SetLiveFlag(bool b) { for (auto& o : object) { o->SetLiveFlag(b); } }
	void SetSpawnFlag(bool b) { spawn = b; }
};
