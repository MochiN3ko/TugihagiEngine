#pragma once
#include "BaseGameObject.h"
#include "Object3d.h"
#include <DirectXMath.h>
#include<random>
#include<time.h>

class Particle :
	public BaseGameObject
{
private:
	std::unique_ptr<Object3d>object;

	int ptime = 0;			//”­ŽË‚³‚ê‚Ä‚©‚ç‚ÌƒJƒEƒ“ƒg
public:
	Particle();
	~Particle();
	void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, UINT texNum) override;
	void Update()override;
	void Draw(DirectXCommon* dxCommon)override;

	void SetColor(const Vector3& color) { object->SetColor(color); }

	//Getter
	const int& GetTime() { return ptime; }

};

