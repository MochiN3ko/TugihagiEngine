#pragma once
#include"Vector2.h"
#include"Vector3.h"
#include<DirectXMath.h>
class Camera
{
public://�G�C���A�X
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();
	/// <summary>
	/// �X�V
	/// </summary>
	void Update();
	/// <summary>
	/// �r���[�s��ϊ��̌v�Z
	/// </summary>
	void UpdateViewMatrix();
	/// <summary>
	/// �������e
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
	XMMATRIX matView;				//�r���[�s��
	XMMATRIX matProjection;			//�ˉe�s��
	XMFLOAT3 eye;					//���_���W
	XMFLOAT3 target;				//�����_���W
	XMFLOAT3 up;					//������x�N�g��
	XMMATRIX matBillboard;		    //�S�����r���{�[�h
	XMMATRIX matBillboardY;	        //Y���r���{�[�h
};

