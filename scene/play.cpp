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

	//�J�[�\��------------------------------
	cursor->update();


	//�v���C���[-------------------------------------------
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

	//�G�l�~�[----------------------------------------------------------




	//���S����-------------------------------
	dead< Player* >(player);
	dead< PlayerCamp* >(playerCamp);
	dead< Enemy* >(enemy);
	dead< EnemyCamp* >(enemyCamp);

	//�J����--------------------------------
	camera->update();

}



void Play::draw()
{
	glColor3f(1, 1, 1);		//�F�̏�����
	glClearColor(0, 0.39f, 1, 0.5f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//�t�B�[���h-----------------------------
	field->draw();

	//�J�[�\��-------------------------------
	cursor->draw();

	//�v���C���[-----------------------------
	//�v���C���[�L�����N�^�[
	std::list< Player* > ::const_iterator playerIter = player.begin();
	while (playerIter != player.end())
	{
		(*playerIter)->draw((*playerIter)->type);
		++playerIter;
	}

	//�v���C���[�w�n

	playerBase->draw();//�����{�w

	std::list< PlayerCamp* > ::const_iterator playerCampIter = playerCamp.begin();
	while (playerCampIter != playerCamp.end())
	{
		(*playerCampIter)->draw();
		++playerCampIter;
	}



	//�G�l�~�[-------------------------------
	//�G�l�~�[�L�����N�^�[
	std::list< Enemy* > ::const_iterator enemyIter = enemy.begin();
	while (enemyIter != enemy.end())
	{
		(*enemyIter)->draw();
		++enemyIter;
	}

	//�G�l�~�[�w�n

	enemyBase->draw();//�G�{�w

	std::list< EnemyCamp* > ::const_iterator enemyCampIter = enemyCamp.begin();
	while (enemyCampIter != enemyCamp.end())
	{
		(*enemyCampIter)->draw();
		++enemyCampIter;
	}



	//�J����--------------------------------
	camera->draw();
}