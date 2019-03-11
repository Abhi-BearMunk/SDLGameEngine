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
#include "ChangeColor.h"
#include "Enemy.h"
#include "RenderModule.h"



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
	Camera::width = 640;
	Camera::height = 1136;
	Time::timeScale = 1;
	RenderModule::numberOfLayers = 3;
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
	SpriteRenderer* wallRenderer = new SpriteRenderer(new Sprite("Assets/wall-block.png"));
	go->AddComponent(wallRenderer);
	go->transform->SetRelativeScale(Vector2(0.75f, 0.2f));

	// Rigidbody
	Rigidbody* rb = new Rigidbody();
	rb->SetBodyType(Rigidbody::staticBody);
	go->AddComponent(rb);

	// Collider
	BoxCollider* col = new BoxCollider();
	go->AddComponent(col);
	col->SetCategory(physics->Layer_2);
	col->SetDimension(Vector2(800, 624));
}

void MidtermGame::WallBlockPrefab(GameObject* go)
{
	// Graphics
	SpriteRenderer* wallRenderer = new SpriteRenderer(new Sprite("Assets/wall-block.png"), 1);
	go->AddComponent(wallRenderer);
	go->transform->SetRelativeScale(Vector2(0.15f, 0.2f));

	// Rigidbody
	Rigidbody* rb = new Rigidbody();
	rb->SetBodyType(Rigidbody::staticBody);
	go->AddComponent(rb);

	// Collider
	BoxCollider* col = new BoxCollider();
	go->AddComponent(col);
	col->SetCategory(physics->Layer_2);
	col->SetDimension(Vector2(800, 624));
}

void MidtermGame::EnemyPrefab(GameObject* go)
{
	go->name = "enemy";
	GameObject* graphic = Instantiate("enemy_graphic", 0, 0, 180);
	graphic->AddComponent(new SpriteRenderer("Assets/tanks_3.png", new Rect(350, 250, 225, 150)));
	graphic->transform->SetParentRelative(go->transform);
	graphic->transform->SetAbsoluteScale(Vector2(0.3f, 0.3f));

	go->AddComponent(new Enemy());
}

void MidtermGame::GatePrefab(GameObject* go)
{
	SpriteRenderer* wallRenderer = new SpriteRenderer(new Sprite("Assets/white-rectangle.png"), 1);
	go->AddComponent(wallRenderer);
	go->transform->SetRelativeScale(Vector2(0.1f, 0.1f));
	wallRenderer->SetColor(Color(255, 128, 0, 128));

	// Rigidbody
	Rigidbody* rb = new Rigidbody();
	rb->SetBodyType(Rigidbody::staticBody);
	go->AddComponent(rb);

	// Collider
	BoxCollider* col = new BoxCollider();
	go->AddComponent(col);
	//col->SetCategory(physics->Layer_2);
	col->SetDimension(Vector2(2268, 1260));
	col->SetTrigger(true);

	go->AddComponent(new ChangeColor());
}

void MidtermGame::FloorPrefab(GameObject* go)
{
	Sprite* bgSprite = new Sprite("Assets/background.png");
	SpriteRenderer* bgRenderer = new SpriteRenderer(bgSprite);
	go->AddComponent(bgRenderer);
}

void MidtermGame::Setup()
{
	AddPrefab("Bullet", std::bind(&MidtermGame::BulletPrefab, this, std::placeholders::_1));
	AddPrefab("Enemy", std::bind(&MidtermGame::EnemyPrefab, this, std::placeholders::_1));
	AddPrefab("Wall", std::bind(&MidtermGame::WallPrefab, this, std::placeholders::_1));
	AddPrefab("WallBlock", std::bind(&MidtermGame::WallBlockPrefab, this, std::placeholders::_1));
	AddPrefab("Gate", std::bind(&MidtermGame::GatePrefab, this, std::placeholders::_1));
	AddPrefab("Floor", std::bind(&MidtermGame::FloorPrefab, this, std::placeholders::_1));

	SetScene(new MidtermScene());
}