#include "MidtermGame.h"
#include <time.h>
#include <stdlib.h>
#include "Shooter.h"
#include "Bullet.h"
#include "GameObject.h"
#include "Time.h"
#include "Shoot.h"
#include "SpriteRenderer.h"
#include "Rigidbody.h"
#include "BoxCollider.h"
#include "MidtermScene.h"



MidtermGame::MidtermGame()
{
}


MidtermGame::~MidtermGame()
{
}

void MidtermGame::Awake()
{
	Camera::x = 0;
	Camera::y = 0;
	Camera::width = 1280;
	Camera::height = 720;
	Time::timeScale = 1;
}

void MidtermGame::BulletPrefab(GameObject* go)
{
	go->name = "bullet";
	// Graphics
	go->AddComponent(new SpriteRenderer("Assets/beams.png", new Rect(15, 300, 50, 90)));

	// Bullet script
	go->AddComponent(new Bullet());

	// Rigidbody
	Rigidbody* rb = new Rigidbody();
	rb->SetBodyType(Rigidbody::dynamicBody);
	go->AddComponent(rb);
	rb->SetBullet(true);

	// Collider
	BoxCollider* col = new BoxCollider();
	go->AddComponent(col);
	col->SetDimension(Vector2(10, 10));
	col->SetTrigger(true);
}

void MidtermGame::WallPrefab(GameObject* go)
{
	// Graphics
	SpriteRenderer* wallRenderer = new SpriteRenderer(new Sprite("Assets/stones_wall.png"));
	go->AddComponent(wallRenderer);
	go->transform->SetRelativeScale(Vector2(0.3f, 0.3f));

	// Rigidbody
	Rigidbody* rb = new Rigidbody();
	rb->SetBodyType(Rigidbody::staticBody);
	go->AddComponent(rb);

	// Collider
	BoxCollider* col = new BoxCollider();
	go->AddComponent(col);
	col->SetCategory(physics->Layer_2);
	col->SetDimension(Vector2(300, 60));
}

void MidtermGame::EnemyPrefab(GameObject* go)
{
	go->name = "enemy";
	GameObject* graphic = Instantiate("enemy_graphic", 0, 0, 90);
	graphic->AddComponent(new SpriteRenderer("Assets/tanks_3.png", new Rect(350, 250, 225, 150)));
	graphic->transform->SetParentRelative(go->transform);
	graphic->transform->SetAbsoluteScale(Vector2(0.3f, 0.3f));
}

void MidtermGame::GatePrefab(GameObject* go)
{

}

void MidtermGame::Setup()
{
	AddPrefab("Bullet", std::bind(&MidtermGame::BulletPrefab, this, std::placeholders::_1));
	AddPrefab("Enemy", std::bind(&MidtermGame::EnemyPrefab, this, std::placeholders::_1));
	AddPrefab("Wall", std::bind(&MidtermGame::WallPrefab, this, std::placeholders::_1));


	SetScene(new MidtermScene());
}