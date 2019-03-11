#include "Rigidbody.h"
#include "GameObject.h"
#include "Transform.h"
#include "Game.h"
#include "Collider.h"
#include <algorithm>
#include "Time.h"
#include "EventListener.h"

Rigidbody::Rigidbody()
{

}

Rigidbody::~Rigidbody()
{

}

void Rigidbody::Cleanup()
{
	if (gameObject != nullptr)
	{
		// remove transform listener
		gameObject->transform->OnTransformUpdate.RemoveListener(onTransformUpdate);
		// remove from gameobject
		gameObject->RemoveRigidbody();
	}
	physics->rigidbodies.remove(this);
}


void Rigidbody::Awake()
{
	Component::Awake();

	// Add to physics list
	physics = game->physics;
	physics->rigidbodies.push_back(this);

	// update bodydeft transform
	if (gameObject != NULL)
	{
		b2Vec2 pos = physics->GetPhysicsCoordinates(gameObject->transform->GetAbsolutePosition());
		bodyDef.position.Set(pos.x, pos.y);
		bodyDef.angle = gameObject->transform->GetAbsoluteAngle() * M_PI / 180.0f;
	}

	// Create body
	body = physics->GetPhysicsWorld().CreateBody(&bodyDef);
	body->SetUserData(this);

	// Set non-bodydef properties
	SetMass(mass);

	// Callback on gameobject
	if (gameObject != nullptr)
	{
		gameObject->AddRigidbody(this);
	}

	// add transform listener
	onTransformUpdate = std::make_shared<EventListener<TransformData>>(std::bind(&Rigidbody::UpdatePhysicsTransform, this, std::placeholders::_1));
	gameObject->transform->OnTransformUpdate.AddListener(onTransformUpdate);
}

b2BodyType Rigidbody::ConvertToB2Type(const bodyType& _type)
{
	switch (_type)
	{
	case staticBody:
		return b2_staticBody;
		break;
	case kinematicBody:
		return b2_kinematicBody;
		break;
	case dynamicBody:
		return b2_dynamicBody;
		break;
	default:
		break;
	}
}

void Rigidbody::SetBodyType(const bodyType& _type)
{
	type = _type;
	b2BodyType b2Type = ConvertToB2Type(type);
	bodyDef.type = b2Type;
	if (body != NULL)
	{
		body->SetType(b2Type);
	}
}

const Rigidbody::bodyType& Rigidbody::GetBodyType() const
{
	return type;
}

void Rigidbody::FixedUpdate()
{
	Component::FixedUpdate();
	accelaration = body->GetLinearVelocity() - lastVelocity;
	accelaration *= 1 / Time::FixedDeltaTime();
	lastVelocity = body->GetLinearVelocity();
}

void Rigidbody::Extrapolate(float dt)
{
	b2Vec2 delta = body->GetLinearVelocity();
	delta *= dt;
	b2Vec2 delta2 = accelaration;
	delta2 *= 0.5f * dt * dt;
	b2Vec2 extrapolatedPos = body->GetPosition() + delta + delta2;
	onTransformUpdate->disabled = true;
	gameObject->transform->SetAbsolutePosition(physics->GetWorldCoordinates(extrapolatedPos));
	gameObject->transform->SetAbsoluteAngle((body->GetAngle() + body->GetAngularVelocity() * dt) * 180.0f / M_PI);
	onTransformUpdate->disabled = false;
}

void Rigidbody::AddForce(Vector2 force)
{
	body->ApplyForceToCenter(physics->GetPhysicsCoordinates(force), true);
}

void Rigidbody::AddForce(Vector2 force, Vector2 center)
{
	body->ApplyForce(physics->GetPhysicsCoordinates(force), physics->GetPhysicsCoordinates(center), true);
}

void Rigidbody::SetMass(float _mass)
{
	mass = _mass;
	if (body != nullptr && physics != nullptr)
	{
		b2MassData massData;
		body->GetMassData(&massData);
		massData.mass = _mass;
		body->SetMassData(&massData);
	}	
}

float Rigidbody::GetMass()
{
	return body->GetMass();
}

void Rigidbody::SetVelocity(const Vector2& velocity)
{
	if (body)
	{
		body->SetLinearVelocity(physics->GetPhysicsCoordinates(velocity));
	}
}

const Vector2 Rigidbody::GetVelocity()
{
	if (body)
	{
		return physics->GetWorldCoordinates(body->GetLinearVelocity());
	}
	return Vector2(0, 0);
}

void Rigidbody::SetBullet(bool toggle)
{
	isBullet = true;
	bodyDef.bullet = toggle;
	if (body)
	{
		body->SetBullet(toggle);
	}
}

bool Rigidbody::ContainsCollider(Collider* col)
{
	return std::find(myColliders.begin(), myColliders.end(), col) != myColliders.end();
}

void Rigidbody::AddCollider(Collider* col)
{
 	col->fixture = body->CreateFixture(&col->fixtureDef);
	col->fixture->SetUserData(col);
	myColliders.push_back(col);
}

void Rigidbody::RemoveCollider(Collider* col)
{
	if (col->fixture)
	{
		body->DestroyFixture(col->fixture);
	}
	col->fixture = nullptr;
	myColliders.remove(col);
}

void Rigidbody::UpdatePhysicsTransform(const TransformData &data)
{
	body->SetTransform(physics->GetPhysicsCoordinates(data.position), data.angle * M_PI / 180.0f);
}

