#pragma once
#include"Vector2.h"
#include"Vector3.h"
#include<DirectXMath.h>
class Camera
{
public://エイリアス
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// ビュー行列変換の計算
	/// </summary>
	void UpdateViewMatrix();
	/// <summary>
	/// 透視投影
	/// </summary>
	void UpdateProjectionMatrix();

	//getter
	const XMMATRIX& getMatView() { return matView; }
	const XMMATRIX& getMatProjection() { return matProjection; }
	const XMFLOAT3& GetEye() { return eye; }
	const XMFLOAT3& GetTarget() { return target; }
	const XMFLOAT3& GetUp() { return up; }
	//setter
	void SetMatView(const XMMATRIX& matView) { this->matView = matView; }
	void SetMatProjection(const XMMATRIX& matProjection) { this->matProjection = matProjection; }
	void SetEye(const XMFLOAT3& eye) { this->eye = eye; }
	void SetTarget(const XMFLOAT3& target) { this->target = target; }
	void SetUp(const XMFLOAT3& up) { this->up = up; }

private:
	XMMATRIX matView;				//ビュー行列
	XMMATRIX matProjection;			//射影行列
	XMFLOAT3 eye;					//視点座標
	XMFLOAT3 target;				//注視点座標
	XMFLOAT3 up;					//上方向ベクトル
	XMMATRIX matBillboard;		    //全方向ビルボード
	XMMATRIX matBillboardY;	        //Y軸ビルボード
};

