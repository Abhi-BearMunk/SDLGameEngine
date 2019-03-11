#pragma once
#include <Box2D/Box2D.h>
#include "Vector2.h"
#include "LayerdStorage.h"
#include "ContactListener.h"

class Ray;
class RaycastHit;
class Rigidbody;
class Collider;
class Physics
{
public:
	Physics();
	~Physics();

	void Start();
	void FixedUpdate();
	//void Cleanup();

	const b2Vec2 GetPhysicsCoordinates(const Vector2& pos);
	const Vector2 GetWorldCoordinates(const b2Vec2& pos);

	b2World& GetPhysicsWorld();

	uint8_t numberOfLayers = 1;
	std::list<Rigidbody*> rigidbodies;
	void SetGravity(const Vector2& _gravity);

	void Extrapolate(float dt);

	enum Layer
	{
		Layer_1 = 0x0001,
		Layer_2 = 0x0002,
		Layer_3 = 0x0004,
		Layer_4 = 0x0008,
		Layer_5 = 0x0010,
		Layer_6 = 0x0020,
		Layer_7 = 0x0040,
		Layer_8 = 0x0080,
		Layer_9 = 0x0100,
		Layer_10 = 0x0200,
		Layer_11 = 0x0400,
		Layer_12 = 0x0800,
		Layer_13 = 0x1000,
		Layer_14 = 0x2000,
		Layer_15 = 0x4000,
		Layer_16 = 0x8000
	};

	RaycastHit Raycast(Vector2 origin, Vector2 direction, float maxDistance, uint16_t layerMask = 0xFFFF, bool queriesHitTriggers = false);
	RaycastHit Raycast(Ray ray, float maxDistance, uint16_t layerMask = 0xFFFF, bool queriesHitTriggers = false);

private:
    float worldScale = 100;
	Vector2 gravity = Vector2(0, 1000);
	b2World world = b2World(b2Vec2(0, 0));

	uint32_t velocityIterations = 8;
	uint32_t positionIterations = 3;
	ContactListener contactListener;	
};


