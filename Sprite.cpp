#include "Sprite.h"

#include <d3dcompiler.h>

#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;

Sprite::Common* Sprite::common = nullptr;

void Sprite::StaticInitialize(DirectXCommon* dxCommon, TextureManager* textureManager)
{
	common = new Common;
	common->dxCommon = dxCommon;
	common->textureManager = textureManager;

	//�O���t�B�b�N�X�p�C�v���C������
	common->InitializeGraphicsPipeline();

	// �ˉe�s��v�Z
	common->matProjection = DirectX::XMMatrixOrthographicOffCenterLH(
		0.0f,WinApp::window_width,
		WinApp::window_height,0.0f,
		0.0f, 1.0f);
}

void Sprite::StaticFinalize()
{
	//���
	if (common != nullptr) {
		delete common;
		common = nullptr;
	}
}

void Sprite::SetPiepelineState(ID3D12GraphicsCommandList* cmdList)
{
	//�p�C�v���C���X�e�[�g�̐ݒ�
	cmdList->SetPipelineState(common->pipelineState.Get());
	//���[�g�V�O�l�`���̐ݒ�
	cmdList->SetGraphicsRootSignature(common->rootSignature.Get());
	//�v���~�e�B�u�`���ݒ�
	cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
}

Sprite::Sprite(UINT texNumber, XMFLOAT2 position, XMFLOAT2 size, XMFLOAT4 color, XMFLOAT2 anchorpoint, bool isFlipX, bool isFlipY)
{
	this->position = XMFLOAT3(position.x, position.y,0);
	//this->size = size;
	this->anchorpoint = anchorpoint;
	this->matWorld = XMMatrixIdentity();
	this->color = color;
	this->texNumber = texNumber;
	this->isFlipX = isFlipX;
	this->isFlipY = isFlipY;
	//this->texSize = size;
}

void Sprite::Initialize(UINT texNumber)
{
	HRESULT result = S_FALSE;
	
	this->texNumber = texNumber;

	if (common->textureManager->GetSpriteTexBuff(texNumber))
	{
		D3D12_RESOURCE_DESC resDesc = common->textureManager->GetSpriteTexBuff(texNumber)->GetDesc();

		width = (float)resDesc.Width;
		height = (float)resDesc.Height;

		tex_width = (float)resDesc.Width;
		tex_height = (float)resDesc.Height;

	}

	//���_�o�b�t�@����
	result = common->dxCommon->GetDevice()->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(sizeof(VertexPosUv)*4),
		D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&vertBuff));
	if (FAILED(result)) {
		assert(0);
	}

	TransferVertices();

	////�o�b�t�@�ւ̃f�[�^�]��
	//VertexPosUv* vertMap = nullptr;
	//result = vertBuff->Map(0, nullptr, (void**)&vertMap);
	//memcpy(vertMap, vertices, sizeof(vertices));
	//vertBuff->Unmap(0, nullptr);


	//���_�o�b�t�@�r���[�̍쐬
	vbView.BufferLocation = vertBuff->GetGPUVirtualAddress();
	vbView.SizeInBytes = sizeof(VertexPosUv)*4;
	vbView.StrideInBytes = sizeof(VertexPosUv);

	//�萔�o�b�t�@�̐���
	result = common->dxCommon->GetDevice()->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferData) + 0xff) & ~0xff),
		D3D12_RESOURCE_STATE_GENERIC_READ, nullptr,
		IID_PPV_ARGS(&constBuff));
	if (FAILED(result)) {
		assert(0);
	}

	//�萔�o�b�t�@�Ƀf�[�^�]��
	ConstBufferData* constMap = nullptr;
	result = constBuff->Map(0, nullptr, (void**)&constMap);
	if (SUCCEEDED(result)) {
		constMap->color = color;//�F�w��
		constMap->mat = common->matProjection;
		constBuff->Unmap(0, nullptr);
	}
}

void Sprite::Draw(ID3D12GraphicsCommandList* cmdList)
{
	//���[���h�s��̍X�V
	matWorld = XMMatrixIdentity();
	matWorld *= XMMatrixRotationZ(XMConvertToRadians(rotation));
	matWorld *= XMMatrixTranslation(position.x, position.y, position.z);
	//matWorld*= 
	//�s��̓]��
	ConstBufferData* constMap = nullptr;
	HRESULT result = constBuff->Map(0, nullptr, (void**)&constMap);
	constMap->mat = matWorld * common->matProjection;//�s��̍���
	constBuff->Unmap(0, nullptr);


	//���_�o�b�t�@���Z�b�g
	cmdList->IASetVertexBuffers(0, 1, &vbView);

	//�萔�o�b�t�@���Z�b�g
	cmdList->SetGraphicsRootConstantBufferView(0, constBuff->GetGPUVirtualAddress());


	//�f�X�N���v�^�q�[�v�̔z��
	common->textureManager->SetDescripterHeaps(cmdList);
	//�V�F�[�_���\�[�X�r���[���Z�b�g
	common->textureManager->SetShaderResourceView(cmdList, 1, texNumber);

	//�`��R�}���h
	cmdList->DrawInstanced(4, 1, 0, 0);
}

