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

	std::unique_ptr<Object3d>turretObj;//��Ԃ̖C���̃I�u�W�F�N�g

	std::unique_ptr<Object3d>bodyObj;//��Ԃ̎ԑ̂̃I�u�W�F�N�g

	std::unique_ptr<EnemyBullet>eBullet;//�e
	std::unique_ptr<HitParticle>hitParticle;//���������ۂ̃p�[�e�B�N��

	static Player* player;//�v���C���[
	static std::vector<Bullet*> pBullet;//�v���C���[�̕��ʂ̒e

	Vector3 adjustment;//�I�u�W�F�N�g�̈ʒu�����p�̕ϐ�
	int reverseCount;//���]���邽�߂̕ϐ�

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
