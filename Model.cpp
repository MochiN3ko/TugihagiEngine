#include "Model.h"

#include<vector>
#include<fstream>
#include<sstream>
#include<string>

using namespace DirectX;
using namespace std;

 const float Model::radius = 5.0f;
 const float Model::prizmHeight = 8.0f;

 void Model::LoadModel(const std::string& failename, bool smoothing)
 {
	 const string filename = failename + ".obj";
	 const string directoryPath = "Resources/";

	 // �t�@�C���X�g���[��
	 std::ifstream file;
	 // .obj�t�@�C�����J��
	 file.open(directoryPath + filename);
	 // �t�@�C���I�[�v�����s���`�F�b�N
	 if (file.fail()) {
		 assert(0);
	 }
	 vector<XMFLOAT3> positions;	// ���_���W
	 vector<XMFLOAT3> normals;	// �@���x�N�g��
	 vector<XMFLOAT2> texcoords;	// �e�N�X�`��UV
	 // 1�s���ǂݍ���
	 string line;
	 while (getline(file, line)) {

		 // 1�s���̕�������X�g���[���ɕϊ����ĉ�͂��₷������
		 std::istringstream line_stream(line);

		 // ���p�X�y�[�X��؂�ōs�̐擪��������擾
		 string key;
		 getline(line_stream, key, ' ');

		 // �擪������v�Ȃ璸�_���W
		 if (key == "v") {
			 // X,Y,Z���W�ǂݍ���
			 XMFLOAT3 position{};
			 line_stream >> position.x;
			 line_stream >> position.y;
			 line_stream >> position.z;
			 positions.emplace_back(position);
		 }
		
		 // �擪������f�Ȃ�|���S���i�O�p�`�j
		 if (key == "f")
		 {
			 int faceIndexCount = 0;
			 // ���p�X�y�[�X��؂�ōs�̑�����ǂݍ���
			 string index_string;
			 while (getline(line_stream, index_string, ' ')) {
				 // ���_�C���f�b�N�X1���̕�������X�g���[���ɕϊ����ĉ�͂��₷������
				 std::istringstream index_stream(index_string);
				 unsigned short indexPosition, indexNormal, indexTexcoord;
				 // ���_�ԍ�
				 index_stream >> indexPosition;
				 index_stream.seekg(1, ios_base::cur);
				 index_stream >> indexTexcoord;
				 index_stream.seekg(1, ios_base::cur);
				 index_stream >> indexNormal;

				 //���_�f�[�^�ɒǉ�
				Vertex vertex{};
				vertex.pos = positions[indexPosition-1];
				vertex.normal = normals[indexNormal -1];
				vertex.uv = texcoords[indexTexcoord -1];
				vertices.emplace_back(vertex);
				 //���_�C���f�b�N�X�ɒǉ�
				 indices.emplace_back((unsigned short)indices.size());
			 }
		 }
		 //�擪������vt�Ȃ�e�N�X�`��
		 if (key == "vt") {
		 //U,V�����ǂݍ���
			 XMFLOAT2 texcoord{};
			 line_stream >> texcoord.x;
			 line_stream >> texcoord.y;
			 //V�������]
			 texcoord.y = 1.0f - texcoord.y;
			 //�e�N�X�`�����W�f�[�^�ɒǉ�
			 texcoords.emplace_back(texcoord);
		 }
		 //�擪������vn�Ȃ�@���x�N�g��
		 if (key == "vn") {
			 //X,Y,Z�����ǂݍ���
			 XMFLOAT3 normal{};
			 line_stream >> normal.x;
			 line_stream >> normal.y;
			 line_stream >> normal.z;
			 //�e�N�X�`�����W�f�[�^�ɒǉ�
			 normals.emplace_back(normal);
		 }
	 }
	 file.close();
 }

 void Model::LoadTriangle(Vector3 pos1, Vector3 pos2, Vector3 pos3)
 {
	 vertices.resize(3);
	 indices.resize(3);

	 vertices[0].pos = XMFLOAT3(pos1.x, pos1.y, pos1.z);
	 vertices[1].pos = XMFLOAT3(pos2.x, pos2.y, pos2.z);
	 vertices[2].pos = XMFLOAT3(pos3.x, pos3.y, pos3.z);;

	 vertices[0].normal = { 0,0,-1 };
	 vertices[1].normal = { 0,0,-1 };
	 vertices[2].normal = { 0,0,-1 };

	 vertices[0].uv = { 0,0 };
	 vertices[1].uv = { 0,0 };
	 vertices[2].uv = { 0,0 };

	 indices[0] = 0;
	 indices[1] = 1;
	 indices[2] = 2;
 }

 void Model::Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, UINT texNumber)
{
	this->textureManager = textureManager;
	this->texNumber = texNumber;

	HRESULT result = S_FALSE;
	
	//�@�������̌v�Z

	for (int i = 0; i <	(UINT)indices.size()/3; i++)
	{
		//�O�p�`1���v�Z���Ă���
		//�O�p�`�̃C���f�b�N�X���擾
		unsigned short index0 = indices[i * 3 + 0];
		unsigned short index1 = indices[i * 3 + 1];
		unsigned short index2 = indices[i * 3 + 2];
		//�O�p�`���\�����钸�_���W���x�N�g���ɑ��
		XMVECTOR p0 = XMLoadFloat3(&vertices[index0].pos);
		XMVECTOR p1 = XMLoadFloat3(&vertices[index1].pos);
		XMVECTOR p2 = XMLoadFloat3(&vertices[index2].pos);
		//p0��p1�x�N�g���Ap0��p2�x�N�g�����v�Z
		XMVECTOR v1 = XMVectorSubtract(p1, p0);
		XMVECTOR v2 = XMVectorSubtract(p2, p0);
		//�O�ς͗������琂���ȃx�N�g��
		XMVECTOR normal = XMVector3Cross(v1, v2);
		//���K��
		normal = XMVector3Normalize(normal);
		//���߂��@���𒸓_�f�[�^�ɑ��
		XMStoreFloat3(&vertices[index0].normal, normal);
		XMStoreFloat3(&vertices[index1].normal, normal);
		XMStoreFloat3(&vertices[index2].normal, normal);
	}

	UINT sizeVB = static_cast<UINT>(sizeof(Vertex) * vertices.size());
	UINT sizeIB = static_cast<UINT>(sizeof(unsigned short) * indices.size());

	//���_�o�b�t�@����
	result = dxCommon->GetDevice()->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(sizeVB),
		D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&vertBuff));
	if (FAILED(result)) {
		assert(0);
	}
	//�C���f�b�N�X�o�b�t�@����
	result = dxCommon->GetDevice()->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(sizeIB),
		D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&indexBuff));
	if (FAILED(result)) {
		assert(0);
	}
	//�o�b�t�@�ւ̃f�[�^�]��
	Vertex* vertMap = nullptr;
	result = vertBuff->Map(0, nullptr, (void**)&vertMap);
	std::copy(vertices.begin(), vertices.end(), vertMap);

	vertBuff->Unmap(0, nullptr);

	//GPU��̃o�b�t�@�ɑΉ��������z���������擾
	unsigned short* indexMap = nullptr;
	result = indexBuff->Map(0, nullptr, (void**)&indexMap);

	//�S�C���f�b�N�X�ɑ΂���
	std::copy(indices.begin(), indices.end(), indexMap);

	indexBuff->Unmap(0, nullptr);

	//���_�o�b�t�@�r���[�̍쐬
	vbView.BufferLocation = vertBuff->GetGPUVirtualAddress();
	vbView.SizeInBytes = sizeVB;
	vbView.StrideInBytes = sizeof(vertices[0]);

	//�C���f�b�N�X�o�b�t�@�r���[�̍쐬
	ibView.BufferLocation = indexBuff->GetGPUVirtualAddress();
	ibView.Format = DXGI_FORMAT_R16_UINT;
	ibView.SizeInBytes = sizeIB;

}

void Model::Draw(ID3D12GraphicsCommandList* cmdList)
{
	//���_�o�b�t�@�̐ݒ�
	cmdList->IASetVertexBuffers(0, 1, &vbView);
	//�C���f�b�N�X�o�b�t�@�̃Z�b�g�R�}���h
	cmdList->IASetIndexBuffer(&ibView);
	//�f�X�N���v�^�q�[�v�̔z��
	textureManager->SetDescripterHeaps(cmdList);
	//�V�F�[�_���\�[�X�r���[���Z�b�g
	textureManager->SetShaderResourceView(cmdList, 1, texNumber);
	// �`��R�}���h
	cmdList->DrawIndexedInstanced((UINT)indices.size(), 1, 0, 0, 0);

}
