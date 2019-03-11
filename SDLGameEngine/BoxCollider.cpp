#include "BoxCollider.h"
#include "Game.h"
#include "Rigidbody.h"
#include "GameObject.h"
#include "Transform.h"

BoxCollider::BoxCollider()
{
	fixtureDef.shape = &box;
}


BoxCollider::~BoxCollider()
{
}

void BoxCollider::SetDimension(const Vector2& _dimension)
{
	dimension = _dimension;
	ResetFixture();
}

const Vector2& BoxCollider::GetDimension()
{
	return dimension;
}

void BoxCollider::SetOffset(const Vector2& _offset)
{
	offset = _offset;
	ResetFixture();
}

const Vector2& BoxCollider::GetOffset()
{
	return offset;
}

void BoxCollider::SetFixtureDef()
{
	b2Vec2 physicsDimension = game->physics->GetPhysicsCoordinates(Vector2(dimension.x * gameObjectScale.x, dimension.y * gameObjectScale.y));
	Vector2 relOffsetInWorldSpace = offset.x * gameObject->transform->Right() + offset.y * gameObject->transform->Up();
	Vector2 relOffset = Vector2(relOffsetInWorldSpace.Dot(rigidbody->gameObject->transform->Right()), relOffsetInWorldSpace.Dot(rigidbody->gameObject->transform->Up()));
	b2Vec2 physicsOffset = game->physics->GetPhysicsCoordinates(relativePosition + relOffset);

	box.SetAsBox(physicsDimension.x / 2, physicsDimension.y / 2, physicsOffset, relativeAngle);
	fixtureDef.shape = &box;
}

void BoxCollider::SetRelativeValues()
{
	if (rigidbody != nullptr)
	{
		Vector2 toVec = gameObject->transform->GetAbsolutePosition() - rigidbody->gameObject->transform->GetAbsolutePosition();
		float x = toVec.Dot(rigidbody->gameObject->transform->Right());
		float y = toVec.Dot(rigidbody->gameObject->transform->Up());
		relativePosition = Vector2(x, y);
		relativeAngle = atan2(gameObject->transform->Right().Dot(rigidbody->gameObject->transform->Up()), gameObject->transform->Right().Dot(rigidbody->gameObject->transform->Right()));
	}
	gameObjectScale = gameObject->transform->GetAbsoluteScale();
}

void BoxCollider::FixedUpdate()
{
	Collider::FixedUpdate();
	SDL_SetRenderDrawColor(Game::gRenderer, 0x00, 0xFF, 0x00, 0xFF);
	Vector2 cam = Vector2(Camera::x, Camera::y);
	Vector2 up = gameObject->transform->Up() * (dimension.y * gameObjectScale.y / 2);
	Vector2 right = gameObject->transform->Right() * (dimension.x * gameObjectScale.x / 2);
	Vector2 relOffset = gameObject->transform->Up() * offset.y + gameObject->transform->Right() * offset.x;
	Vector2 a = gameObject->transform->GetAbsolutePosition() + up - right - cam + relOffset;
	Vector2 b = gameObject->transform->GetAbsolutePosition() + up + right - cam + relOffset;
	Vector2 c = gameObject->transform->GetAbsolutePosition() - up + right - cam + relOffset;
	Vector2 d = gameObject->transform->GetAbsolutePosition() - up - right - cam + relOffset;
	SDL_RenderDrawLine(Game::gRenderer, a.x, a.y, b.x, b.y);
	SDL_RenderDrawLine(Game::gRenderer, b.x, b.y, c.x, c.y);
	SDL_RenderDrawLine(Game::gRenderer, c.x, c.y, d.x, d.y);
	SDL_RenderDrawLine(Game::gRenderer, d.x, d.y, a.x, a.y);
}

