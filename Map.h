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
	static const int MAP_SIZE_X = 19;//X方向の壁の数
	static const int MAP_SIZE_Z = 19;//Z方向の壁の数
	static const int MAP_COUNT = 1;//マップの数及び読み込む番号

	std::vector<std::vector<int>> mapchip[MAP_COUNT];
	
	Vector3 position;
	float chipsize;//一個分のサイズ（間隔）
	int nowmap;

	//ゲームオブジェクトの初期位置用
	Vector3 player[MAP_COUNT];
	std::vector<Vector3> floor[MAP_COUNT];//床
	std::vector<Vector3> ceiling[MAP_COUNT];//天井
	std::vector<Vector3> wall[MAP_COUNT];//壁
	std::vector<Vector3> normalEnemies[MAP_COUNT];//動かないエネミー
	std::vector<Vector3> squareEnemies[MAP_COUNT];//四角に動くエネミー

	//各オブジェクトの番号変数
	int p;//プレイヤー
	int n;//動かないエネミー

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

