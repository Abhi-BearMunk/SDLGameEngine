#pragma once
#include "Game.h"
class MidtermGame :
	public Game
{
public:
	MidtermGame();
	~MidtermGame();

	void Awake();
	void Setup();

	void BulletPrefab(GameObject* go);
	void EnemyPrefab(GameObject* go);
	void WallPrefab(GameObject* go);
	void WallBlockPrefab(GameObject* go);
	void GatePrefab(GameObject* go);
	void FloorPrefab(GameObject* go);
};

