#pragma once
#include "Object3d.h"
#include"Bullet.h"
#include"Player.h"
#include <DirectXMath.h>

class EnemyBullet
{
private:
	int size = 0;//弾の要素数
	std::vector<Bullet*> object;
	int a = 0;//発射レート用のカウント
	int b = 0;	//弾のカウント

	float speed = 0.0f;//弾の速度

public:
	EnemyBullet(const int& a);
	~EnemyBullet();
	void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, UINT texNum);
	void Update(const Vector3& p, Player* player);
	void Draw(DirectXCommon* dxCommon);
	void Reset();
	std::vector<Bullet*>GetBullet() { return object; }
};