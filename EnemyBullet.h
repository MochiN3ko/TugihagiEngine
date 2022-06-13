#pragma once
#include "Model.h"
#include <DirectXMath.h>
#include "Object3d.h"
#include"Bullet.h"
#include"Player.h"

class EnemyBullet
{
private:
	int size;//�e�̗v�f��
	std::vector<Bullet*> object;
	int a = 0;//���˃��[�g�p�̃J�E���g
	int b = 0;	//�e�̃J�E���g

	float speed = 0.0f;//�e�̑��x

public:
	EnemyBullet(int a);
	~EnemyBullet();
	void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, UINT texNum);
	void Update(const Vector3& p, Player* player);
	void Draw(DirectXCommon* dxCommon);
	void Reset();
	std::vector<Bullet*>GetBullet() { return object; }
};