#include "CameraFollow.h"
#include "Camera.h"
#include "GameObject.h"
#include "Transform.h"


CameraFollow::CameraFollow()
{
}


CameraFollow::~CameraFollow()
{
}

void CameraFollow::FixedUpdate()
{
	Camera::x = (gameObject->transform->GetAbsolutePosition().x) - (Camera::width * 0.5f);
	Camera::y = (gameObject->transform->GetAbsolutePosition().y) - (Camera::height * 0.5f);

}