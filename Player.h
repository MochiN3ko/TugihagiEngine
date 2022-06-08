#pragma once
#include "BaseGameObject.h"
#include "Model.h"
#include <DirectXMath.h>
#include "Object3d.h"
#include"Camera.h"
#include "NormalBullet.h"
#include"FireParticle.h"
#include"SmokeParticle.h"
#include"Laser.h"

class Player :
	public BaseGameObject
{
public://�G�C���A�X
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMMATRIX = DirectX::XMMATRIX;
private:
	static Input* input;//�L�[����

	std::unique_ptr<Object3d>turretObj;//��Ԃ̖C���̃I�u�W�F�N�g
	std::unique_ptr<Object3d>bodyObj;//��Ԃ̎ԑ̂̃I�u�W�F�N�g

	std::unique_ptr<NormalBullet>nBullet;//�v���C���[�̕��ʂ̒e
	std::unique_ptr<FireParticle>fireParticle;//�������ۂ̃p�[�e�B�N��
	std::unique_ptr<Laser>laser;//�⏕��
	
	static bool isInput;
	//��l�̃J����
	Vector3 eye = Vector3::Zero;//���_
	Vector3 target = Vector3::Zero;//�����_
	
	float cameraRightAngle;//��]�p�x
	float sensibility;//���x����
	float distanceY;
	float distanceZ;

	int hp;//�̗�
	float speed;//�e�̑��x

	float angle = 0.0f;
	
	Vector3 adjustment = Vector3::Zero;
	Vector3 bodyRotation = Vector3::Zero;

	int interval = 0;

	bool knockBack = false;
	Vector3 recoil = Vector3::Zero;
	Vector3 vel = Vector3::Zero;
	Vector3 dirVel = Vector3::Zero;

	int normal = 0;
	int invincible = 0;

public:
	Player();
	~Player();
	void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, UINT texNum) override;
	void Update()override;
	void Draw(DirectXCommon*dxCommon)override;

	void Move();
	void TPSCameraUpdate();
	void ObjectRot();
	void Reset();

	//Getter
	Vector3 GetPlayerEye() { return eye; }
	Vector3 GetPlayerTarget() { return target; }
	NormalBullet* GetNormalBullet() { return nBullet.get(); }
	int GetHp() { return hp; }
	//Setter
	static void SetInput(Input* i) { input = i; }
	void SetInputFlag(bool isInput) { this->isInput = isInput; }
	void SetHp(int i) { hp = i; }
	void Damage();
};

