#include "PlayerControls.h"
#include "GameObject.h"
#include "Transform.h"
#include "Time.h"
#include "Input.h"
#include "Game.h"
#include "RaycastHit.h"
#include "Rigidbody.h"

PlayerControls::PlayerControls()
{
}


PlayerControls::~PlayerControls()
{
}

void PlayerControls::Update()
{
	// Horizontal
	int horizontal = Input::GetKey(SDLK_d) ? 1 : Input::GetKey(SDLK_a) ? -1 : 0;
	
	// Vertical
	int vertical = Input::GetKey(SDLK_w) ? -1 : Input::GetKey(SDLK_s) ? 1 : 0;

	/*if (gameObject->GetComponent<Rigidbody>()->GetVelocity().Dot(Vector2(horizontal * xSpeed, vertical * ySpeed)) < 100)
	{
		gameObject->GetComponent<Rigidbody>()->AddForce(Vector2(horizontal * xSpeed, vertical * ySpeed));
	}*/
	gameObject->GetComponent<Rigidbody>()->SetVelocity(Vector2(horizontal * xSpeed, vertical * ySpeed));
	//gameObject->transform->SetAbsolutePositionDelta(Vector2(horizontal * xSpeed * Time::DeltaTime(), vertical * ySpeed * Time::DeltaTime()));
	
	// Orientation
	if (vertical != 0 || horizontal != 0)
	{
		gameObject->transform->SetAbsoluteAngle(atan2(vertical, horizontal) * 180 / M_PI);
	}

	RaycastHit hit = game->physics->Raycast(gameObject->transform->GetAbsolutePosition(), gameObject->transform->Right(), 10000, ~game->physics->Layer_2);
}
