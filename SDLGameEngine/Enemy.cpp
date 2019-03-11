#include "Enemy.h"
#include "Input.h"
#include "Rigidbody.h"
#include "GameObject.h"
#include "Physics.h"
#include "RaycastHit.h"
#include "Game.h"
#include "Time.h"

Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}


void Enemy::Update()
{

	Behaviour::Update();

	if (abs(player->GetAbsolutePosition().y - gameObject->transform->GetAbsolutePosition().y) < 300)
	{
		timer += Time::DeltaTime();
		if (timer > time)
		{
			// Shoot
			gameObject->transform->SetAbsoluteAngle(atan2(player->GetAbsolutePosition().y - gameObject->transform->GetAbsolutePosition().y, player->GetAbsolutePosition().x - gameObject->transform->GetAbsolutePosition().x) * 180.0f / M_PI);
			Instantiate(game->Prefab("Bullet"), gameObject->transform->GetAbsolutePosition() + 50 * gameObject->transform->Right(), gameObject->transform->GetAbsoluteAngle() - 90);
			timer = 0;
		}
	}
	

}