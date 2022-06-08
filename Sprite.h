#pragma once
#include<d3d12.h>
#include<d3dx12.h>
#include<wrl.h>
#include<DirectXMath.h>

#include"TextureManager.h"
#include"DirectXCommon.h"

/// <summary>
/// �X�v���C�g
/// </summary>
class Sprite
{
public:   //�G�C���A�X
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
	
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	class  Common
	{
		friend class Sprite;
	public:
		void InitializeGraphicsPipeline();

	protected:
		DirectXCommon* dxCommon = nullptr;
		TextureManager* textureManager = nullptr;
		ComPtr<ID3D12RootSignature>rootSignature;
		ComPtr<ID3D12PipelineState>pipelineState;
		XMMATRIX matProjection{};//�ˉe�ϊ�
	};

	struct VertexPosUv
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT2 uv;
	};
	//�萔�o�b�t�@�p�f�[�^�\����
	struct ConstBufferData {
		DirectX::XMFLOAT4 color;// �F (RGBA)
		DirectX::XMMATRIX mat;	//�RD�ϊ��s��
	};

public:	//�ÓI�����o�֐�
	/// <summary>
	/// �ÓI�����o�̏�����
	/// </summary>
	static void StaticInitialize(DirectXCommon* dxCommon, TextureManager* textureManager);
	/// <summary>
	/// �ÓI�����o�̉��
	/// </summary>
	static void StaticFinalize();
/// <summary>
/// �O���t�B�b�N�X�p�C�v���C���̃Z�b�g
/// </summary>
	static void SetPiepelineState(ID3D12GraphicsCommandList* cmdList);

protected:	//�ÓI�����o�ϐ�
	static Common* common;

public:
	/// <summary>
	/// 
	/// </summary>
	/// <param name="texNumber"></param>
	/// <param name="position"></param>
	/// <param name="size"></param>
	/// <param name="color"></param>
	/// <param name="anchorpoint"></param>
	/// <param name="isFlipX"></param>
	/// <param name="isFlipY"></param>
	Sprite(UINT texNumber, XMFLOAT2 position, XMFLOAT2 size, XMFLOAT4 color, XMFLOAT2 anchorpoint, bool isFlipX, bool isFlipY);
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="texNumber"></param>
	void Initialize(UINT texNumber);
	/// <summary>
	/// �`��
	/// </summary>
	void Draw(ID3D12GraphicsCommandList* cmdList);
	/// <summary>
	/// ���_�o�b�t�@�Ƀf�[�^�]��
	/// </summary>
	void TransferVertices();
	/// <summary>
	/// �T�C�Y�ݒ�
	/// </summary>
	void SetSize(float width, float height);
	/// <summary>
	/// �e�N�X�`���͈͎̔w��
	/// </summary>
	/// <param name="anchorpoint"></param>
	void TextureRange(float tex_x, float tex_y, float tex_width, float tex_height);
public:
	DirectXCommon* GetdxCommon() { return common->dxCommon; }
	ComPtr<ID3D12PipelineState> GetPipielineState() { return common->pipelineState; }

protected:	//�����o�ϐ�
	ComPtr<ID3D12Resource> vertBuff;//���_�o�b�t�@
	ComPtr<ID3D12Resource> constBuff;//�萔�o�b�t�@
	D3D12_VERTEX_BUFFER_VIEW vbView{};//���_�o�b�t�@�r���[
	float rotation = 0.0f;//Z����]
	XMFLOAT3 position{};//���W
	XMMATRIX matWorld{};//���[���h�s��
	XMFLOAT4 color = { 1,1,1,1 };//�F
	UINT texNumber = 0;//�e�N�X�`���ԍ�
	XMFLOAT2 anchorpoint = { 0.5f,0.5f };//��_
	float width=100.0f;
	float height=100.0f;
	bool isFlipX = false;//���E���]
	bool isFlipY = false;//�㉺���]
	float tex_x = 0.0f;//�e�N�X�`������@x���W
	float tex_y = 0.0f;//�e�N�X�`������@y���W
	float tex_width = 100.0f;//�e�N�X�`������
	float tex_height = 100.0f;//�e�N�X�`���c��
};

