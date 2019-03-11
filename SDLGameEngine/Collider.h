#pragma once
#include "Component.h"
#include <Box2D/Box2D.h>
#include "Event.h"

class Ray;
class RaycastHit;
class Rigidbody;
class TransformData;
class Collider :
	public Component
{
public:
	Collider();
	virtual ~Collider();

	b2FixtureDef fixtureDef;
	b2Fixture* fixture;

	virtual void Awake();
	virtual void FixedUpdate();
	virtual void Cleanup();

	void SetTrigger(bool toggle);
	bool GetTrigger();

	void SetCategory(uint16_t flags);
	void SetCollisionMask(uint16_t flags);

	RaycastHit Raycast(Ray ray, float maxDistance);
	RaycastHit Raycast(Vector2 origin, Vector2 direction, float maxDistance);

	void AddCollider(Rigidbody* rigidbody);
	void RemoveCollider(Rigidbody* rigidbody);

	std::shared_ptr<EventListener<Rigidbody*>> OnRigidbodyAdded = nullptr;
	//std::shared_ptr<EventListener<Rigidbody*>> OnRigidbodyRemoved = std::make_shared<EventListener<Rigidbody*>>(std::bind(&RigidbodyRemoved, this));
	std::shared_ptr<EventListener<TransformData>> onTransformUpdate = nullptr;

	void RigidbodyAdded(Rigidbody* rigidbody);
	//void RigidbodyRemoved(Rigidbody* rigidbody);

	// Box2D functions
	void SetRestitution(float _restitution);
	void SetFriction(float _friction);
	void SetDensity(float _density);

	float GetRestitution();
	float GetFriction();
	float GetDensity();

protected:
	bool isTrigger = false;
	Rigidbody* rigidbody = NULL;

	virtual void SetFixtureDef() = 0;
	virtual void SetRelativeValues() = 0;
	void ResetFixture();
	void UpdateTransform(const TransformData &tData);
};

