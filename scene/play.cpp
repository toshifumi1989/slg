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
	//�t�B�[���h----------------------------------------------------------------
	glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_ID::FIELD_SETUP]);
	field = new Field();
	field->setup("setup.bmp");

	glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_ID::FIELD]);
	field->read("field.bmp");

	//�J�[�\���ݒ�-----------------------------------------------------------------------
	cursor = new Cursor();
	cursor->pos = glm::vec3(field->size / 2.f, 4, field->size / 2.f);
	const float moveSpeed = 0.01f;
	cursor->speed = glm::vec3(moveSpeed, 0, moveSpeed);

	//�v���C���[--------------------------------------------------------------------------------

	//�v���C���[�w�n

		//�{�w
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

	//�v���C���[�L�����N�^�[�ݒ�
	Player tentativePlayer;
	for (int i = 0; i < 3; i++)
	{
		//�����ʒu
		int playerInitPos = 10;
		if (i == 0)
		{
			//���S
			tentativePlayer.pos = glm::vec3(field->size / 2.f - 60, 1, field->size / 2.f - 60);
		}
		else if (i % 2 == 0)
		{
			//�E��
			tentativePlayer.pos = glm::vec3(field->size / 2.f - 60 - playerInitPos * i / 2, 1, field->size / 2.f - 60 + playerInitPos * i / 2);
		}
		else
		{
			//����
			tentativePlayer.pos = glm::vec3(field->size / 2.f - 60 + playerInitPos * (i / 2 + 1), 1, field->size / 2.f - 60 - playerInitPos * (i / 2 + 1));
		}

		//�n�߂̌���
		tentativePlayer.moveTargetPoint = glm::vec3(field->size / 2 + 75, 1, field->size / 2 + 75);

		player.push_back(tentativePlayer);
	}



	//�G�l�~�[-----------------------------------------------------------------------------
	//�G�l�~�[�w�n

	//�{�w
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

	//�G�l�~�[�L�����N�^�[�ݒ�
	Enemy tentativeEnemy;
	for (int i = 0; i < 3; i++)
	{
		//�����ʒu
		int enemyInitPos = 10;
		if (i == 0)
		{
			//���S
			tentativeEnemy.pos = glm::vec3(field->size / 2.f + 60, 1, field->size / 2.f + 60);
		}
		else if (i % 2 == 0)
		{
			//�E��
			tentativeEnemy.pos = glm::vec3(field->size / 2.f + 60 - enemyInitPos * i / 2, 1, field->size / 2.f + 60 + enemyInitPos * i / 2);
		}
		else
		{
			//����
			tentativeEnemy.pos = glm::vec3(field->size / 2.f + 60 + enemyInitPos * (i / 2 + 1), 1, field->size / 2.f + 60 - enemyInitPos * (i / 2 + 1));
		}

		//�n�߂̌���
		tentativeEnemy.moveTargetPoint = glm::vec3(field->size / 2 - 75, 1, field->size / 2 - 75);

		enemy.push_back(tentativeEnemy);
	}


	//�J�����ݒ�---------------------------------------------------------------------
	camera = new Camera();
	camera->target = cursor->pos;

}

void Play::update()
{

	//�J�[�\��------------------------------
	cursor->update();


	//�v���C���[-------------------------------------------
	//�v���C���[�L�����N�^�[
	std::list < Player > ::iterator playerIter = player.begin();
	while (playerIter != player.end())
	{
		playerIter->move();
		playerIter->collisionCursor();
		playerIter->attackToCamp();
		playerIter->update();

		++playerIter;
	}
	//�G�l�~�[----------------------------------------------------------
	//�G�l�~�[�w�n

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

	//�G�l�~�[�L�����N�^�[
	std::list< Enemy >::iterator enemyIter = enemy.begin();
	while (enemyIter != enemy.end())
	{
		enemyIter->update();
		++enemyIter;
	}

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
	std::list< Player > ::iterator playerIter = player.begin();
	while (playerIter != player.end())
	{
		playerIter->draw();
		++playerIter;
	}

	//�v���C���[�w�n

	playerBase->draw();//�����{�w

	std::list< PlayerCamp > ::iterator playerCampIter = playerCamp.begin();
	while (playerCampIter != playerCamp.end())
	{
		playerCampIter->draw();
		++playerCampIter;
	}



	//�G�l�~�[-------------------------------
	//�G�l�~�[�L�����N�^�[
	std::list< Enemy > ::iterator enemyIter = enemy.begin();
	while (enemyIter != enemy.end())
	{
		enemyIter->draw();
		++enemyIter;
	}

	//�G�l�~�[�w�n

	enemyBase->draw();//�G�{�w

	std::list< EnemyCamp > ::iterator enemyCampIter = enemyCamp.begin();
	while (enemyCampIter != enemyCamp.end())
	{
		enemyCampIter->draw();
		++enemyCampIter;
	}



	//�J����--------------------------------
	camera->draw();
}