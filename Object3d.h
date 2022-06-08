#pragma once

#include<d3d12.h>
#include<d3dx12.h>
#include<wrl.h>

#include"DirectXCommon.h"
#include"Model.h"
#include"Camera.h"
#include"Vector2.h"
#include"Vector3.h"

#include<memory>
#include <DirectXMath.h>

class Object3d
{
public:	//定数
	static const int maxObjectCount = 3000;//3Dオブジェクトの最大個数

public:   //エイリアス
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;

	//using XMFLOAT2 = DirectX::XMFLOAT2;
	//using XMVECTOR = DirectX::XMVECTOR;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	//共通データ
	class Common
	{
		friend class Object3d;
	public:
		/// <summary>
		/// グラフィクスパイプライン初期化
		/// </summary>
		/// <param name="dxCommon">DirectX基盤</param>
		void InitializeGraphicsPipeline(DirectXCommon*dxCommon);
		/// <summary>
		/// カメラ初期化
		/// </summary>
		void InitializeCamera();
	private:
		//DirectX12基盤
		DirectXCommon* dxCommon = nullptr;
		//ルートシグネチャ
		ComPtr < ID3D12RootSignature> rootsignature;
		//パイプラインステート
		ComPtr < ID3D12PipelineState> pipelinestate;
		//カメラ
		Camera* camera = nullptr;
	};
	
	//定数バッファ用データ構造体
	struct ConstBufferData {
		XMFLOAT4 color;// 色 (RGBA)
		XMMATRIX mat;	//３D変換行列
	};

public://静的メンバ関数
	/// <summary>
	/// 静的メンバの初期化
	/// </summary>
	static void StaticInitialize(DirectXCommon* dxCommon,Camera* camera);
	/// <summary>
	/// デスクリプターヒープリセット
	/// </summary>
	static void RestDescriptorHeap();
	/// <summary>
	/// 静的メンバの終了処理
	/// </summary>
	static void StaticFinalize();

private://静的メンバ変数
	static Common* common;

public://メンバ関数
	Object3d();

	~Object3d();
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model);
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="cmdList"></param>
	void Draw(ID3D12GraphicsCommandList*cmdList);

	//Getter
	const Vector3& GetPosition() { return position; }
	const Vector3& GetScale() { return scale; }
	const Vector3& GetRotation() { return rotation; }
	//Setter
	void SetPosition(Vector3 position) { this->position = position; }
	void SetScale(Vector3 scale) { this->scale = scale; }
	void SetRotation(Vector3 rotation) { this->rotation = rotation; }
	void SetColor(Vector3 color) { this->color = color; }
	void SetParent(Object3d* parent) { this->parent = parent; }

private:
	ComPtr<ID3D12Resource> constBuff;
	//トランスフォーム
	Vector3 scale = { 1.0f,1.0f,1.0f };
	Vector3 rotation = { 0.0f,0.0f,0.0f };
	Vector3 position = { 0.0f,0.0f,0.0f };
	Vector3 color = { 1.0f,1.0f,1.0f };
	XMMATRIX matWorld;			//ローカルワールド変換行列
	//XMMATRIX matScale, matRot, matTrans;

	Object3d* parent = nullptr;	//親オブジェクト
	//モデルデータ
	Model* model = nullptr;
};

