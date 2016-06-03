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

void Play::init() {}

void Play::update()
{

	//カーソル------------------------------
	cursor->update();


	//プレイヤー-------------------------------------------
	std::list< Player* >::iterator playerIter = player.begin();
	std::list< Enemy* >::iterator enemyIter = enemy.begin();
	while (playerIter != player.end())
	{
		(*playerIter)->move();
		(*playerIter)->collisionCursor();
		(*playerIter)->attackToBase();
		(*playerIter)->attackToObject< Enemy* >(enemy);
		(*playerIter)->attackToObject< EnemyCamp* >(enemyCamp);
		(*playerIter)->update();

		++playerIter;
	}

	//エネミー----------------------------------------------------------




	//死亡判定-------------------------------
	dead< Player* >(player);
	dead< PlayerCamp* >(playerCamp);
	dead< Enemy* >(enemy);
	dead< EnemyCamp* >(enemyCamp);

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
	std::list< Player* > ::const_iterator playerIter = player.begin();
	while (playerIter != player.end())
	{
		(*playerIter)->draw((*playerIter)->type);
		++playerIter;
	}

	//プレイヤー陣地

	playerBase->draw();//味方本陣

	std::list< PlayerCamp* > ::const_iterator playerCampIter = playerCamp.begin();
	while (playerCampIter != playerCamp.end())
	{
		(*playerCampIter)->draw();
		++playerCampIter;
	}



	//エネミー-------------------------------
	//エネミーキャラクター
	std::list< Enemy* > ::const_iterator enemyIter = enemy.begin();
	while (enemyIter != enemy.end())
	{
		(*enemyIter)->draw();
		++enemyIter;
	}

	//エネミー陣地

	enemyBase->draw();//敵本陣

	std::list< EnemyCamp* > ::const_iterator enemyCampIter = enemyCamp.begin();
	while (enemyCampIter != enemyCamp.end())
	{
		(*enemyCampIter)->draw();
		++enemyCampIter;
	}



	//カメラ--------------------------------
	camera->draw();
}