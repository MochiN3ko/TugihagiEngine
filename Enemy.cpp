#include "Enemy.h"
#include<time.h>

Player* Enemy::player = nullptr;
std::vector<Bullet*> Enemy::pBullet;

Enemy::Enemy()
{
	turretObj = std::make_unique<Object3d>();
	bodyObj = std::make_unique<Object3d>();
	eBullet = std::make_unique<EnemyBullet>(5);
	hitParticle = std::make_unique<HitParticle>();
}

Enemy::~Enemy()
{
}

void Enemy::Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, UINT texNum)
{
	turretObj->Initialize(loader->GetModel(Loader::ModelIndex::TURRET));//��Ԃ̖C���̃I�u�W�F�N�g�̏�����
	turretObj->SetColor(Vector3(0.0f, 0.0f, 1.0f));

	bodyObj->Initialize(loader->GetModel(Loader::ModelIndex::BODY));//��Ԃ̎ԑ̂̃I�u�W�F�N�g�̏�����
	bodyObj->SetColor(Vector3(0.0f, 0.0f, 1.0f));

	scale = Vector3(0.6f, 0.6f, 0.6f);//�I�u�W�F�N�g�̃T�C�Y
	adjustment = Vector3(0.0f, -0.4f, 0.0f);//�ʒu����
	reverseCount = 0;

	position = Vector3::Zero;//�ʒu�ݒ�
	velocity = Vector3(0.05f, 0.0f, 0.0f);//�ړ����x�̏����l
	eBullet->Initialize(dxCommon, textureManager, texNum);//�e�̏�����
	hitParticle->Initialize(dxCommon, textureManager, texNum);//���������ۂ̃p�[�e�B�N���̏�����
}

void Enemy::Update()
{
	if (liveFlag)
	{
		Vector3 direction = player->GetPosition() - position;
		rotation.y = rotation.y = atan2f(direction.z, direction.x) * (-57.325f) + 180.0f;
		//��Ԃ̖C���̏���
		turretObj->Update();//�X�V����
		turretObj->SetPosition(position + adjustment);//�ʒu�̍X�V
		turretObj->SetRotation(rotation);//��]�̍X�V
		turretObj->SetScale(scale);//�T�C�Y�̍X�V
		//��Ԃ̎ԑ̂̏���
		bodyObj->Update();//�X�V����
		bodyObj->SetPosition(position + adjustment);//�ʒu�̍X�V
		bodyObj->SetRotation(Vector3(0.0f, 0.0f, 0.0f));//��]�̍X�V
		bodyObj->SetScale(scale);//�T�C�Y�̍X�V

		Hit();//�����蔻��֐�
		position += velocity;//�ړ�����
		reverseCount++;
		//�J�E���g����萔�������甽�]
		if (reverseCount >= 150)
		{
			velocity.x *= -1.0f;
			reverseCount = 0;
		}
		
		eBullet->Update(position, player);//�e�̍X�V����
	}
	hitParticle->Update(position);//���������ۂ̃p�[�e�B�N���̍X�V����
}

void Enemy::Draw(DirectXCommon* dxCommon)
{
	if (liveFlag)
	{
		turretObj->Draw(dxCommon->GetCommandList());//��Ԃ̖C���̕`��
		bodyObj->Draw(dxCommon->GetCommandList());//��Ԃ̎ԑ̂̕`��
		eBullet->Draw(dxCommon);//�e�̕`��
	}
	hitParticle->Draw(dxCommon);//���������ۂ̃p�[�e�B�N���̕`��
}

void Enemy::Hit()
{
	//�G�ƃv���C���[�̕��ʂ̒e�̓����蔻��
	for (int i = 0, size = pBullet.size(); i < size; i++)
	{
		if (pBullet[i]->GetLiveFlag())
		{
			if (SphereAndSphere(position, pBullet[i]->GetPosition(), scale.z, pBullet[i]->GetScale().z))
			{
				//soundManager->PlayWave("Resources/sound/hit2.wav");

				//���������ʂ�����
				pBullet[i]->SetLiveFlag(false);
				//�G�t�F�N�g
				hitParticle->SetSpawnFlag(true);
				//�G��������
				liveFlag = false;
			}
		}
	}
	//�G�̒e�ƃv���C���[
	for (int i = 0, size = eBullet->GetBullet().size(); i < size; i++)
	{
		if (eBullet->GetBullet()[i]->GetLiveFlag())
		{
			if (SphereAndSphere(player->GetPosition(), eBullet->GetBullet()[i]->GetPosition(), player->GetScale().x, eBullet->GetBullet()[i]->GetScale().y))
			{
				//soundManager->PlayWave("Resources/sound/hit2.wav");

				//���������ʂ�����
				eBullet->GetBullet()[i]->SetLiveFlag(false);
				eBullet->GetBullet()[i]->SetPosition(position);
				//�v���C���[�̗̑͂����炷
				//player->SetHp(player->GetHp() - 1);
				player->Damage();
			}
		}
	}
}

void Enemy::Reset()
{
	eBullet->Reset();
}


