#pragma once
#include "BaseGameObject.h"
#include "Object3d.h"
#include"Player.h"
#include <DirectXMath.h>

class Ceiling :
	public BaseGameObject
{
private:
	std::unique_ptr<Object3d>object;
	static Player* player;//ÉvÉåÉCÉÑÅ[
	static std::vector<Bullet*>pBullet;

public:
	Ceiling();
	~Ceiling();
	void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, UINT texNum) override;
	void Update()override;
	void Draw(DirectXCommon* dxCommon)override;
	//Setter
	static void SetPlayer(Player* p) { player = p; }
	static void SetNormalBullet(const std::vector<Bullet*>b) { pBullet = b; }
};


