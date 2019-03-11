#include "ChangeColor.h"
#include "GameObject.h"
#include "Transform.h"



ChangeColor::ChangeColor()
{
}


ChangeColor::~ChangeColor()
{
}

void ChangeColor::Awake()
{
	Behaviour::Awake();
	triggerEventListener = std::make_shared<EventListener<Collider*>>(std::bind(&ChangeColor::OnTriggerEnter, this, std::placeholders::_1));
	gameObject->OnTriggerEnter.AddListener(triggerEventListener);
}

void ChangeColor::Cleanup()
{
	Behaviour::Cleanup();
	gameObject->OnTriggerEnter.RemoveListener(triggerEventListener);
}

void ChangeColor::OnTriggerEnter(Collider* col)
{
	if (col->gameObject->name == "Player")
	{
		gameObject->GetComponent<SpriteRenderer>()->SetColor(triggerColor);
	}
}
