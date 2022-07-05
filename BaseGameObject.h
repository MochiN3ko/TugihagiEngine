#pragma once
#include "DirectXCommon.h"
#include "TextureManager.h"
#include"Input.h"
#include"Sprite.h"
#include"Vector2.h"
#include"Vector3.h"
#include"Collision.h"
#include"Loader.h"

#include <DirectXMath.h>
#include <random>
#include<memory>
#include<vector>

class BaseGameObject
{
protected:
	Vector3 position = Vector3::Zero;//座標
	Vector3 velocity = Vector3::Zero;//加速度
	Vector3 rotation = Vector3::Zero;//回転
	Vector3 scale = Vector3::Zero;//スケール
	Vector3 color = Vector3::Zero;//色
	bool liveFlag = false;//表示フラグ

	static Loader* loader;

public: // メンバ関数
	BaseGameObject();
	virtual ~BaseGameObject();

	virtual void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, UINT texNum) = 0;
	virtual void Update() = 0;
	virtual void Draw(DirectXCommon* dxCommon) = 0;

	//Setter
	void SetPosition(const Vector3& position){ this->position = position; }
	void SetVelocity(const Vector3& velocity) { this->velocity = velocity; }
	void SetRotation(const Vector3& rotation) { this->rotation = rotation; }
	void SetScale(const Vector3& scale) { this->scale = scale; }
	void SetColor(const Vector3& color) { this->color = color; }
	void SetLiveFlag(const bool& b) { liveFlag = b; }
	static void SetModelLoad(Loader* l) { loader = l; }
	//Getter
	const Vector3& GetPosition() { return position; }
	const Vector3& GetVelocity() { return velocity; }
	const Vector3& GetRotation() { return rotation; }
	const Vector3& GetScale() { return scale; }
	const Vector3& GetColor() { return color; }
	const bool& GetLiveFlag() { return liveFlag; }
};

