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
public:	//�萔
	static const int maxObjectCount = 3000;//3D�I�u�W�F�N�g�̍ő��

public:   //�G�C���A�X
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;

	//using XMFLOAT2 = DirectX::XMFLOAT2;
	//using XMVECTOR = DirectX::XMVECTOR;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	//���ʃf�[�^
	class Common
	{
		friend class Object3d;
	public:
		/// <summary>
		/// �O���t�B�N�X�p�C�v���C��������
		/// </summary>
		/// <param name="dxCommon">DirectX���</param>
		void InitializeGraphicsPipeline(DirectXCommon*dxCommon);
		/// <summary>
		/// �J����������
		/// </summary>
		void InitializeCamera();
	private:
		//DirectX12���
		DirectXCommon* dxCommon = nullptr;
		//���[�g�V�O�l�`��
		ComPtr < ID3D12RootSignature> rootsignature;
		//�p�C�v���C���X�e�[�g
		ComPtr < ID3D12PipelineState> pipelinestate;
		//�J����
		Camera* camera = nullptr;
	};
	
	//�萔�o�b�t�@�p�f�[�^�\����
	struct ConstBufferData {
		XMFLOAT4 color;// �F (RGBA)
		XMMATRIX mat;	//�RD�ϊ��s��
	};

public://�ÓI�����o�֐�
	/// <summary>
	/// �ÓI�����o�̏�����
	/// </summary>
	static void StaticInitialize(DirectXCommon* dxCommon,Camera* camera);
	/// <summary>
	/// �f�X�N���v�^�[�q�[�v���Z�b�g
	/// </summary>
	static void RestDescriptorHeap();
	/// <summary>
	/// �ÓI�����o�̏I������
	/// </summary>
	static void StaticFinalize();

private://�ÓI�����o�ϐ�
	static Common* common;

public://�����o�֐�
	Object3d();

	~Object3d();
	/// <summary>
	/// ������
	/// </summary>
	void Initialize(Model* model);
	/// <summary>
	/// �X�V
	/// </summary>
	void Update();
	/// <summary>
	/// �`��
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
	//�g�����X�t�H�[��
	Vector3 scale = { 1.0f,1.0f,1.0f };
	Vector3 rotation = { 0.0f,0.0f,0.0f };
	Vector3 position = { 0.0f,0.0f,0.0f };
	Vector3 color = { 1.0f,1.0f,1.0f };
	XMMATRIX matWorld;			//���[�J�����[���h�ϊ��s��
	//XMMATRIX matScale, matRot, matTrans;

	Object3d* parent = nullptr;	//�e�I�u�W�F�N�g
	//���f���f�[�^
	Model* model = nullptr;
};

