#include "Triangle.h"

Model* Triangle::model = nullptr;
std::vector<Player*> Triangle::player;
Triangle::Triangle()
{
	model = new Model();
	object = new Object3d();
}
Triangle::~Triangle()
{
	delete object;
}
void Triangle::SetTrianglePosition(Vector3 pos1, Vector3 pos2, Vector3 pos3)
{
	this->pos1 = pos1;
	this->pos2 = pos2;
	this->pos3 = pos3;
	model->LoadTriangle(pos1, pos2, pos3);
}
void Triangle::Load(std::string filename)
{
}
void Triangle::StaticFinalize()
{
	delete model;
}
void Triangle::Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, UINT texNum)
{
	model->Initialize(dxCommon, textureManager, texNum);

	object->Initialize(model);

	scale = Vector3(1, 1, 1);
}

void Triangle::Update()
{
		object->Update();
	if (liveFlag)
	{
		Vector3 p1p2 = pos2 - pos1;
		Vector3 p2p3 = pos3 - pos2;
		Vector3 p3p1 = pos1 - pos3;

		for (int i = 0; i < player.size(); i++)
		{
			if (TriangleAndPoint(pos1, pos2, pos3, player[i]->GetPosition()+player[i]->GetVelocity()))
			{
				if (Player::GetInputFlag()!=0)
				{
					if (player[i]->GetPosition().x < pos1.x)
					{
						if (Player::GetInputFlag() == 1)
						{
							player[i]->SetVelocity(Vector3(p3p1.normalize() / 3));
						}
						else if (Player::GetInputFlag() == -1)
						{
							player[i]->SetVelocity(Vector3(-p3p1.normalize() / 3));
						}
					}
					else
					{
						if (Player::GetInputFlag() == 1)
						{
							player[i]->SetVelocity(Vector3(p1p2.normalize() / 3));
						}
						else if (Player::GetInputFlag() == -1)
						{
							player[i]->SetVelocity(Vector3(-p1p2.normalize() / 3));
						}
					}
				}
				else
				{
					player[i]->SetVelocity(Vector3());
				}
			}
		}
	}
}
void Triangle::Draw(DirectXCommon* dxCommon)
{
	if (liveFlag)
	{
		object->Draw(dxCommon->GetCommandList());
	}
}
