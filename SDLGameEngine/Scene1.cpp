#include "Scene1.h"
#include "PlayerControls.h"
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
#include "Renderer.h"
#include "Camera.h"
#include "Game.h"
#include "Rigidbody.h"
#include "BoxCollider.h"
#include "Physics.h"

Scene1::Scene1()
{
}


Scene1::~Scene1()
{
}

void Scene1::Setup()
{
	Scene::Setup();


	GameObject* bg = Instantiate("bg", 300, 200, 0);
	Sprite* bgSprite = new Sprite("Assets/background.png");
	SpriteRenderer* bgRenderer = new SpriteRenderer(bgSprite);
	bg->AddComponent(bgRenderer);

	GameObject* bg1 = Instantiate("bg", 300 - 700, 200, 0);
	SpriteRenderer* bgRenderer1 = new SpriteRenderer(bgSprite);
	bg1->AddComponent(bgRenderer1);

	GameObject* bg2 = Instantiate("bg", 300 + 700, 200, 0);
	SpriteRenderer* bgRenderer2 = new SpriteRenderer(bgSprite);
	bg2->AddComponent(bgRenderer2);

	GameObject* bg3 = Instantiate("bg", 300, 200 + 600, 0);
	SpriteRenderer* bgRenderer3 = new SpriteRenderer(bgSprite);
	bg3->AddComponent(bgRenderer3);

	GameObject* bg4 = Instantiate("bg", 300, 200 - 600, 0);
	SpriteRenderer* bgRenderer4 = new SpriteRenderer(bgSprite);
	bg4->AddComponent(bgRenderer4);

	//GameObject* wall1 = Instantiate("wall1", 200, 200, 90);
	//SpriteRenderer* wall1Renderer = new SpriteRenderer(new Sprite("Assets/stones_wall.png"));
	//wall1->AddComponent(wall1Renderer);
	//wall1->transform->SetRelativeScale(Vector2(0.3f, 0.3f));
	//Rigidbody* rb1 = new Rigidbody();
	//rb1->SetBodyType(Rigidbody::staticBody);
	//wall1->AddComponent(rb1);
	//BoxCollider* col1 = new BoxCollider();
	//wall1->AddComponent(col1);

	//col1->SetDimension(Vector2(300, 60));

	GameObject* wall1 = Instantiate(game->Prefab("Wall"), 200, 200, 90);
	GameObject* wall2 = Instantiate(game->Prefab("Wall"), 500, 400, 0);
	GameObject* wall3 = Instantiate(game->Prefab("Wall"), 0, 0, 0);
	GameObject* wall4 = Instantiate(game->Prefab("Wall"), 700, 200, 45);
	GameObject* wall5 = Instantiate(game->Prefab("Wall"), 400, 100, 10);
	GameObject* wall6 = Instantiate(game->Prefab("Wall"), -50, 550, 45);




	GameObject* go = Instantiate("Tank", 300, 200, 0);
	go->AddComponent(new SpriteRenderer("Assets/Target.png"));
	go->transform->SetRelativeScale(Vector2(0.1f, 0.1f));
	Rigidbody* rb = new Rigidbody();
	rb->SetBodyType(Rigidbody::dynamicBody);
	go->AddComponent(rb);
	BoxCollider* col = new BoxCollider();
	col->SetCategory(game->physics->Layer_1);
	go->AddComponent(col);

	col->SetDimension(Vector2(80, 80));

	GameObject* graphic = Instantiate("TankGraphic", 0, 0, 90);
	Sprite* tankSprite = new Sprite("Assets/Tank.png");
	SpriteRenderer* tankRenderer = new SpriteRenderer();
	tankRenderer->SetSprite(tankSprite);
	//tankRenderer->flipY = true;

	graphic->AddComponent(tankRenderer);
	/*graphic->transform->scale.x = 0.1f;
	graphic->transform->scale.y = 0.1f;*/



	graphic->transform->SetParentRelative(go->transform);


	go->AddComponent(new PlayerControls());
	go->AddComponent(new CameraFollow());

	graphic->AddComponent(new Shoot());
	
	for (int i = 0; i < 10; i++)
	{
		GameObject* enemy = Instantiate(game->Prefab("Enemy"), Camera::x + rand() % Camera::width, Camera::y + rand() % Camera::height, 0);
		//enemy->GetComponent<Rigidbody>()->AddForce(50 * Vector2(rand() % 100 - 50 , rand() % 100 - 50));
	}



}
