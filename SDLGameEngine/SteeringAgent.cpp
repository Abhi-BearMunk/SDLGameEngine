#include "SteeringAgent.h"
#include "GameObject.h"
#include "Transform.h"
#include "Game.h"
#include "Time.h"


SteeringAgent::SteeringAgent()
{
}

SteeringAgent::SteeringAgent(GameObject* go) : Behaviour(go)
{
}

SteeringAgent::~SteeringAgent()
{
}

void SteeringAgent::Start()
{
	rb = gameObject->GetComponent<Rigidbody>();
	//rb->SetMass(0.01f);
}


void SteeringAgent::Update()
{
	for (SteeringBehaviour* steering : steerings)
	{
		if (rb)
		{
			rb->AddForce(steering->steering.weight * steering->steering.linear * 100);
		}
		velocity += steering->steering.weight * steering->steering.linear;
		angularSpeed += steering->steering.weight * steering->steering.angular;
	}
	if (velocity.Length() > maxSpeed)
	{
		velocity.Normalize();
		velocity *= maxSpeed;
	}

	//gameObject->transform->SetAbsolutePositionDelta(velocity * Time::DeltaTime());
	//gameObject->transform->angle += (angularSpeed / 60.0f) * 180.0f / M_PI;
	if (rb)
	{
		gameObject->transform->SetAbsoluteAngle(atan2(rb->GetVelocity().y, rb->GetVelocity().x) * 180.0f / M_PI + 90.0f);
	}

	SDL_SetRenderDrawColor(Game::gRenderer, 0x00, 0xFF, 0x00, 0xFF);
	SDL_RenderDrawLine(Game::gRenderer, gameObject->transform->GetAbsolutePosition().x - Camera::x, gameObject->transform->GetAbsolutePosition().y - Camera::y, gameObject->transform->GetAbsolutePosition().x + rb->GetVelocity().x - Camera::x, gameObject->transform->GetAbsolutePosition().y + rb->GetVelocity().y - Camera::y);
	Behaviour::Update();
}
