#include "Player.h"

using namespace DirectX;

Input* Player::input = nullptr;
bool Player::isInput = false;

Player::Player()
{
	turretObj = std::make_unique<Object3d>();
	bodyObj = std::make_unique<Object3d>();
	nBullet = std::make_unique<NormalBullet>(20);
	//fireParticle = std::make_unique<FireParticle>();
	hitParticle = std::make_unique<HitParticle>();
	laser = std::make_unique<Laser>();
}

Player::~Player()
{
}

//������
void Player::Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, UINT texNum)
{
	turretObj->Initialize(loader->GetModel(Loader::ModelIndex::TURRET));
	turretObj->SetColor(Vector3(0.7f,0.13f,0.13f));

	bodyObj->Initialize(loader->GetModel(Loader::ModelIndex::BODY));
	bodyObj->SetColor(Vector3(0.7f, 0.13f, 0.13f));

	position = Vector3(0.0f, 0.0f, -20.0f);

	scale = Vector3(0.6f, 0.6f, 0.6f);
	rotation = Vector3::Zero;
	
	//�J�����֘A
	distanceY = 1.0f;
	distanceZ = 3.5f;
	eye = Vector3(position.x, position.y + distanceY, position.z - distanceZ);
	target = position;
	cameraRightAngle = 0.0f;//�J�������̉������̉�]�p�x(�o�x�̂悤��)
	sensibility = 0.001f;

	adjustment = Vector3(0.0f, -0.4f, 0.0f);
	bodyRotation = Vector3(0.0f, 90.0f, 0.0f);
	
	hp = 5;//�v���C���[�̗̑�
	speed = 0.6f;//�e�̃X�s�[�h

	interval = 0;

	knockBack = false;

	invincible = 120;
	normal = invincible;

	//�e
	nBullet->Initialize(dxCommon, textureManager, texNum);//�e�̏�����

	//fireParticle->Initialize(dxCommon, textureManager, texNum);
	hitParticle->Initialize(dxCommon, textureManager, texNum);//���������ۂ̃p�[�e�B�N���̏�����
	hitParticle->SetRedFlag(true);

	laser->Initialize(dxCommon, textureManager, texNum);//�⏕���̏�����
	laser->SetParent(turretObj.get());//�v���C���[�I�u�W�F�N�g��⏕���I�u�W�F�N�g�̐e�ɂ���
}
//�X�V����
void Player::Update()
{
	//��Ԃ̖C���̏���
	turretObj->Update();
	turretObj->SetPosition(position + adjustment);
	turretObj->SetRotation(rotation);
	turretObj->SetScale(scale);
	//��Ԃ̎ԑ̂̏���
	bodyObj->Update();
	bodyObj->SetPosition(position + adjustment);
	bodyObj->SetRotation(bodyRotation);
	bodyObj->SetScale(scale);

	if (liveFlag)
	{
		TPSCameraUpdate();//�J�����̓���
		ObjectRot();//�I�u�W�F�N�g�̉�]
		Move();//�v���C���[�̓���
	}
}

void Player::Draw(DirectXCommon* dxCommon)
{
	if (liveFlag)
	{
		if (normal > invincible)
		{
			turretObj->Draw(dxCommon->GetCommandList());//�v���C���[
			bodyObj->Draw(dxCommon->GetCommandList());//�v���C���[
			laser->Draw(dxCommon);//�⏕��
		}
		else
		{
			if (normal % 4 == 0)
			{
				turretObj->Draw(dxCommon->GetCommandList());//�v���C���[
				bodyObj->Draw(dxCommon->GetCommandList());//�v���C���[
				laser->Draw(dxCommon);//�⏕��
			}
		}
		nBullet->Draw(dxCommon);//�e
		hitParticle->Draw(dxCommon);
		//fireParticle->Draw(dxCommon);//���ˎ��̃p�[�e�B�N��
	}
}

void Player::Move()
{
	//�����̌v�Z
	Vector3 direction = Vector3(target.x - eye.x, 0.0f, target.z - eye.z);
	//���K��
	direction.Normalize();
	velocity = Vector3::Zero;
	//����
	if (input->KeyPress(DIK_W) || input->KeyPress(DIK_S))
	{
		if (input->KeyPress(DIK_W))
		{
			velocity += direction * 0.1f;
			dirVel = direction * 0.1f;
		}
		if (input->KeyPress(DIK_S))
		{
			velocity -= direction * 0.1f;
			dirVel = direction * 0.1f;
		}
		isInput = true;
	}

	if (interval == 0)
	{
		//���N���b�N�Œe�̔���
		if (input->MouseButtonTrigger(0))
		{
			nBullet->Fire();//�e�̔��ˊ֐��Ăяo��
			vel = Vector3(direction.x * 0.125f, 0.0f, direction.z * 0.125f);//�m�b�N�o�b�N�p��velocity
			recoil = Vector3(direction.x * 0.01f, 0.0f, direction.z * 0.01f);
			knockBack = true;
			//fireParticle->SetSpawnFlag(true);
		}
	}

	position += velocity;
	
	//�e���������ۂ̔���
	if (knockBack)
	{
		interval++;
		if (interval <= 26)
		{
			position -= vel;
			vel -= recoil;
		}
		else if(interval > 26)
		{
			vel = Vector3::Zero;
			interval = 0;
			knockBack = false;
		}
	}
	else
	{
		vel = Vector3::Zero;
		interval = 0;
	}

	//�_���[�W�󂯂��ۂ̖��G����
	if (normal != invincible + 1)
	{
		normal++;
	}

	nBullet->Update(position, direction * speed);//�e�̍X�V����

	hitParticle->Update(position);
	//fireParticle->Update(position);//���˂����ۂ̃p�[�e�B�N���̍X�V����

	laser->Update();//�⏕���̍X�V����

	//�����ĂȂ�������Ō��False��Ԃ�
	isInput = false;

	//�̗͂�0�ɂȂ����玀�S
	if (hp <= 0)
	{
		liveFlag = false;
	}
}

void Player::TPSCameraUpdate()
{
	//�J�����̒Ǐ]
	eye = Vector3(position.x, position.y + distanceY, position.z - distanceZ);
	target = position;
	//�J�����̉�]
	cameraRightAngle += input->MouseXMove() * sensibility;
	eye.x = target.x - (sinf(cameraRightAngle) * distanceZ);
	eye.z = target.z - (cosf(cameraRightAngle) * distanceZ);
}

void Player::ObjectRot()
{
	//��Ԃ̖C���̌����̌v�Z
	Vector3 TurretDirection = target - eye;
	rotation.y = atan2f(TurretDirection.z, TurretDirection.x) * (-57.325f) + 180.0f;

	//��Ԃ̎ԑ̂̌����̌v�Z
	if (fabsf(dirVel.z) > 0 && fabsf(dirVel.x) > 0)
	{
		float bodyDirection = atan2f(dirVel.z, dirVel.x);

		bodyRotation.y = bodyDirection * (-57.325f) + 180.0f;
	}
}

void Player::Reset()
{
	nBullet->Reset();
	SetHp(5);
	cameraRightAngle = 0;
}

void Player::Damage()
{
	if (normal > invincible)
	{
		hp--;
		hitParticle->SetSpawnFlag(true);
		normal = 0;
	}
}

