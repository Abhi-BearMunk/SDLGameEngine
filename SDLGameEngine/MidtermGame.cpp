#include "MidtermGame.h"
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
