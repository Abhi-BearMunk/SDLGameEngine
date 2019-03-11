#include "Collider.h"
#include "GameObject.h"
#include "Rigidbody.h"
#include "Game.h"
#include "Ray.h"
#include "RaycastHit.h"
#include "Rect.h"
#include "Transform.h"
#include "TransformData.h"

Collider::Collider()
{

}


Collider::~Collider()
{
	
}

void Collider::Cleanup()
{
	if (rigidbody)
	{
		RemoveCollider(rigidbody);
	}
	gameObject->OnAddRigidbody.RemoveListener(OnRigidbodyAdded);
	gameObject->transform->OnTransformUpdate.RemoveListener(onTransformUpdate);

	//gameObject->OnRemoveRigidbody.RemoveListener(OnRigidbodyRemoved);
}

void Collider::Awake()
{
	if (gameObject->rigidbody)
	{
		AddCollider(gameObject->rigidbody);
	}
	OnRigidbodyAdded = std::make_shared<EventListener<Rigidbody*>>(std::bind(&Collider::RigidbodyAdded, this, std::placeholders::_1));
	//OnRigidbodyRemoved = std::make_shared<EventListener<Rigidbody*>>(std::bind(&RigidbodyRemoved, this));*/
	gameObject->OnAddRigidbody.AddListener(OnRigidbodyAdded);
	//gameObject->OnRemoveRigidbody.AddListener(OnRigidbodyRemoved);
	onTransformUpdate = std::make_shared<EventListener<TransformData>>(std::bind(&Collider::UpdateTransform, this, std::placeholders::_1));
	gameObject->transform->OnTransformUpdate.AddListener(onTransformUpdate);

}


void Collider::FixedUpdate()
{

	Component::FixedUpdate();
}

void Collider::SetTrigger(bool toggle)
{
	isTrigger = toggle;
	fixtureDef.isSensor = toggle;
	if (fixture)
	{
		fixture->SetSensor(toggle);
	}
}
bool Collider::GetTrigger()
{
	return isTrigger;
}

void Collider::SetCategory(uint16_t flags)
{
	if (fixture)
	{
		b2Filter filter = fixture->GetFilterData();
		filter.categoryBits = flags;
		fixture->SetFilterData(filter);
	}
	fixtureDef.filter.categoryBits = flags;
}

void Collider::SetCollisionMask(uint16_t flags)
{
	if (fixture)
	{
		b2Filter filter = fixture->GetFilterData();
		filter.maskBits = flags;
		fixture->SetFilterData(filter);
	}
	fixtureDef.filter.maskBits = flags;
}

RaycastHit Collider::Raycast(Vector2 origin, Vector2 direction, float maxDistance)
{
	b2RayCastInput input;
	input.p1 = game->physics->GetPhysicsCoordinates(origin);
	input.p2 = game->physics->GetPhysicsCoordinates(origin + direction * maxDistance);
	input.maxFraction = 1;

	RaycastHit hit;

	b2RayCastOutput output;
	if (fixture->RayCast(&output, input, 0))
	{
		hit.collider = this;
		hit.normal = Vector2(output.normal.x, output.normal.y);
		hit.point = origin + output.fraction * maxDistance * direction;

		SDL_SetRenderDrawColor(Game::gRenderer, 0x00, 0x00, 0xFF, 0xFF);
		SDL_RenderDrawLine(Game::gRenderer, origin.x - Camera::x, origin.y - Camera::y, hit.point.x - Camera::x, hit.point.y - Camera::y);
		SDL_RenderDrawRect(Game::gRenderer, new Rect(hit.point.x - Camera::x - 5, hit.point.y - Camera::y - 5, 10, 10));
	}

	return hit;
}

RaycastHit Collider::Raycast(Ray ray, float maxDistance)
{
	return Raycast(ray.origin, ray.direction, maxDistance);
}

void Collider::AddCollider(Rigidbody* _rigidbody)
{	
	rigidbody = _rigidbody;
	SetRelativeValues();
	SetFixtureDef();
	_rigidbody->AddCollider(this);
}

void Collider::RemoveCollider(Rigidbody* _rigidbody)
{
	_rigidbody->RemoveCollider(this);
	rigidbody = nullptr;
}

void Collider::RigidbodyAdded(Rigidbody* _rigidbody)
{
	if (_rigidbody != rigidbody)
	{
		if (rigidbody != nullptr)
		{
			RemoveCollider(rigidbody);
		}
		if (_rigidbody != nullptr)
		{
			AddCollider(_rigidbody);
		}
	}
}

void Collider::UpdateTransform(const TransformData &tData)
{
	SetRelativeValues();
	ResetFixture();
}

void Collider::ResetFixture()
{
	SetFixtureDef();
	if (rigidbody)
	{
		if (fixture)
		{
			rigidbody->RemoveCollider(this);
		}
		rigidbody->AddCollider(this);
	}
}



//void Collider::RigidbodyRemoved(Rigidbody* _rigidbody)
//{
//	if (_rigidbody == rigidbody)
//	{
//		RemoveCollider(rigidbody);
//
//		if (gameObject->rigidbody != nullptr)
//		{
//			AddCollider(gameObject->rigidbody);
//		}
//	}
//}


void Collider::SetRestitution(float _restitution)
{
	fixtureDef.restitution = _restitution;
	if (fixture)
	{
		fixture->SetRestitution(_restitution);
	}
}
void Collider::SetFriction(float _friction)
{
	fixtureDef.friction = _friction;
	if (fixture)
	{
		fixture->SetFriction(_friction);
	}
}
void Collider::SetDensity(float _density)
{
	fixtureDef.density = _density;
	if (fixture)
	{
		fixture->SetDensity(_density);
	}
}

float Collider::GetRestitution()
{
	return fixture->GetRestitution();
}
float Collider::GetFriction()
{
	return fixture->GetFriction();
}
float Collider::GetDensity()
{
	return fixture->GetDensity();
}