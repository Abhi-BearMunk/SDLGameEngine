#pragma once
#include "Collider.h"
#include "Vector2.h"

class BoxCollider :
	public Collider
{
public:
	BoxCollider();
	~BoxCollider();

	void SetDimension(const Vector2& _dimension);
	const Vector2& GetDimension();

	void SetOffset(const Vector2& _offset);
	const Vector2& GetOffset();

	void FixedUpdate();

private:
	b2PolygonShape box;
	Vector2 dimension = Vector2(100, 100);
	Vector2 offset;

	Vector2 relativePosition = Vector2(0,0);
	Vector2 gameObjectScale = Vector2(1, 1);
	float relativeAngle = 0;

	void SetFixtureDef();
	void SetRelativeValues();
};

