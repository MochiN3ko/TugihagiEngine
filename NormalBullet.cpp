#include "NormalBullet.h"

NormalBullet::NormalBullet(int size)
{
	this->size = size;//�e�̃T�C�Y
	for (int i = 0; i < size; ++i)
	{
		object.emplace_back(new Bullet());
	}
}

NormalBullet::~NormalBullet()
{
	oSize = object.size();
	for (int i = 0; i < oSize; ++i)
	{
		delete object[i];
	}
}

void NormalBullet::Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, UINT texNum)
{
	oSize = object.size();
	for (int i = 0; i < oSize; ++i)
	{
		object[i]->Initialize(dxCommon, textureManager, texNum);//������
		object[i]->GetObj()->SetColor(Vector3(0.7f, 0.13f, 0.13f));
		object[i]->GetSmoke()->SetRedFlag(true);
		object[i]->SetReverseCount(2);//���˂ł����
	}
	bulletCount = 0;
}

void NormalBullet::Update(const Vector3& position, const Vector3& velocity)
{
	for (int i = 0; i < oSize; ++i)
	{
		if (!object[i]->GetLiveFlag())
		{
			//�e�̑������Z�b�g
			object[i]->SetVelocity(velocity);
			//�w�肵���|�W�V�����ɑҋ@
			object[i]->SetPosition(position);
		}
		else
		{
			//�e�̌����v�Z
			float direction = atan2f(object[i]->GetVelocity().z, object[i]->GetVelocity().x);
			
			object[i]->SetRotation(Vector3(0.0f, direction * -57.325f - 90.0f, 0.0f));
		}
		object[i]->Update();


		//���˂ł���񐔂�0����������������
		if (object[i]->GetReverseCount() < 0)
		{
			object[i]->SetLiveFlag(false);
			object[i]->SetReverseCount(2);
		}
	}
}

void NormalBullet::Draw(DirectXCommon* dxCommon)
{
	for (int i = 0; i < oSize; ++i)
	{
		object[i]->Draw(dxCommon);
	}
}

void NormalBullet::Fire()
{
	//�v�f����������J�E���g������
	if (bulletCount >= size)
	{
		bulletCount = 0;
	}
	//���Ԃɔ���
	object[bulletCount]->SetLiveFlag(true);
	bulletCount++;
}

void NormalBullet::Reset()
{
	for (int i = 0; i < oSize; ++i)
	{
		object[i]->SetLiveFlag(false);
	}
}
