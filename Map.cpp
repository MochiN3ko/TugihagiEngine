#include "Map.h"
#include<fstream>
#include<sstream>
#include<string>

void Map::Initialize()
{
	chipsize = 3;
	nowmap = 0;
	position = Vector3(-13.0f, 0.0f, 7.0f);

	p = 3;//�v���C���[
	n = 4;//�����Ȃ��G�l�~�[

#pragma region �X�e�[�W�f�[�^

#pragma region 1�X�e�[�W��

	mapchip[0] = {

		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1 },
		{1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1 },
		{1,2,2,2,2,n,2,2,2,2,2,2,2,n,2,2,2,2,1 },
		{1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1 },
		{1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1 },
		{1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1 },
		{1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1 },
		{1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1 },
		{1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1 },
		{1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1 },
		{1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1 },
		{1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1 },
		{1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1 },
		{1,2,2,2,2,2,2,2,2,p,2,2,2,2,2,2,2,2,1 },
		{1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1 },
		{1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1 },
		{1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1 },
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	};

#pragma endregion

#pragma endregion

	for (int i = 0; i < MAP_COUNT; i++)
	{
		for (int z = 0; z < MAP_SIZE_Z; z++)
		{
			for (int x = 0; x < MAP_SIZE_X; x++)
			{
				//�����Ȃ�
				if (mapchip[i][z][x] == NOTHING)
				{
				}
				//��
				if (mapchip[i][z][x] == WALL)
				{
					wall[i].emplace_back(Vector3(position.x + chipsize * x, 0.0f,position.z - chipsize * z));
				}
				//���ƓV��
				if (mapchip[i][z][x] == FLOORCEILING)
				{
					floor[i].emplace_back(Vector3(position.x + chipsize * x, -3.0f, position.z - chipsize * z));
					ceiling[i].emplace_back(Vector3(position.x + chipsize * x, 3.0f, position.z - chipsize * z));
				}
				//�v���C���[�̏����ʒu
				if (mapchip[i][z][x] == PLAYER)
				{
					player[i] = Vector3(position.x + chipsize * x, -2.5f, position.z - chipsize * z);
					floor[i].emplace_back(Vector3(position.x + chipsize * x, -3.0f, position.z - chipsize * z));
					ceiling[i].emplace_back(Vector3(position.x + chipsize * x, 3.0f, position.z - chipsize * z));
				}
				//�����Ȃ��G�l�~�[�̏����ʒu
				if (mapchip[i][z][x] == NORMALENEMY)
				{
					normalEnemies[i].emplace_back(Vector3(position.x + chipsize * x, -2.5f, position.z - chipsize * z));
					floor[i].emplace_back(Vector3(position.x + chipsize * x, -3.0f, position.z - chipsize * z));
					ceiling[i].emplace_back(Vector3(position.x + chipsize * x, 3.0f, position.z - chipsize * z));
				}
				//�l�p�ɓ����G�l�~�[�̏����ʒu
				if (mapchip[i][z][x] == SQUAREENEMY)
				{
					squareEnemies[i].emplace_back(Vector3(position.x + chipsize * x, -2.5f, position.z - chipsize * z));
					floor[i].emplace_back(Vector3(position.x + chipsize * x, -3.0f, position.z - chipsize * z));
					ceiling[i].emplace_back(Vector3(position.x + chipsize * x, 3.0f, position.z - chipsize * z));
				}
			}
		}
	}
}

void Map::Reset()
{

}


int Map::GetFloorMax()
{
	std::vector<Vector3> result = floor[0];
	int a = floor[0].size();
	for (int i = 0; i < MAP_COUNT; i++)
	{
		//�擪�������Ă���
		if (result.size() < floor[i].size())
		{
			result = floor[i];
			a = floor[i].size();
		}
	}
	return a;
}

int Map::GetCeilingMax()
{
	std::vector<Vector3> result = ceiling[0];
	int a = ceiling[0].size();
	for (int i = 0; i < MAP_COUNT; i++)
	{
		//�擪�������Ă���
		if (result.size() < ceiling[i].size())
		{
			result = ceiling[i];
			a = ceiling[i].size();
		}
	}
	return a;
}

int Map::GetWallMax()
{
	std::vector<Vector3> result = wall[0];
	int a = wall[0].size();
	for (int i = 0; i < MAP_COUNT; i++)
	{
		//�擪�������Ă���
		if (result.size() < wall[i].size())
		{
			result = wall[i];
			a = wall[i].size();
		}
	}
	return a;
}

int Map::GetEnemyMax()
{
	std::vector<Vector3> result = normalEnemies[0];
	int a = normalEnemies[0].size();
	for (int i = 0; i < MAP_COUNT; i++)
	{
		//�擪�������Ă���
		if (result.size() < normalEnemies[i].size())
		{
			result = normalEnemies[i];
			a = normalEnemies[i].size();
		}
	}
	return a;
}

