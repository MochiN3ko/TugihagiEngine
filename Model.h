#pragma once
#include"DirectXCommon.h"
#include"TextureManager.h"
#include"Vector2.h"
#include"Vector3.h"
#include<DirectXMath.h>

#include<d3d12.h>
#include<wrl.h>
/// <summary>
/// �􉽃��f��
/// </summary>
class Model
{
public:
	static const int division = 4;
	static const float radius;
	static const float prizmHeight;
	static const int planeCount = division * 2 + division * 2;
	static const int vertexCount = planeCount * 3;

public:
	//���_�f�[�^�\����
	struct Vertex
	{
		DirectX::XMFLOAT3 pos; // xyz ���W
		DirectX::XMFLOAT3 normal; //�@���x�N�g��
		DirectX::XMFLOAT2 uv; // uv ���W
	};
public:
	/// <summary>
	/// OBJ���[�h
	/// </summary>
	/// <param name="modelname">�t�@�C���l�[��</param>
	/// <param name="smoothing">�X���[�X</param>
	void LoadModel(const std::string& modelname, bool smoothing);

	/// <summary>
	/// �O�p�`���f��
	/// </summary>
	void LoadTriangle(Vector3 pos1, Vector3 pos2, Vector3 pos3);

	/// <summary>
	/// ������	
	/// </summary>
	void Initialize(DirectXCommon*dxCommon, TextureManager* textureManager,UINT texNumber);

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(ID3D12GraphicsCommandList* cmdList);

	//�C���f�b�N�X�z��̗v�f���𐔂���
	//int CountIndices() { return _countof(indices); }
	int CountIndices() { return (int)indices.size(); }

	const D3D12_VERTEX_BUFFER_VIEW& GetVbView() { return vbView; }
	const D3D12_INDEX_BUFFER_VIEW& GetIbView() { return ibView; }

	std::vector<Vertex> GetVertices() { return vertices; }
private:
	//�e�N�X�`���[�}�l�[�W��
	TextureManager*textureManager = nullptr;
	//�e�N�X�`���[�ԍ�
	UINT texNumber;
	//���_�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D12Resource>vertBuff;
	//�C���f�b�N�X�o�b�t�@
	Microsoft::WRL::ComPtr < ID3D12Resource>indexBuff;
	//���_�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	//�C���f�b�N�X�o�b�t�@�r���[
	D3D12_INDEX_BUFFER_VIEW ibView{};

	//���_�f�[�^�z��
	 std::vector<Vertex> vertices;
	//���_�C���f�b�N�X�z��
	 std::vector<unsigned short> indices;

};

