#include "SmokeParticle.h"

SmokeParticle::SmokeParticle()
{
	for (int i = 0; i < size; ++i)
	{
		object.emplace_back(new Particle());
	}
}

SmokeParticle::~SmokeParticle()
{
	for (const auto& x : object)
	{
		delete x;
	}
}

void SmokeParticle::Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, UINT texNum)
{
	size_t size = object.size();
	for (int i = 0; i < size; ++i)
	{
		object[i]->Initialize(dxCommon, textureManager, texNum);
		//�T�C�Y�������_���Őݒ�
		float rs = rand() % 2 + 1;
		object[i]->SetScale(Vector3(rs / 10, rs / 10, rs / 10));
	}
	a = 0;
	red = false;
}

void SmokeParticle::Update(const Vector3& p)
{
	size_t size = object.size();
	for (int i = 0; i < size; ++i)
	{
		object[i]->Update();
		if (object[i]->GetLiveFlag())
		{
			//�J���[�̈ڂ�ς��
			if (red)
			{
				object[i]->SetColor(Vector3(1, object[i]->GetTime() / 15.0f, 0));
				object[i]->SetScale(object[i]->GetScale() - Vector3(0.1f, 0.1f, 0.1f));
			}
			else
			{
				object[i]->SetScale(object[i]->GetScale() - Vector3(0.03f, 0.03f, 0.03f));
				object[i]->SetColor(Vector3(object[i]->GetTime() / 60.0f, object[i]->GetTime() / 60.0f, 1));
			}
		}
		else
		{
			//�T�C�Y�ƃ|�W�V�����w��
			float rs = rand() % 2 + 1;
			object[i]->SetScale(Vector3(rs / 10, rs / 10, rs / 10));
			float rnd = rand() % 10 - 5;
			object[i]->SetPosition(p + Vector3(0.0f, 0.1f, rnd / 10));
		}
	}

	//���Ԃɉ����o��
	if (a < object.size())
	{
		object[a]->SetLiveFlag(true);
	}
	else
	{
		a = 0;
	}

	a++;
}

void SmokeParticle::Draw(DirectXCommon* dxCommon)
{
	for (auto& o : object)
	{
		o->Draw(dxCommon);
	}
}