void Sprite::TransferVertices()
{
	HRESULT result;
		//���_�f�[�^
		VertexPosUv vertices[] = {
			//x      y      z       u     v
			{{  0.0f,100.0f,0.0f},{0.0f,1.0f}},//����
			{{  0.0f,  0.0f,0.0f},{0.0f,0.0f}},//����
			{{100.0f,100.0f,0.0f},{1.0f,1.0f}},//�E��
			{{100.0f,  0.0f,0.0f},{1.0f,0.0f}},//�E��
		};

		//���E�㉺���W�̌v�Z
		enum { LB, LT, RB, RT };

		float left = (0.0f - anchorpoint.x) * width;
		float right = (1.0f - anchorpoint.x) * width;
		float top = (0.0f - anchorpoint.y) * height;
		float botton = (1.0f - anchorpoint.y) * height;

		//���]�̔��f
		if (isFlipX)
		{//���E����ւ�
			left = -left;
			right = -right;
		}
		if (isFlipY)
		{//�㉺����ւ�
			top = -top;
			botton = -botton;
		}

		//���_�f�[�^�z��ɍ��W�Z�b�g
		vertices[LB].pos = { left,			botton,			0.0f };	//����
		vertices[LT].pos = { left,			top,				0.0f };	//	����
		vertices[RB].pos = { right,		 botton,		0.0f };	//�E��
		vertices[RT].pos = { right,		top,				0.0f };	//�E��

		//�e�N�X�`�����擾
		if (common->textureManager->GetSpriteTexBuff(texNumber))
		{
			D3D12_RESOURCE_DESC resDesc = common->textureManager->GetSpriteTexBuff(texNumber)->GetDesc();

			if (tex_width == 0 && tex_height == 0)
			{
				tex_width = resDesc.Width;
				tex_height = resDesc.Height;
			}

			float tex_left = tex_x / resDesc.Width;
			float tex_right = (tex_x + tex_width) / resDesc.Width;
			float tex_top = tex_y / resDesc.Height;
			float tex_botton = (tex_y + tex_height) / resDesc.Height;

			vertices[LB].uv = { tex_left,tex_botton };//����
			vertices[LT].uv = { tex_left,tex_top };//����
			vertices[RB].uv = { tex_right,tex_botton };//�E��
			vertices[RT].uv = { tex_right,tex_top };//�E��
		}

		//���_�o�b�t�@�ւ̃f�[�^�]��
		VertexPosUv* vertMap = nullptr;
		result = vertBuff->Map(0, nullptr, (void**)&vertMap);
		memcpy(vertMap, vertices, sizeof(vertices));
		vertBuff->Unmap(0, nullptr);
}

void Sprite::SetSize(float width, float height)
{
	this->width = width;
	this->height = height;
}

void Sprite::TextureRange(float tex_x, float tex_y, float tex_width, float tex_height)
{
	tex_x = tex_x;
	tex_y = tex_y;

	tex_width = tex_width;
	tex_height = tex_height;

	width = tex_width;
	height = tex_height;

}

