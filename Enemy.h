#pragma once
#include "BaseGameObject.h"
#include "Object3d.h"
#include"HitParticle.h"
#include"EnemyBullet.h"
#include"Player.h"
#include <DirectXMath.h>
class Enemy :
	public BaseGameObject
{
private:

	std::unique_ptr<Object3d>turretObj;//戦車の砲塔のオブジェクト

	std::unique_ptr<Object3d>bodyObj;//戦車の車体のオブジェクト

	std::unique_ptr<EnemyBullet>eBullet;//弾
	std::unique_ptr<HitParticle>hitParticle;//当たった際のパーティクル

	static Player* player;//プレイヤー
	static std::vector<Bullet*> pBullet;//プレイヤーの普通の弾

	Vector3 adjustment;//オブジェクトの位置調整用の変数
	int reverseCount;//反転するための変数

public:
	Enemy();
	~Enemy();

	void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, UINT texNum) override;
	void Update()override;
	void Draw(DirectXCommon* dxCommon)override;
	void Hit();
	void Reset();
	EnemyBullet* GetNEnemyBullet() { return eBullet.get(); }

	//Setter
	static void StaticLoad();
	static void SetPlayer(Player* p) { player = p; }
	static void SetNormalBullet(const std::vector<Bullet*>b){ pBullet = b; }
};
