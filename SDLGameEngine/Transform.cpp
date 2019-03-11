#include "Transform.h"
#include "Game.h"



Transform::Transform()
{
	position.x = 0;
	position.y = 0;
	data.angle = angle;
	data.position = position;
	data.scale = scale;
}


Transform::Transform(GameObject* _gameObject, float x, float y, float _angle, float xScale, float yScale) : Component(_gameObject)
{
	SetAbsolutePosition(Vector2(x, y));
	SetAbsoluteAngle(_angle);
	SetAbsoluteScale(Vector2(xScale, yScale));
	data.angle = angle;
	data.position = position;
	data.scale = scale;
}

Transform::~Transform()
{
}

const Vector2& Transform::GetAbsolutePosition() const
{
	if (parent != NULL)
	{
		SDL_SetRenderDrawColor(Game::gRenderer, 0x00, 0xFF, 0x00, 0xFF);
		SDL_RenderDrawLine(Game::gRenderer, parent->GetAbsolutePosition().x - Camera::x, parent->GetAbsolutePosition().y - Camera::y, position.x - Camera::x, position.y - Camera::y);
	}
	return position;
}

const float& Transform::GetAbsoluteAngle() const
{
	return angle;
}

const Vector2& Transform::GetAbsoluteScale() const
{
	return scale;
}

const Vector2& Transform::GetRelativePosition() const
{
	return relativePosition;
}

const float& Transform::GetRelativeAngle() const
{
	return relativeAngle;
}

const Vector2& Transform::GetRelativeScale() const
{
	return relativeScale;
}

void Transform::SetAbsolutePosition(const Vector2& _position) 
{
	position = _position;
	if (parent == NULL)
	{
		relativePosition = _position;
	}
	else
	{
		relativePosition = (position - parent->GetAbsolutePosition()).Rotation(-parent->GetAbsoluteAngle() * M_PI / 180.0f);
	}
	for (Transform* t : children)
	{
		t->SetRelativePosition(t->GetRelativePosition());
	}
	data.position = position;
	OnTransformUpdate(data);
}

void Transform::SetRelativePosition(const Vector2& _position)
{
	relativePosition = _position;
	if (parent == NULL)
	{
		position = _position;
	}
	else
	{
		position = parent->GetAbsolutePosition() + relativePosition.Rotation(parent->GetAbsoluteAngle() * M_PI / 180.0f);
	}
	for (Transform* t : children)
	{
		t->SetRelativePosition(t->GetRelativePosition());
	}
	data.position = position;
	OnTransformUpdate(data);
}

void Transform::SetAbsoluteAngle(const float& _angle)
{
	angle = _angle;
	if (parent == NULL)
	{
		relativeAngle = angle;
	}
	else
	{
		relativeAngle = angle - parent->GetAbsoluteAngle();
	}
	for (Transform* t : children)
	{
		t->SetRelativeAngle(t->GetRelativeAngle());
		t->SetRelativePosition(t->GetRelativePosition());
	}
	data.angle = angle;
	OnTransformUpdate(data);
}

void Transform::SetRelativeAngle(const float& _angle)
{
	relativeAngle = _angle;
	if (parent == NULL)
	{
		angle = angle;
	}
	else
	{
		angle = relativeAngle + parent->GetAbsoluteAngle();
	}
	for (Transform* t : children)
	{
		t->SetRelativeAngle(t->GetRelativeAngle());
		t->SetRelativePosition(t->GetRelativePosition());
	}
	data.angle = angle;
	OnTransformUpdate(data);
}

void Transform::SetAbsoluteScale(const Vector2& _scale)
{
	scale = _scale;
	if (parent == NULL)
	{
		relativeScale = scale;
	}
	else
	{
		const Vector2& parentScale = parent->GetAbsoluteScale();
		if (parentScale.x == 0)
		{
			scale.x = 0;
			relativeScale.x = 0;
		}
		else
		{
			relativeScale.x = scale.x / parentScale.x;
		}

		if (parentScale.y == 0)
		{
			scale.y = 0;
			relativeScale.y = 0;
		}
		else
		{
			relativeScale.y = scale.y / parentScale.y;
		}
	}
	for (Transform* t : children)
	{
		t->SetRelativeScale(t->GetRelativeScale());
	}
	data.scale = scale;
	OnTransformUpdate(data);
}

void Transform::SetRelativeScale(const Vector2& _scale)
{
	relativeScale = _scale;
	if (parent == NULL)
	{
		scale = relativeScale;
	}
	else
	{
		const Vector2& parentScale = parent->GetAbsoluteScale();
		scale.x = relativeScale.x * parentScale.x;
		scale.y = relativeScale.y * parentScale.y;
	}
	for (Transform* t : children)
	{
		t->SetRelativeScale(t->GetRelativeScale());
	}
	data.scale = scale;
	OnTransformUpdate(data);
}


void Transform::SetAbsolutePositionDelta(const Vector2& delta)
{
	SetAbsolutePosition(position + delta);
}

void Transform::SetRelativePositionDelta(const Vector2& delta)
{
	SetRelativePosition(relativePosition + delta);
}

void Transform::SetAbsoluteAngleDelta(const float& delta)
{
	SetAbsoluteAngle(angle + delta);
}

void Transform::SetRelativeAngleDelta(const float& delta)
{
	SetRelativeAngle(relativeAngle + delta);
}

void Transform::SetAbsoluteScaleDelta(const Vector2& delta)
{
	SetAbsoluteScale(scale + delta);
}

void Transform::SetRelativeScaleDelta(const Vector2& delta)
{
	SetRelativeScale(relativeScale + delta);
}

void Transform::SetParent(Transform* _parent)
{
	if (parent != NULL)
	{
		parent->children.remove(this);
	}
	parent = _parent;
	if (parent != NULL)
	{
		parent->children.push_back(this);
	}
	SetAbsolutePosition(position);
	SetAbsoluteAngle(angle);
	SetAbsoluteScale(scale);
}

void Transform::SetParentRelative(Transform* _parent)
{
	if (parent != NULL)
	{
		parent->children.remove(this);
	}
	parent = _parent;
	if (parent != NULL)
	{
		parent->children.push_back(this);
	}
	SetRelativePosition(relativePosition);
	SetRelativeAngle(relativeAngle);
	SetRelativeScale(relativeScale);
}

const Vector2 Transform::Right() const
{
	const float& _absoluteAngle = GetAbsoluteAngle() * M_PI / 180.0f;
	return Vector2(cos(_absoluteAngle), sin(_absoluteAngle));
}

const Vector2 Transform::Up() const
{
	const float& _absoluteAngle = GetAbsoluteAngle() * M_PI / 180.0f;
	return Vector2(-sin(_absoluteAngle), cos(_absoluteAngle));
}

void Transform::Cleanup()
{

}