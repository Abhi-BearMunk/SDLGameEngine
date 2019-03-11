#pragma once
#include "Behaviour.h"
#include "Color.h"
#include "SpriteRenderer.h"
#include "EventListener.h"
#include "Collider.h"

class ChangeColor :
	public Behaviour
{
public:
	ChangeColor();
	~ChangeColor();

	Color triggerColor = Color(0, 255, 0, 128);

	void Awake();
	//void Update();
	void Cleanup();
	std::shared_ptr<EventListener<Collider*>> triggerEventListener = NULL;
	void OnTriggerEnter(Collider* col);
};

