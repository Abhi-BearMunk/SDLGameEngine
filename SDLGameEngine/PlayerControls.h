#pragma once
#include "Behaviour.h"
class PlayerControls :
	public Behaviour
{
public:
	PlayerControls();
	~PlayerControls();

	float xSpeed = 150;
	float ySpeed = 150;

	virtual void Update();
};

