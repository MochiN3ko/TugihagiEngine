#pragma once
#include "DirectXCommon.h"
#include "TextureManager.h"
#include <DirectXMath.h>
#include <random>
#include"Input.h"
#include"Vector2.h"
#include"Vector3.h"
#include"Collision.h"

#include"Loader.h"

#include<memory>

class BaseGameObject
{
protected:
	Vector3 position = Vector3::Zero;	//���W
	Vector3 rotation = Vector3::Zero;	//��]
	Vector3 scale = Vector3::Zero;	//�X�P�[��
	Vector3 velocity = Vector3::Zero;//�����x
	bool liveFlag = false;//�\���t���O

	static Loader* loader;

public: // �����o�֐�
	BaseGameObject();
	virtual ~BaseGameObject();

	virtual void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, UINT texNum) = 0;
	virtual void Update() = 0;
	virtual void Draw(DirectXCommon* dxCommon) = 0;

	//Setter
	void SetPosition(Vector3 p){ position = p; }
	void SetVelocity(Vector3 v) { velocity = v; }
	void SetRotation(Vector3 r) { rotation = r; }
	void SetScale(Vector3 s) { scale = s; }
	void SetLiveFlag(bool b) { liveFlag = b; }
	static void SetModelLoad(Loader* l) { loader = l; }
	//Getter
	Vector3 GetPosition() { return position; }
	Vector3 GetVelocity() { return velocity; }
	Vector3 GetRotation() { return rotation; }
	Vector3 GetScale() { return scale; }
	bool GetLiveFlag() { return liveFlag; }
};

