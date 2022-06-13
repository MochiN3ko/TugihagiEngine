#pragma once
#include"Vector2.h"
#include"Vector3.h"
#include<vector>

class Map
{
	enum MapName
	{
		NOTHING,
		WALL,
		FLOORCEILING,
		PLAYER,
		NORMALENEMY,
		SQUAREENEMY
	};

private:
	static const int MAP_SIZE_X = 19;//X�����̕ǂ̐�
	static const int MAP_SIZE_Z = 19;//Z�����̕ǂ̐�
	static const int MAP_COUNT = 1;//�}�b�v�̐��y�ѓǂݍ��ޔԍ�

	std::vector<std::vector<int>> mapchip[MAP_COUNT];
	
	Vector3 position;
	float chipsize;//����̃T�C�Y�i�Ԋu�j
	int nowmap;

	//�Q�[���I�u�W�F�N�g�̏����ʒu�p
	Vector3 player[MAP_COUNT];
	std::vector<Vector3> floor[MAP_COUNT];//��
	std::vector<Vector3> ceiling[MAP_COUNT];//�V��
	std::vector<Vector3> wall[MAP_COUNT];//��
	std::vector<Vector3> normalEnemies[MAP_COUNT];//�����Ȃ��G�l�~�[
	std::vector<Vector3> squareEnemies[MAP_COUNT];//�l�p�ɓ����G�l�~�[

	//�e�I�u�W�F�N�g�̔ԍ��ϐ�
	int p;//�v���C���[
	int n;//�����Ȃ��G�l�~�[

public:

	void Initialize();
	void Reset();
	void SetNowMap(int map) { nowmap = map; }

	//Getter
	Vector3 GetPlayerPosition() { return player[nowmap]; }
	std::vector<Vector3> GetNEnemy(){ return normalEnemies[nowmap]; }
	std::vector<Vector3> GetFloor(){ return floor[nowmap]; }
	std::vector<Vector3> GetCeiling(){ return ceiling[nowmap]; }
	std::vector<Vector3> GetWall(){ return wall[nowmap]; }

	int GetFloorMax();
	int GetCeilingMax();
	int GetWallMax();
	int GetEnemyMax();
};

