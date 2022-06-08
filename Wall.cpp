#include "Wall.h"

Player* Wall::player;
std::vector<Bullet*> Wall::pBullet;

Wall::Wall()
{
	object = std::make_unique<Object3d>();
}

Wall::~Wall()
{
}

void Wall::Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, UINT texNum)
{
	object->Initialize(loader->GetModel(Loader::ModelIndex::WALL));

	scale = Vector3(3.0f, 6.0f, 3.0f);
}

void Wall::Update()
{
	if (liveFlag)
	{
		object->Update();
		object->SetPosition(position);
		object->SetRotation(rotation);
		object->SetScale(scale);

		//�ǂƃv���C���[�̓����蔻��
		if (RectangleAndSphere2D(position - scale, position + scale, player->GetPosition() + player->GetVelocity(), player->GetScale().z))
		{
			player->SetPosition(Vector3(player->GetPosition().x - player->GetVelocity().x, player->GetPosition().y, player->GetPosition().z - player->GetVelocity().z));
		}
		//�ǂƃv���C���[�̕��ʂ̒e�̓����蔻��
		WallBulletHit(pBullet);
	}
}

void Wall::WallBulletHit(const std::vector<Bullet*> bullet)
{
	//�ǂƒe�̓����蔻��
	for (int i = 0, size = bullet.size(); i < size; i++)
	{
		if (bullet[i]->GetLiveFlag())
		{
			//�e�̉E���̓����蔻��
			if (RectangleAndSphere2D(position - scale, position + scale, bullet[i]->GetRightPoint() + bullet[i]->GetVelocity(), bullet[i]->GetPointSize()))
			{
				//�o�E���h
				bullet[i]->SetVelocity(Vector3(bullet[i]->GetVelocity().x * -1.0f, bullet[i]->GetVelocity().y, bullet[i]->GetVelocity().z));
				//���˂ł���񐔂����炷
				bullet[i]->Counting();
			}
			//�e�̍����̓����蔻��
			if (RectangleAndSphere2D(position - scale, position + scale, bullet[i]->GetLeftPoint() + bullet[i]->GetVelocity(), bullet[i]->GetPointSize()))
			{
				//�o�E���h
				bullet[i]->SetVelocity(Vector3(bullet[i]->GetVelocity().x * -1.0f, bullet[i]->GetVelocity().y, bullet[i]->GetVelocity().z));
				//���˂ł���񐔂����炷
				bullet[i]->Counting();
			}
			//�e�̑O���̓����蔻��
			if (RectangleAndSphere2D(position - scale, position + scale, bullet[i]->GetFrontPoint() + bullet[i]->GetVelocity(), bullet[i]->GetPointSize()))
			{
				//�o�E���h
				bullet[i]->SetVelocity(Vector3(bullet[i]->GetVelocity().x, bullet[i]->GetVelocity().y, bullet[i]->GetVelocity().z * -1.0f));
				//���˂ł���񐔂����炷
				bullet[i]->Counting();
			}
			//�e�̌�둤�̓����蔻��
			if (RectangleAndSphere2D(position - scale, position + scale, bullet[i]->GetBehindPoint() + bullet[i]->GetVelocity(), bullet[i]->GetPointSize()))
			{
				//�o�E���h
				bullet[i]->SetVelocity(Vector3(bullet[i]->GetVelocity().x, bullet[i]->GetVelocity().y, bullet[i]->GetVelocity().z * -1.0f));
				//���˂ł���񐔂����炷
				bullet[i]->Counting();
			}
		}
	}
}

void Wall::Draw(DirectXCommon* dxCommon)
{
	if (liveFlag)
	{
		object->Draw(dxCommon->GetCommandList());
	}
}

