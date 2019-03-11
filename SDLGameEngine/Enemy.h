#pragma once
#include "Behaviour.h"
#include "Transform.h"
class Enemy :
	public Behaviour
{
public:
	Enemy();
	~Enemy();

	void Update();

	bool playerDetected = true;
	Transform* player;
	float time = 3;
	float timer = 3;
};

