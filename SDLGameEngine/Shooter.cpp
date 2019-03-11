#include <time.h>
#include <stdlib.h>
#include "Shooter.h"
#include "Bullet.h"
#include "GameObject.h"
#include "SteeringAgent.h"
#include "Seek.h"
#include "Flee.h"
#include "Arrive.h"
#include "Align.h"
#include "Pursue.h"
#include "UpdateVectorTarget.h"
#include "MoveInCircle.h"
#include "Time.h"
#include "PathFollowing.h"
#include "Shoot.h"
#include "CameraFollow.h"
#include "SpriteRenderer.h"
#include "Scene1.h"
#include "PlayerControls.h"
#include "Rigidbody.h"
#include "BoxCollider.h"
#include "Enemy.h"
#include "ObstacleAvoidance.h"

Shooter::Shooter()
{
}


Shooter::~Shooter()
{
}

void Shooter::Awake()
{
	Camera::x = 0;
	Camera::y = 0;
	Camera::width = 1280;
	Camera::height = 720;
	Time::timeScale = 1;
}

void Shooter::BulletPrefab(GameObject* go)
{
	go->name = "bullet";
	go->AddComponent(new SpriteRenderer("Assets/beams.png", new Rect(15, 300, 50, 90)));
	go->AddComponent(new Bullet());
	//go->transform->SetRelativeScale(Vector2(0.1f, 0.1f));
	Rigidbody* rb = new Rigidbody();
	rb->SetBodyType(Rigidbody::dynamicBody);
	go->AddComponent(rb);
	rb->SetBullet(true);

	BoxCollider* col = new BoxCollider();
	go->AddComponent(col);

	col->SetDimension(Vector2(10, 10));
	col->SetTrigger(true);
}

void Shooter::WallPrefab(GameObject* go)
{
	SpriteRenderer* wallRenderer = new SpriteRenderer(new Sprite("Assets/stones_wall.png"));
	go->AddComponent(wallRenderer);
	go->transform->SetRelativeScale(Vector2(0.3f, 0.3f));
	Rigidbody* rb = new Rigidbody();
	rb->SetBodyType(Rigidbody::staticBody);
	go->AddComponent(rb);
	BoxCollider* col = new BoxCollider();
	go->AddComponent(col);
	col->SetCategory(physics->Layer_2);
	col->SetDimension(Vector2(900, 180));
}

void Shooter::EnemyPrefab(GameObject* go)
{
	go->name = "enemy";
	GameObject* graphic = Instantiate("enemy_graphic", 0, 0, 90);
	graphic->AddComponent(new SpriteRenderer("Assets/tanks_3.png", new Rect(350, 250, 225, 150)));
	graphic->transform->SetParentRelative(go->transform);
	graphic->transform->SetAbsoluteScale(Vector2(0.3f, 0.3f));

	GameObject* tgt = Instantiate("Target", Camera::x + rand() % Camera::width, Camera::y + rand() % Camera::height);
	//go->transform->SetRelativeScale(Vector2(0.1f, 0.1f));

	Arrive* arrive = new Arrive(go);
	arrive->target = tgt->transform;;
	arrive->maxAccelaraction = 1;
	arrive->slowRadius = 30;
	arrive->targetRadius = 10;
	arrive->steering.weight = 0.5f;
	go->AddComponent(arrive);

	ObstacleAvoidance* obstacleAvoidance = new ObstacleAvoidance();
	obstacleAvoidance->avoidLayer = physics->Layer_2;
	obstacleAvoidance->steering.weight = 1;
	obstacleAvoidance->maxAccelaraction = 1;
	go->AddComponent(obstacleAvoidance);

	SteeringAgent* agent = new SteeringAgent(go);
	agent->steerings.push_back(arrive);
	agent->steerings.push_back(obstacleAvoidance);
	agent->maxSpeed = 200;
	//agent->velocity.y = -100;
	go->AddComponent(agent);
	arrive->agent = agent;
	obstacleAvoidance->agent = agent;

	UpdateVectorTarget* updateTarget = new UpdateVectorTarget(go);
	updateTarget->target = &tgt->transform->GetAbsolutePosition();
	updateTarget->maxTime = 6;
	go->AddComponent(updateTarget);

	updateTarget->targetObject = tgt;

	//go->transform->SetRelativeScale(Vector2(0.2f, 0.2f));
	Rigidbody* rb = new Rigidbody();
	rb->SetBodyType(Rigidbody::dynamicBody);
	go->AddComponent(rb);

	BoxCollider* col = new BoxCollider();
	go->AddComponent(col);

	col->SetDimension(Vector2(50, 50));
	col->SetCategory(physics->Layer_3);
	col->SetCollisionMask(~physics->Layer_3);

	go->AddComponent(new Enemy());
}

void Shooter::Setup()
{
	AddPrefab("Bullet", std::bind(&Shooter::BulletPrefab, this, std::placeholders::_1));
	AddPrefab("Enemy", std::bind(&Shooter::EnemyPrefab, this, std::placeholders::_1));
	AddPrefab("Wall", std::bind(&Shooter::WallPrefab, this, std::placeholders::_1));


	SetScene(new Scene1());
}



