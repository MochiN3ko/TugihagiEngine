#pragma once

#include"DirectXCommon.h"

#include<d3d12.h> 
#include<d3dx12.h>
#include<wrl.h>
#include<DirectXTex.h>


class TextureManager
{
public:   //�G�C���A�X
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
public:	  //�萔
	static const int spriteSRVCount = 512;//�e�N�X�`���̍ő喇��
public:		//�����o�֐�
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="dxCommon"></param>
	void Initialize(DirectXCommon*dxCommon);
	/// <summary>
	/// �e�N�X�`���ǂݍ���
	/// </summary>
	/// <param name="texnumber">�e�N�X�`���ԍ�</param>
	/// <param name="filename">�e�N�X�`���t�@�C����</param>
	void LoadTexture(UINT texnumber, const wchar_t* filename);
	/// <summary>
	/// �e�N�X�`���o�b�t�@�擾
	/// </summary>
	ID3D12Resource* GetSpriteTexBuff(UINT texnumber);
	/// <summary>
	/// �f�X�N���v�^�[�q�[�v���Z�b�g(�O���t�B�b�N�X�R�}���h)
	/// </summary>
	/// <param name="cmdList">�R�}���h���X�g</param>
	void SetDescripterHeaps(ID3D12GraphicsCommandList* cmdList);
	/// <summary>
	/// SRV���Z�b�g�i�O���t�B�b�N�X�R�}���h�j
	/// </summary>
	/// <param name="cmdList">�R�}���h���X�g</param>
	/// <param name="rootParameterIndex">���[�g�p�����[�^�[�̔ԍ�</param>
	/// <param name="texNumber">�e�N�X�`���ԍ�</param>
	void SetShaderResourceView(ID3D12GraphicsCommandList* cmdList,UINT rootParameterIndex,UINT texNumber);
	//getter
	ID3D12DescriptorHeap* GetSpriteDescHeap() { return spriteDescHeap.Get(); }
private:  //�����o�ϐ�
	ComPtr<ID3D12DescriptorHeap> spriteDescHeap;
	ComPtr<ID3D12Resource> spriteTexBuff[spriteSRVCount];
	DirectXCommon* dxCommon = nullptr;
};

