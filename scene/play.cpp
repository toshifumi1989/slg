#define _USE_MATH_DEFINES

#include  <math.h>
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
	//フィールド----------------------------------------------------------------
	glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_ID::FIELD_SETUP]);
	field = new Field();
	field->setup("setup.bmp");

	glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_ID::FIELD]);
	field->read("field.bmp");

	//カーソル設定-----------------------------------------------------------------------
	cursor = new Cursor();
	cursor->pos = glm::vec3(field->size / 2.f, 4, field->size / 2.f);
	const float moveSpeed = 0.01f;
	cursor->speed = glm::vec3(moveSpeed, 0, moveSpeed);

	//プレイヤー--------------------------------------------------------------------------------

	//プレイヤー陣地

		//本陣
	playerBase = new PlayerCamp();
	playerBase->pos = glm::vec3(field->size / 2 - 75, 1, field->size / 2 - 75);
	playerBase->size = glm::vec3(10.f, 3.f, 10.f);
	field->intersect(playerBase->pos);
	playerBase->pos.y = field->charcterHeight + 1;


	for (int i = 0; i < 2; i++)
	{
		PlayerCamp tentativePlayerCamp;
		tentativePlayerCamp.pos = glm::vec3(field->size / 2 - rand() % 45 - 20, 1, field->size / 2 - rand() % 45 - 20);
		field->intersect(tentativePlayerCamp.pos);
		tentativePlayerCamp.pos.y = field->charcterHeight + 1;
		playerCamp.push_back(tentativePlayerCamp);
	}

	//プレイヤーキャラクター設定
	Player tentativePlayer;
	for (int i = 0; i < 3; i++)
	{
		//初期位置
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

		//始めの向き
		tentativePlayer.moveTargetPoint = glm::vec3(field->size / 2 + 75, 1, field->size / 2 + 75);

		player.push_back(tentativePlayer);
	}



	//エネミー-----------------------------------------------------------------------------
	//エネミー陣地

	//本陣
	enemyBase = new EnemyCamp();
	enemyBase->pos = glm::vec3(field->size / 2 + 75, 1, field->size / 2 + 75);
	enemyBase->size = glm::vec3(10.f, 3.f, 10.f);
	field->intersect(enemyBase->pos);
	enemyBase->pos.y = field->charcterHeight + 1;

	for (int i = 0; i < 2; i++)
	{
		EnemyCamp tentativeEnemyCamp;
		tentativeEnemyCamp.pos = glm::vec3(field->size / 2 + rand() % 45 + 20, 1, field->size / 2 + rand() % 45 + 20);
		field->intersect(tentativeEnemyCamp.pos);
		tentativeEnemyCamp.pos.y = field->charcterHeight + 1;
		enemyCamp.push_back(tentativeEnemyCamp);
	}

	//エネミーキャラクター設定
	Enemy tentativeEnemy;
	for (int i = 0; i < 3; i++)
	{
		//初期位置
		int enemyInitPos = 10;
		if (i == 0)
		{
			//中心
			tentativeEnemy.pos = glm::vec3(field->size / 2.f + 60, 1, field->size / 2.f + 60);
		}
		else if (i % 2 == 0)
		{
			//右側
			tentativeEnemy.pos = glm::vec3(field->size / 2.f + 60 - enemyInitPos * i / 2, 1, field->size / 2.f + 60 + enemyInitPos * i / 2);
		}
		else
		{
			//左側
			tentativeEnemy.pos = glm::vec3(field->size / 2.f + 60 + enemyInitPos * (i / 2 + 1), 1, field->size / 2.f + 60 - enemyInitPos * (i / 2 + 1));
		}

		//始めの向き
		tentativeEnemy.moveTargetPoint = glm::vec3(field->size / 2 - 75, 1, field->size / 2 - 75);

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


	//プレイヤー-------------------------------------------
	//プレイヤーキャラクター
	std::list < Player > ::iterator playerIter = player.begin();
	while (playerIter != player.end())
	{
		playerIter->move();
		playerIter->collisionCursor();
		playerIter->attackToCamp();
		playerIter->update();

		++playerIter;
	}
	//エネミー----------------------------------------------------------
	//エネミー陣地

	std::list< EnemyCamp >::iterator enemyCampIter = enemyCamp.begin();
	while (enemyCampIter != enemyCamp.end())
	{

		if (enemyCampIter->HP <= 0)
		{
			enemyCampIter = enemyCamp.erase(enemyCampIter);
		}
		else
		{
			++enemyCampIter;
		}

	}

	//エネミーキャラクター
	std::list< Enemy >::iterator enemyIter = enemy.begin();
	while (enemyIter != enemy.end())
	{
		enemyIter->update();
		++enemyIter;
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

	//プレイヤー-----------------------------
	//プレイヤーキャラクター
	std::list< Player > ::iterator playerIter = player.begin();
	while (playerIter != player.end())
	{
		playerIter->draw();
		++playerIter;
	}

	//プレイヤー陣地

	playerBase->draw();//味方本陣

	std::list< PlayerCamp > ::iterator playerCampIter = playerCamp.begin();
	while (playerCampIter != playerCamp.end())
	{
		playerCampIter->draw();
		++playerCampIter;
	}



	//エネミー-------------------------------
	//エネミーキャラクター
	std::list< Enemy > ::iterator enemyIter = enemy.begin();
	while (enemyIter != enemy.end())
	{
		enemyIter->draw();
		++enemyIter;
	}

	//エネミー陣地

	enemyBase->draw();//敵本陣

	std::list< EnemyCamp > ::iterator enemyCampIter = enemyCamp.begin();
	while (enemyCampIter != enemyCamp.end())
	{
		enemyCampIter->draw();
		++enemyCampIter;
	}



	//カメラ--------------------------------
	camera->draw();
}