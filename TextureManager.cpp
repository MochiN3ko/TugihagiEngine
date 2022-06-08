#include "TextureManager.h"
#include<cassert>

using namespace DirectX;
void TextureManager::Initialize(DirectXCommon* dxCommon)
{
	HRESULT result = S_FALSE;

	this->dxCommon = dxCommon;
	//�f�X�N���v�^�q�[�v���쐬����B
	D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc = {};
	descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	descHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;//�V�F�[�_���猩����悤��
	descHeapDesc.NumDescriptors = spriteSRVCount;
	// ����
	result = dxCommon->GetDevice()->CreateDescriptorHeap(&descHeapDesc, IID_PPV_ARGS(&spriteDescHeap));
	if (FAILED(result))
	{
		assert(0);
	}
}

void TextureManager::LoadTexture(UINT texnumber, const wchar_t* filename)
{
	HRESULT result;
	//WIC�e�N�X�`���̃��[�h
	TexMetadata metadata{};
	ScratchImage scratchImg{};

	result = LoadFromWICFile(
		filename,								//[Resources]�t�H���_��[texture.png]
		WIC_FLAGS_NONE,
		&metadata, scratchImg);
	if (FAILED(result)) {
		assert(0);
	}
	const Image* img = scratchImg.GetImage(0, 0, 0);//���f�[�^���o

	//���\�[�X�ݒ�
	CD3DX12_RESOURCE_DESC texresDesc = CD3DX12_RESOURCE_DESC::Tex2D(
		metadata.format,
		metadata.width,
		(UINT)metadata.height,
		(UINT16)metadata.arraySize,
		(UINT16)metadata.mipLevels
	);

	result = dxCommon->GetDevice()->CreateCommittedResource(    //GPU���\�[�X�̐���
		&CD3DX12_HEAP_PROPERTIES(D3D12_CPU_PAGE_PROPERTY_WRITE_BACK, D3D12_MEMORY_POOL_L0),
		D3D12_HEAP_FLAG_NONE,
		&texresDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,//�e�N�X�`���p�w��
		nullptr,
		IID_PPV_ARGS(&spriteTexBuff[texnumber]));
	if (FAILED(result)) {
		assert(0);
	}

	//�e�N�X�`���o�b�t�@�Ƀf�[�^�]��
	result = spriteTexBuff[texnumber]->WriteToSubresource(
		0,
		nullptr,//�S�̈�փR�s�[
		img->pixels,       //���f�[�^�A�h���X
		(UINT)img->rowPitch,//1���C���T�C�Y
		(UINT)img->slicePitch//1���T�C�Y
	);
	if (FAILED(result)) {
		assert(0);
	}

	//�V�F�[�_�[���\�[�X�r���[�쐬
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};//�ݒ�\����
	srvDesc.Format = metadata.format;//RGBA
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;//2D�e�N�X�`��
	srvDesc.Texture2D.MipLevels = 1;

	dxCommon->GetDevice()->CreateShaderResourceView(spriteTexBuff[texnumber].Get(),
		&srvDesc,//�e�N�X�`���ݒ���
		CD3DX12_CPU_DESCRIPTOR_HANDLE(
			spriteDescHeap->GetCPUDescriptorHandleForHeapStart(),
			texnumber,
			dxCommon->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV)));
}

ID3D12Resource* TextureManager::GetSpriteTexBuff(UINT texnumber)
{
	//�z��I�[�o�[�t���[�h�~
	//assert(texnumber < spriteSRVCount);
	if (texnumber >= spriteSRVCount) {
		return nullptr;
	}
	return spriteTexBuff[texnumber].Get();
}

void TextureManager::SetDescripterHeaps(ID3D12GraphicsCommandList* cmdList)
{
	//�f�X�N���v�^�q�[�v�̔z��
	ID3D12DescriptorHeap* ppHeaps[] = { spriteDescHeap.Get() };
	cmdList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);
}

void TextureManager::SetShaderResourceView(ID3D12GraphicsCommandList* cmdList, UINT rootParameterIndex, UINT texNumber)
{
	//SRV�̃T�C�Y���擾
	UINT sizeSRV = dxCommon->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	
	//�f�X�N���v�^�[�e�[�u���̐擪���擾
	D3D12_GPU_DESCRIPTOR_HANDLE start = spriteDescHeap->GetGPUDescriptorHandleForHeapStart();

	//SRV��GPU�n���h�����擾
	D3D12_GPU_DESCRIPTOR_HANDLE handle = CD3DX12_GPU_DESCRIPTOR_HANDLE(start,texNumber,sizeSRV);
	
	//�V�F�[�_���\�[�X�r���[���Z�b�g
	cmdList->SetGraphicsRootDescriptorTable(rootParameterIndex,handle);
}
