#include "Shoot.h"
#include "Input.h"
#include "Game.h"



Shoot::Shoot()
{
}


Shoot::~Shoot()
{
}

void Shoot::Update()
{
	Behaviour::Update();
	// Shoot
	if (Input::GetMouseButtonDown(SDL_BUTTON_LEFT))
	{
		Instantiate(game->Prefab("Bullet"), gameObject->transform->GetAbsolutePosition() - 50 * gameObject->transform->Up(), gameObject->transform->GetAbsoluteAngle() + 180);
	}
}
