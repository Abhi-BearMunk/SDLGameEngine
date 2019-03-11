#include "MidtermScene.h"
#include "CameraFollow.h"
#include "SpriteRenderer.h"
#include "Renderer.h"
#include "Camera.h"
#include "Game.h"
#include "Rigidbody.h"
#include "BoxCollider.h"
#include "Physics.h"
#include "GameObject.h"
#include "PlayerControls.h"
#include "TextRenderer.h"
#include "Enemy.h"


MidtermScene::MidtermScene()
{
}


MidtermScene::~MidtermScene()
{
}

void MidtermScene::Setup()
{
	Scene::Setup();

	// Room 1

	Instantiate(game->Prefab("Floor"), 300, 200);

	Instantiate(game->Prefab("Gate"), 125, -100);
	Instantiate(game->Prefab("Gate"), 475, -100);

	Instantiate("q1", 300, 100)->AddComponent(new TextRenderer("Assets/Raleway-Bold.ttf", 28, "Question 1 :", 2));
	Instantiate("q1", 300, 150)->AddComponent(new TextRenderer("Assets/Raleway-Bold.ttf", 28, "An algorithm is a step by step process that", 2));
	Instantiate("q1", 300, 190)->AddComponent(new TextRenderer("Assets/Raleway-Bold.ttf", 28, "generates solution to a problem.", 2));

	Instantiate("q1", 125, -100)->AddComponent(new TextRenderer("Assets/Raleway-Bold.ttf", 28, "True", 2));
	Instantiate("q1", 475, -100)->AddComponent(new TextRenderer("Assets/Raleway-Bold.ttf", 28, "False", 2));

	Instantiate(game->Prefab("WallBlock"), 300, -100);

	Instantiate(game->Prefab("Wall"), -50, 200, 90);
	Instantiate(game->Prefab("Wall"), 650, 200, 90);

	// Room 2

	Instantiate(game->Prefab("Floor"), 300, 200 - 600);

	Instantiate(game->Prefab("Gate"), 125, -100 - 600);
	Instantiate(game->Prefab("Gate"), 475, -100 - 600);

	Instantiate("q1", 300, 100 - 600)->AddComponent(new TextRenderer("Assets/Raleway-Bold.ttf", 28, "Question 2 :", 2));
	Instantiate("q1", 300, 150 - 600)->AddComponent(new TextRenderer("Assets/Raleway-Bold.ttf", 28, "It doesn't matter what data structure", 2));
	Instantiate("q1", 300, 190 - 600)->AddComponent(new TextRenderer("Assets/Raleway-Bold.ttf", 28, "you choose for a particular algorithm.", 2));

	Instantiate("q1", 125, -100 - 600)->AddComponent(new TextRenderer("Assets/Raleway-Bold.ttf", 28, "True", 2));
	Instantiate("q1", 475, -100 - 600)->AddComponent(new TextRenderer("Assets/Raleway-Bold.ttf", 28, "False", 2));

	Instantiate(game->Prefab("WallBlock"), 300, -100 - 600);

	Instantiate(game->Prefab("Wall"), -50, 200 - 600, 90);
	Instantiate(game->Prefab("Wall"), 650, 200 - 600, 90);

	// Room 3

	Instantiate(game->Prefab("Floor"), 300, 200 - 1200);

	Instantiate(game->Prefab("Gate"), 125, -100 - 1200);
	Instantiate(game->Prefab("Gate"), 475, -100 - 1200);

	Instantiate("q1", 300, 100 - 1200)->AddComponent(new TextRenderer("Assets/Raleway-Bold.ttf", 28, "Question 3 :", 2));
	Instantiate("q1", 300, 150 - 1200)->AddComponent(new TextRenderer("Assets/Raleway-Bold.ttf", 28, "A rule of thumb or an approximate", 2));
	Instantiate("q1", 300, 190 - 1200)->AddComponent(new TextRenderer("Assets/Raleway-Bold.ttf", 28, "solution that might work in many", 2));
	Instantiate("q1", 300, 230 - 1200)->AddComponent(new TextRenderer("Assets/Raleway-Bold.ttf", 28, "situations but not all is a:", 2));


	Instantiate("q1", 125, -100 - 1200)->AddComponent(new TextRenderer("Assets/Raleway-Bold.ttf", 28, "Heuristic", 2));
	Instantiate("q1", 475, -100 - 1200)->AddComponent(new TextRenderer("Assets/Raleway-Bold.ttf", 28, "Hedonistic", 2));

	Instantiate(game->Prefab("WallBlock"), 300, -100 - 1200);

	Instantiate(game->Prefab("Wall"), -50, 200 - 1200, 90);
	Instantiate(game->Prefab("Wall"), 650, 200 - 1200, 90);

	// Room 4

	Instantiate(game->Prefab("Floor"), 300, 200 - 1800);

	Instantiate(game->Prefab("Gate"), 125, -100 - 1800);
	Instantiate(game->Prefab("Gate"), 475, -100 - 1800);

	Instantiate("q1", 300, 100 - 1800)->AddComponent(new TextRenderer("Assets/Raleway-Bold.ttf", 28, "Question 4 :", 2));
	Instantiate("q1", 300, 150 - 1800)->AddComponent(new TextRenderer("Assets/Raleway-Bold.ttf", 28, "Kinematic movement accounts for how", 2));
	Instantiate("q1", 300, 190 - 1800)->AddComponent(new TextRenderer("Assets/Raleway-Bold.ttf", 28, "characters accelarate and slow down", 2));

	Instantiate("q1", 125, -100 - 1800)->AddComponent(new TextRenderer("Assets/Raleway-Bold.ttf", 28, "True", 2));
	Instantiate("q1", 475, -100 - 1800)->AddComponent(new TextRenderer("Assets/Raleway-Bold.ttf", 28, "False", 2));

	Instantiate(game->Prefab("WallBlock"), 300, -100 - 1800);

	Instantiate(game->Prefab("Wall"), -50, 200 - 1800, 90);
	Instantiate(game->Prefab("Wall"), 650, 200 - 1800, 90);

	// Room 5

	Instantiate(game->Prefab("Floor"), 300, 200 - 2400);

	Instantiate(game->Prefab("Gate"), 125, -100 - 2400);
	Instantiate(game->Prefab("Gate"), 475, -100 - 2400);

	Instantiate("q1", 300, 100 - 2400)->AddComponent(new TextRenderer("Assets/Raleway-Bold.ttf", 28, "Question 5 :", 2));
	Instantiate("q1", 300, 150 - 2400)->AddComponent(new TextRenderer("Assets/Raleway-Bold.ttf", 28, "A dynamic algorithm outputs forces", 2));
	Instantiate("q1", 300, 190 - 2400)->AddComponent(new TextRenderer("Assets/Raleway-Bold.ttf", 28, "or accelarations with the aim of", 2));
	Instantiate("q1", 300, 230 - 2400)->AddComponent(new TextRenderer("Assets/Raleway-Bold.ttf", 28, "changing the velocity of the character", 2));

	Instantiate("q1", 125, -100 - 2400)->AddComponent(new TextRenderer("Assets/Raleway-Bold.ttf", 28, "True", 2));
	Instantiate("q1", 475, -100 - 2400)->AddComponent(new TextRenderer("Assets/Raleway-Bold.ttf", 28, "False", 2));

	Instantiate(game->Prefab("WallBlock"), 300, -100 - 2400);

	Instantiate(game->Prefab("Wall"), -50, 200 - 2400, 90);
	Instantiate(game->Prefab("Wall"), 650, 200 - 2400, 90);

	// Room 6

	Instantiate(game->Prefab("Floor"), 300, 200 - 3000);

	Instantiate(game->Prefab("Gate"), 125, -100 - 3000);
	Instantiate(game->Prefab("Gate"), 475, -100 - 3000);

	Instantiate("q1", 300, 100 - 3000)->AddComponent(new TextRenderer("Assets/Raleway-Bold.ttf", 28, "Question 1 :", 2));
	Instantiate("q1", 300, 150 - 3000)->AddComponent(new TextRenderer("Assets/Raleway-Bold.ttf", 28, "In a typical flocking algorithm,", 2));
	Instantiate("q1", 300, 190 - 3000)->AddComponent(new TextRenderer("Assets/Raleway-Bold.ttf", 28, "a cohesion behaviour works to keep the", 2));
	Instantiate("q1", 300, 230 - 3000)->AddComponent(new TextRenderer("Assets/Raleway-Bold.ttf", 28, "boids close to the center of mass.", 2));

	Instantiate("q1", 125, -100 - 3000)->AddComponent(new TextRenderer("Assets/Raleway-Bold.ttf", 28, "True", 2));
	Instantiate("q1", 475, -100 - 3000)->AddComponent(new TextRenderer("Assets/Raleway-Bold.ttf", 28, "False", 2));

	Instantiate(game->Prefab("WallBlock"), 300, -100 - 3000);

	Instantiate(game->Prefab("Wall"), -50, 200 - 3000, 90);
	Instantiate(game->Prefab("Wall"), 650, 200 - 3000, 90);

	// Last Room

	Instantiate(game->Prefab("Floor"), 300, 200 - 3600);

	Instantiate(game->Prefab("Wall"), -50, 200 - 3600, 90);
	Instantiate(game->Prefab("Wall"), 650, 200 - 3600, 90);

	// Player
	GameObject* go = Instantiate("Player", 300, 400, 0);
	go->AddComponent(new SpriteRenderer("Assets/Target.png"));
	go->transform->SetRelativeScale(Vector2(0.1f, 0.1f));
	Rigidbody* rb = new Rigidbody();
	rb->SetBodyType(Rigidbody::dynamicBody);
	go->AddComponent(rb);
	BoxCollider* col = new BoxCollider();
	//col->SetCategory(game->physics->Layer_1);
	go->AddComponent(col);

	col->SetDimension(Vector2(620, 691));

	GameObject* graphic = Instantiate("TankGraphic", 0, 0, 90);
	Sprite* tankSprite = new Sprite("Assets/Tank.png");
	SpriteRenderer* tankRenderer = new SpriteRenderer();
	tankRenderer->SetSprite(tankSprite);

	graphic->AddComponent(tankRenderer);
	graphic->transform->SetParentRelative(go->transform);

	go->AddComponent(new PlayerControls());
	go->AddComponent(new CameraFollow());


	// Enemies
	GameObject* e1 = Instantiate(game->Prefab("Enemy"), 300, 200 - 3600, 90);
	e1->GetComponent<Enemy>()->player = go->transform;
	e1->GetComponent<Enemy>()->timer = 1;

	GameObject* e2 = Instantiate(game->Prefab("Enemy"), 150, 200 - 3600, 90);
	e2->GetComponent<Enemy>()->player = go->transform;
	e2->GetComponent<Enemy>()->timer = 2;

	GameObject* e3 = Instantiate(game->Prefab("Enemy"), 450, 200 - 3600, 90);
	e3->GetComponent<Enemy>()->player = go->transform;
	e3->GetComponent<Enemy>()->timer = 3;
}
