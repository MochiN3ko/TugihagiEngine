#pragma once
#include "Object3d.h"
#include"Bullet.h"
#include <DirectXMath.h>

class NormalBullet
{
public://�G�C���A�X
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMMATRIX = DirectX::XMMATRIX;

private:
	std::vector<Bullet*> object;//�e
	int size = 0;//�e�̗�
	int bulletCount = 0;//�e�̃J�E���g

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

