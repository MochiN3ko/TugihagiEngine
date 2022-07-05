#pragma once
#include "BaseGameObject.h"
#include "Object3d.h"
#include"Camera.h"
#include "NormalBullet.h"
#include"FireParticle.h"
#include"SmokeParticle.h"
#include"HitParticle.h"
#include"Laser.h"
#include <DirectXMath.h>

class Player :
	public BaseGameObject
{
public://エイリアス
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMMATRIX = DirectX::XMMATRIX;
private:
	static Input* input;//キー入力

	std::unique_ptr<Object3d>turretObj;//戦車の砲塔のオブジェクト
	std::unique_ptr<Object3d>bodyObj;//戦車の車体のオブジェクト

	std::unique_ptr<NormalBullet>nBullet;//プレイヤーの普通の弾
	//std::unique_ptr<FireParticle>fireParticle;//撃った際のパーティクル
	std::unique_ptr<HitParticle>hitParticle;//当たった際のパーティクル
	std::unique_ptr<Laser>laser;//補助線
	
	static bool isInput;
	//一人称カメラ
	Vector3 eye = Vector3::Zero;//視点
	Vector3 target = Vector3::Zero;//注視点
	
	float cameraRightAngle;//回転角度
	float sensibility;//感度調整
	float distanceY;
	float distanceZ;

	int hp = 0;//体力
	float speed = 0.0f;//弾の速度

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
	const Vector3& GetPlayerEye() { return eye; }
	const Vector3& GetPlayerTarget() { return target; }
	NormalBullet* GetNormalBullet() { return nBullet.get(); }
	const int& GetHp() { return hp; }
	//Setter
	static void SetInput(Input* i) { input = i; }
	void SetInputFlag(const bool& isInput) { this->isInput = isInput; }
	void SetHp(const int& i) { hp = i; }
	void Damage();
};