void Sprite::Common::InitializeGraphicsPipeline()
{

	HRESULT result;
	ComPtr<ID3DBlob> vsBlob;//���_�V�F�[�_�[�I�u�W�F�N�g
	ComPtr<ID3DBlob> psBlob;//�s�N�Z���V�F�[�_�[�I�u�W�F�N�g
	ComPtr<ID3DBlob> errorBlob;//�G���[�I�u�W�F�N�g

	//���_�V�F�[�_�[�̓ǂݍ��݂ƃR���p�C��
	result = D3DCompileFromFile(
		L"SpriteVertexShader.hlsl",//�V�F�[�_�t�@�C����
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,//�C���N���[�h���\�ɂ���
		"VSmain", "vs_5_0",//�G���g���[�|�C���g���A�V�F�[�_�[���f���w��
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,//�f�o�b�O�p�ݒ�
		0,
		&vsBlob, &errorBlob);
	if (FAILED(result))
	{
		//errorBlob����G���[���e��string�^�ɃR�s�[
		std::string errstr;
		errstr.resize(errorBlob->GetBufferSize());

		std::copy_n((char*)errorBlob->GetBufferPointer(),
			errorBlob->GetBufferSize(),
			errstr.begin());
		errstr += "\n";
		//�G���[���e���E�B���h�E�ɕ\��
		OutputDebugStringA(errstr.c_str());
		exit(1);
	}

	//�s�N�Z���V�F�[�_�̓ǂݍ��݂ƃR���p�C��
	result = D3DCompileFromFile(
		L"SpritePixelShader.hlsl",//�V�F�[�_�t�@�C����
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,//�C���N���[�h�\�ɂ���
		"PSmain", "ps_5_0",//�G���g���[�|�C���g���A�V�F�[�_���f���w��
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,//�f�o�b�O�p�w��
		0,
		&psBlob, &errorBlob);

	if (FAILED(result))
	{
		//errorBlob����G���[���e��string�^�ɃR�s�[
		std::string errstr;
		errstr.resize(errorBlob->GetBufferSize());

		std::copy_n((char*)errorBlob->GetBufferPointer(),
			errorBlob->GetBufferSize(),
			errstr.begin());
		errstr += "\n";
		//�G���[���e���E�B���h�E�ɕ\��
		OutputDebugStringA(errstr.c_str());
		exit(1);
	}

	D3D12_INPUT_ELEMENT_DESC inputLayout[] =
	{
		{
			"POSITION",
			0,
			DXGI_FORMAT_R32G32B32_FLOAT,
			0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
			0
		},
		{
			"TEXCOORD",
			0,
			DXGI_FORMAT_R32G32_FLOAT,
			0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
			0
		},
	};

	D3D12_GRAPHICS_PIPELINE_STATE_DESC gpipeline{};
	gpipeline.VS = CD3DX12_SHADER_BYTECODE(vsBlob.Get());
	gpipeline.PS = CD3DX12_SHADER_BYTECODE(psBlob.Get());

	gpipeline.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;//�W���ݒ�
	//�W���I�Ȑݒ�(�w�ʃJ�����O�A�h��Ԃ��A�[�x�N���b�s���O�L��)
	gpipeline.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	gpipeline.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;//�w�ʃJ�����O���Ȃ�

	//�����_�[�^�[�Q�b�g�̃u�����h�ݒ�i8���邪���܂͈�����g��Ȃ��j
	D3D12_RENDER_TARGET_BLEND_DESC blenddesc{};
	blenddesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;//�W���ݒ�

	//�u�����h�X�e�[�g�ɐݒ肷��
	blenddesc.BlendEnable = true;
	blenddesc.BlendOpAlpha = D3D12_BLEND_OP_ADD;
	blenddesc.SrcBlendAlpha = D3D12_BLEND_ONE;
	blenddesc.DestBlendAlpha = D3D12_BLEND_ZERO;

	blenddesc.BlendOp = D3D12_BLEND_OP_ADD;
	blenddesc.SrcBlend = D3D12_BLEND_SRC_ALPHA;
	blenddesc.DestBlend = D3D12_BLEND_INV_SRC_ALPHA;
	gpipeline.BlendState.RenderTarget[0] = blenddesc;


	gpipeline.InputLayout.pInputElementDescs = inputLayout;
	gpipeline.InputLayout.NumElements = _countof(inputLayout);

	gpipeline.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

	gpipeline.NumRenderTargets = 1;//�`��Ώۂ͂P��
	gpipeline.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;//0^255�w���RGBA
	gpipeline.SampleDesc.Count = 1;//�P�s�N�Z���ɂ��P��T���v�����O

	//�f�v�X�X�e���V���X�e�[�g�̐ݒ�
	//�W���I�Ȑݒ�(�[�x�e�X�g���s���A�������݋��A�[�x����������΍��i)
	gpipeline.DSVFormat = DXGI_FORMAT_D32_FLOAT;//�[�x�l�t�H�[�}�b�g
	gpipeline.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
	gpipeline.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_ALWAYS;

	//���[�g�V�O�l�`���̐���
	//�f�X�N���v�^�����W
	CD3DX12_DESCRIPTOR_RANGE descRangeSRV;
	descRangeSRV.Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0);//t0���W�X�^

	//���[�g�p�����[�^
	CD3DX12_ROOT_PARAMETER rootparams[2];
	rootparams[0].InitAsConstantBufferView(0, 0, D3D12_SHADER_VISIBILITY_ALL);//�萔�o�b�t�@�r���[�Ƃ��ď�����(b0)
	rootparams[1].InitAsDescriptorTable(1, &descRangeSRV, D3D12_SHADER_VISIBILITY_ALL);

	//�e�N�X�`���T���v���[
	CD3DX12_STATIC_SAMPLER_DESC samplerDesc = CD3DX12_STATIC_SAMPLER_DESC(0);

	//���[�g�V�O�l�`���̐ݒ�
	CD3DX12_VERSIONED_ROOT_SIGNATURE_DESC rootSignatureDesc;
	rootSignatureDesc.Init_1_0(_countof(rootparams), rootparams, 1, &samplerDesc,
		D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

	ComPtr< ID3DBlob> rootSigBlob;
	//�o�[�W������������ł̃V���A���C�Y
	result = D3DX12SerializeVersionedRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1_0,
		&rootSigBlob, &errorBlob);

	//���[�g�V�O�l�`���̐���
	result = dxCommon->GetDevice()->CreateRootSignature(0, rootSigBlob->GetBufferPointer(), rootSigBlob->GetBufferSize(),
		IID_PPV_ARGS(&rootSignature));

	//�O���t�B�b�N�p�C�v���C���X�e�[�g�̐ݒ�ɃZ�b�g
	gpipeline.pRootSignature = rootSignature.Get();

	result = dxCommon->GetDevice()->CreateGraphicsPipelineState(&gpipeline, IID_PPV_ARGS(&pipelineState));
}
