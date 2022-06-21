#pragma once
#include "Object3d.h"
#include"Bullet.h"
#include <DirectXMath.h>

class NormalBullet
{
public://エイリアス
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMMATRIX = DirectX::XMMATRIX;

private:
	std::vector<Bullet*> object;//弾
	int size = 0;//弾の量
	int bulletCount = 0;//弾のカウント

	size_t oSize = 0;

public:
	NormalBullet(const int& size);
	~NormalBullet();
	void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, UINT texNum);
	void Update(const Vector3& position,const Vector3& velocity);
	void Draw(DirectXCommon* dxCommon);
	void Fire();
	void Reset();
	//Getter
	std::vector<Bullet*>GetBullet() { return object; }
};

