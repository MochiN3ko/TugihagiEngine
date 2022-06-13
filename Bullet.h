#pragma once
#include "BaseGameObject.h"
#include "Model.h"
#include <DirectXMath.h>
#include "Object3d.h"
#include"SmokeParticle.h"
class Bullet :
	public BaseGameObject
{
private:
	std::unique_ptr<Object3d>object;
	std::unique_ptr<SmokeParticle>smokeParticle;

	int time;//発射されてからのカウント

	Vector3 rightPoint = Vector3::Zero;//弾の右側の反射判定ポジション
	Vector3 leftPoint = Vector3::Zero;//弾の左側の反射判定ポジション
	Vector3 frontPoint = Vector3::Zero;//弾の前側の反射判定ポジション
	Vector3 behindPoint = Vector3::Zero;//弾の後ろ側の反射判定ポジション
	float intervalX;//横の幅感覚
	float intervalZ;//縦の幅感覚
	float pointSize;//反射判定ポジションの大きさ
	int reverseCount = 0;//反射できる回数

public:
	Bullet();
	~Bullet();
	void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, UINT texNum) override;
	void Update()override;
	void Draw(DirectXCommon* dxCommon)override;
	void Counting();
	//Getter
	int GetTime() { return time; }
	Vector3 GetRightPoint() { return rightPoint; }
	Vector3 GetLeftPoint() { return leftPoint; }
	Vector3 GetFrontPoint() { return frontPoint; }
	Vector3 GetBehindPoint() { return behindPoint; }
	float GetPointSize() { return pointSize; }
	int GetReverseCount() { return reverseCount; }

	Object3d* GetObj() { return object.get(); }
	SmokeParticle* GetSmoke() { return smokeParticle.get(); }
	//Setter
	void SetReverseCount(int count) { reverseCount = count; }
};