#pragma once
#include "BaseGameObject.h"
#include "Model.h"
#include <DirectXMath.h>
#include "Object3d.h"
#include"Player.h"

class Wall :
	public BaseGameObject
{
private:
	std::unique_ptr<Object3d>object;
	
	static Player* player;//プレイヤー
	static std::vector<Bullet*> pBullet;//プレイヤーの弾

public:
	Wall();
	~Wall();
	void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, UINT texNum) override;
	void Update()override;
	void WallBulletHit(const std::vector<Bullet*>bullet);//壁と弾の当たり判定関数
	void Draw(DirectXCommon* dxCommon)override;
	//Setter
	static void SetPlayer(Player* p) { player = p; }
	static void SetNormalBullet(const std::vector<Bullet*>b) { pBullet = b; }

};
