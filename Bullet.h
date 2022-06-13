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

	int time;//���˂���Ă���̃J�E���g

	Vector3 rightPoint = Vector3::Zero;//�e�̉E���̔��˔���|�W�V����
	Vector3 leftPoint = Vector3::Zero;//�e�̍����̔��˔���|�W�V����
	Vector3 frontPoint = Vector3::Zero;//�e�̑O���̔��˔���|�W�V����
	Vector3 behindPoint = Vector3::Zero;//�e�̌�둤�̔��˔���|�W�V����
	float intervalX;//���̕����o
	float intervalZ;//�c�̕����o
	float pointSize;//���˔���|�W�V�����̑傫��
	int reverseCount = 0;//���˂ł����

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