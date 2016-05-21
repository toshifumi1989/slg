#include "play.h"
#include "../library/field.h"
#include "../library/camera.h"
#include "../library/player.h"
#include "../library/enemy.h"
#include "../play/cursor.h"
#include "../play/playerCamp.h"
#include "../play/enemyCamp.h"


void Play::init()
{
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	field = new Field();
	field->read("field.bmp");
	field->setup();


	//カーソル設定-----------------------------------------------------------------------
	cursor = new Cursor();
	cursor->pos = glm::vec3(field->size / 2.f, 4, field->size / 2.f);
	const float moveSpeed = 0.015f;
	cursor->speed = glm::vec3(moveSpeed, 0, moveSpeed);

	//プレイヤー--------------------------------------------------------------------------------

	//プレイヤー陣地
	{
		//本陣
		PlayerCamp tentativePlayerCamp;
		tentativePlayerCamp.pos = glm::vec3(field->size / 2 - 75, 1, field->size / 2 - 75);
		tentativePlayerCamp.size = glm::vec3(8.f, 3.f, 8.f);
		playerCamp.push_back(tentativePlayerCamp);
	}

	for (int i = 0; i < 2; i++)
	{
		PlayerCamp tentativePlayerCamp;
		tentativePlayerCamp.pos = glm::vec3(field->size / 2 - rand() % 45 - 20, 1, field->size / 2 - rand() % 45 - 20);
		playerCamp.push_back(tentativePlayerCamp);
	}

	//プレイヤーキャラクター設定
	Player tentativePlayer;
	for (int i = 0; i < 3; i++)
	{
		int playerInitPos = 10;
		if (i == 0)
		{
			//中心
			tentativePlayer.pos = glm::vec3(field->size / 2.f - 60, 1, field->size / 2.f - 60);
		}
		else if (i % 2 == 0)
		{
			//右側
			tentativePlayer.pos = glm::vec3(field->size / 2.f - 60 - playerInitPos * i / 2, 1, field->size / 2.f - 60 + playerInitPos * i / 2);
		}
		else
		{
			//左側
			tentativePlayer.pos = glm::vec3(field->size / 2.f - 60 + playerInitPos * (i / 2 + 1), 1, field->size / 2.f - 60 - playerInitPos * (i / 2 + 1));
		}

		player.push_back(tentativePlayer);
	}



	//エネミー-----------------------------------------------------------------------------
	//エネミー陣地
	{
		//本陣
		EnemyCamp tentativeEnemyCamp;
		tentativeEnemyCamp.pos = glm::vec3(field->size / 2 + 75, 1, field->size / 2 + 75);
		enemyCamp.push_back(tentativeEnemyCamp);
	}
	for (int i = 0; i < 2; i++)
	{
		EnemyCamp tentativeEnemyCamp;
		tentativeEnemyCamp.pos = glm::vec3(field->size / 2 + rand() % 45 + 20, 1, field->size / 2 + rand() % 45 + 20);
		enemyCamp.push_back(tentativeEnemyCamp);
	}

	//エネミーキャラクター設定
	Enemy tentativeEnemy;
	for (int i = 0; i < 1; i++)
	{
		tentativeEnemy.pos = glm::vec3(200, 1, 200);
		enemy.push_back(tentativeEnemy);
	}





	//カメラ設定---------------------------------------------------------------------
	camera = new Camera();
	camera->target = cursor->pos;

}

void Play::update()
{

	//カーソル------------------------------
	cursor->update();

	//プレイヤーキャラクター----------------
	std::list < Player > ::iterator playerIter = player.begin();
	while (playerIter != player.end())
	{
		playerIter->move();
		playerIter->collisionCursor();
		playerIter->attackToCamp();
		playerIter->update();

		++playerIter;
	}

	//カメラ--------------------------------
	camera->update();

}

void Play::draw()
{
	glColor3f(1, 1, 1);		//色の初期化
	glClearColor(0, 0.39f, 1, 0.5f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//フィールド-----------------------------
	field->draw();

	//カーソル-------------------------------
	cursor->draw();

	//プレイヤーキャラクター-----------------
	std::list< Player > ::iterator playerIter = player.begin();
	while (playerIter != player.end())
	{
		playerIter->draw();
		++playerIter;
	}

	//エネミーキャラクター-------------------
	std::list< Enemy > ::iterator enemyIter = enemy.begin();
	while (enemyIter != enemy.end())
	{
		enemyIter->draw();
		++enemyIter;
	}


	//プレイヤー陣地-------------------------
	std::list< PlayerCamp > ::iterator playerCampIter = playerCamp.begin();
	while (playerCampIter != playerCamp.end())
	{
		playerCampIter->draw();
		++playerCampIter;
	}

	//エネミー陣地--------------------------
	std::list< EnemyCamp > ::iterator enemyCampIter = enemyCamp.begin();
	while (enemyCampIter != enemyCamp.end())
	{
		enemyCampIter->draw();
		++enemyCampIter;
	}



	//カメラ--------------------------------
	camera->draw();
}