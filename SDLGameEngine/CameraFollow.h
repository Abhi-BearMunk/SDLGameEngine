#pragma once
#include "Behaviour.h"
class CameraFollow :
	public Behaviour
{
public:
	CameraFollow();
	~CameraFollow();

	void FixedUpdate();
};

