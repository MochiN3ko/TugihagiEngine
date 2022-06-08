#include "EnemyBullet.h"

EnemyBullet::EnemyBullet(int a)
{
	size = a;//�T�C�Y
	for (int i = 0; i < size; ++i)
	{
		object.emplace_back(new Bullet());
	}
}

EnemyBullet::~EnemyBullet()
{
	for (int i = 0, size = object.size(); i < size; i++)
	{
		delete object[i];
	}
}

void EnemyBullet::Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, UINT texNum)
{
	for (int i = 0, size = object.size(); i < size; i++)
	{
		object[i]->Initialize(dxCommon, textureManager, texNum);//������
		object[i]->SetReverseCount(1);//���ˉ񐔐ݒ�
	}
	a = 0;//���˃��[�g�p�̃J�E���g
	b = 0;//�e�̃J�E���g

	speed = 0.2f;//�e�̑��x

}

void EnemyBullet::Update(Vector3 p, Player* player)
{
	for (int i = 0, size = object.size(); i < size; i++)
	{
		if (!object[i]->GetLiveFlag())
		{
			//�v���C���[�ƃG�l�~�[�̌����𒲂ׂ�
			Vector3 direction = player->GetPosition() - p;
			Vector3 directionRot = player->GetPosition() - p;
			//���K��
			direction.Normalize();
			//��������
			object[i]->SetVelocity(direction * speed);
			//LiveFlag��False�̏ꍇ�͕`�悵�Ȃ��Ŏw�肵���|�W�V�����ɑҋ@
			object[i]->SetPosition(p);
		}
		else
		{
			//�e�̌����v�Z
			float direction = atan2f(object[i]->GetVelocity().z, object[i]->GetVelocity().x);

			object[i]->SetRotation(Vector3(0.0f, direction * -57.325f - 90.0f, 0.0f));
		}
		
		
		object[i]->Update();//�I�u�W�F�N�g�̍X�V����
		//���˂ł���񐔂�0����������������
		if (object[i]->GetReverseCount() < 0)
		{
			object[i]->SetLiveFlag(false);//���S�t���O
			object[i]->SetReverseCount(1);//���ˉ񐔃��Z�b�g
		}
	}
	a++;
	//�e�̔��ˊԊu
	b = a / 100;
	//���Ԃɒe�𔭎˂���
	if (b < size)
	{
		object[b]->SetLiveFlag(true);
	}
	else
	{
		//b���v�f���𒴂�����J�E���g��������
		a = 0;
	}

}

void EnemyBullet::Draw(DirectXCommon* dxCommon)
{
	for (int i = 0, size = object.size(); i < size; i++)
	{
		object[i]->Draw(dxCommon);//�`�揈��
	}
}

void EnemyBullet::Reset()
{
	for (int i = 0, size = object.size(); i < size; i++)
	{
		object[i]->SetLiveFlag(false);//�t���O���Z�b�g
	}
}
