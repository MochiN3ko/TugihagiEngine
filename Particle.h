#pragma once
#include "BaseGameObject.h"
#include "Model.h"
#include <DirectXMath.h>
#include<random>
#include<time.h>
#include "Object3d.h"

class Particle :
	public BaseGameObject
{
private:
	std::unique_ptr<Object3d>object;

	int ptime;			//”­ŽË‚³‚ê‚Ä‚©‚ç‚ÌƒJƒEƒ“ƒg
public:
	Particle();
	~Particle();
	void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, UINT texNum) override;
	void Update()override;
	void Draw(DirectXCommon* dxCommon)override;

	void SetColor(Vector3 c) { object->SetColor(c); }

	//Getter
	int GetTime() { return ptime; }

};

