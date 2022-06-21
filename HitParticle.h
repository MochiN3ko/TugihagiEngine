#pragma once
#include "Object3d.h"
#include"Particle.h"
#include <DirectXMath.h>

class HitParticle
{
private:
	static const int size = 10;
	std::vector<Particle*>object;
	bool spawn = false;;
	bool red = false;
	int a = 0;

public:
	HitParticle();
	~HitParticle();
	void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, UINT texNum);
	void Update(const Vector3& p);
	void Draw(DirectXCommon* dxCommon);

	void SetPosition(const Vector3& position) { for (int i = 0, size = object.size(); i < size; ++i) { object[i]->SetPosition(Vector3(position.x, position.y, position.z)); } }
	void SetLiveFlag(const bool& b) { for (auto& o : object) { o->SetLiveFlag(b); } }
	void SetSpawnFlag(const bool& b) { spawn = b; }
	void SetRedFlag(const bool& b) { red = b; }
};
