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
#include "../library/wavFile.h"

Texture *play;

void Play::init()
{
	//背景
	glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_ID::PLAY]);
	play = new Texture();
	play->read_alpha("play.bmp");


	//音楽
	bgm->playMusic(BGM::BATTLE_BGM);

	//敵の攻撃目標
	enemyBase->targetType = rand() % 3;
	//攻撃目標	0:playerBase  
	//			1:playerCamp
	//			2:player

	//1:playerCamp
	if (enemyBase->targetType == 1)
	{
		if (playerCamp.size() == 0)
		{
			enemyBase->targetType = 0;
		}
		else
		{
			//自陣の数だけの選択肢
			enemyBase->target = rand() % playerCamp.size();
		}

	}
	//2:player
	else if (enemyBase->targetType == 2)
	{
		if (player.size() == 0)
		{
			enemyBase->targetType = 0;
		}
		else
		{
			//playerの数の選択肢
			enemyBase->target = rand() % player.size();
		}
	}

	enemyBase->pattern = rand() % 2;
	//	0:攻撃を受けても進む
	//	1:攻撃を受けたら立ち止まる

}

void Play::update()
{

	//カーソル------------------------------
	cursor->update();


	//プレイヤー-------------------------------------------
	std::list< Player* >::iterator playerIter = player.begin();
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
	//キャラクター

	std::list< Enemy* >::iterator enemyIter = enemy.begin();
	while (enemyIter != enemy.end())
	{
		(*enemyIter)->AI(enemyBase->targetType, enemyBase->target, enemyBase->pattern);
		(*enemyIter)->attackToBase();
		(*enemyIter)->attackToObject< Player* >(player);
		(*enemyIter)->attackToObject< PlayerCamp* >(playerCamp);
		(*enemyIter)->update();
		++enemyIter;
	}


	//死亡判定-------------------------------
	//プレイヤーキャラクター
	playerIter = player.begin();
	while (playerIter != player.end())
	{
		if ((*playerIter)->HP <= 0)
		{
			Player* temp = (*playerIter);
			delete temp;
			playerIter = player.erase(playerIter);
		}
		else
		{
			++playerIter;
		}

	}



	//エネミーキャラクター
	enemyIter = enemy.begin();

	while (enemyIter != enemy.end())
	{
		if ((*enemyIter)->HP <= 0)
		{
			Enemy* temp = (*enemyIter);
			delete temp;
			enemyIter = enemy.erase(enemyIter);

		}
		else
		{
			++enemyIter;
		}
	}

	//エネミー陣
	std::list< EnemyCamp* >::iterator enemyCampIter;
	enemyCampIter = enemyCamp.begin();
	while (enemyCampIter != enemyCamp.end())
	{
		if ((*enemyCampIter)->HP <= 0)
		{
			EnemyCamp* temp = (*enemyCampIter);
			delete temp;
			enemyCampIter = enemyCamp.erase(enemyCampIter);

		}
		else {
			++enemyCampIter;
		}

		printf("%d\n", enemyCamp.size());

	}

	//カメラ--------------------------------
	camera->update();

}



void Play::draw()
{

	glColor3f(1, 1, 1);		//色の初期化
	glClearColor(0, 0.39f, 1, 0.5f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//カメラ--------------------------------
	camera->draw();

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

	twoDimension();

}

void Play::twoDimension()
{
	camera->twoDimensionCamera();

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_ID::PLAY]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glEnable(GL_BLEND);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPushMatrix();
	{
		glBegin(GL_QUADS);
		{
			glTexCoord2d(0, 1);
			glVertex3d(camera->left, camera->bottom, 0);
			glTexCoord2d(1, 1);
			glVertex3d(camera->right, camera->bottom, 0);
			glTexCoord2d(1, 0);
			glVertex3d(camera->right, camera->top, 0);
			glTexCoord2d(0, 0);
			glVertex3d(camera->left, camera->top, 0);
		}
		glEnd();

	}
	glPopMatrix();


	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

}

void Play::pDelete()
{
	delete playerBase;
	playerCamp.clear();
	delete enemyBase;
	enemyCamp.clear();

	bgm->stopMusic(BGM::BATTLE_BGM);
}
