#define _USE_MATH_DEFINES

#include  <math.h>
#include "battleSetUp.h"
#include "../library/field.h"
#include "../library/camera.h"
#include "../library/player.h"
#include "../library/enemy.h"
#include "../play/cursor.h"
#include "../play/playerCamp.h"
#include "../play/enemyCamp.h"

extern unsigned char keys[256];

void BattleSetUp::init()
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

	//�{�w
	playerBase = new PlayerCamp();
	playerBase->pos = glm::vec3(field->size / 2 - 75, 1, field->size / 2 - 75);
	playerBase->size = glm::vec3(10.f, 3.f, 10.f);
	field->intersect(playerBase->pos);
	playerBase->pos.y = field->charcterHeight + 1;

	//�G�l�~�[-----------------------------------------------------------------------------

	//�{�w
	enemyBase = new EnemyCamp();
	enemyBase->pos = glm::vec3(field->size / 2 + 75, 1, field->size / 2 + 75);
	enemyBase->size = glm::vec3(10.f, 3.f, 10.f);
	field->intersect(enemyBase->pos);
	enemyBase->pos.y = field->charcterHeight + 1;

	for (int i = 0; i < 2; i++)
	{
		EnemyCamp* tentativeEnemyCamp = new EnemyCamp();
		tentativeEnemyCamp->pos = glm::vec3(field->size / 2 + rand() % 45 + 20, 1, field->size / 2 + rand() % 45 + 20);
		field->intersect(tentativeEnemyCamp->pos);
		tentativeEnemyCamp->pos.y = field->charcterHeight + 1;
		tentativeEnemyCamp->ID = i;
		enemyCamp.push_back(tentativeEnemyCamp);
	}

	//�G�l�~�[�L�����N�^�[�ݒ�

	for (int i = 0; i < 3; i++)
	{
		Enemy *tentativeEnemy = new Enemy();
		//�����ʒu
		int enemyInitPos = 10;
		if (i == 0)
		{
			//���S
			tentativeEnemy->pos = glm::vec3(field->size / 2.f + 60, 1, field->size / 2.f + 60);
		}
		else if (i % 2 == 0)
		{
			//�E��
			tentativeEnemy->pos = glm::vec3(field->size / 2.f + 60 - enemyInitPos * i / 2, 1, field->size / 2.f + 60 + enemyInitPos * i / 2);
		}
		else
		{
			//����
			tentativeEnemy->pos = glm::vec3(field->size / 2.f + 60 + enemyInitPos * (i / 2 + 1), 1, field->size / 2.f + 60 - enemyInitPos * (i / 2 + 1));
		}

		//�n�߂̌���
		tentativeEnemy->moveTargetPoint = glm::vec3(field->size / 2 - 75, 1, field->size / 2 - 75);
		tentativeEnemy->ID = i;
		enemy.push_back(tentativeEnemy);
	}

	//�J�����ݒ�---------------------------------------------------------------------
	camera = new Camera();
	camera->target = cursor->pos;

}

void BattleSetUp::update()
{
	if (setUpScene == SetupScene::CursorMove)
	{
		cursorMove();
	}
	else
	{
		typeChoice();
	}

	std::list< Enemy* >::const_iterator enemyIter = enemy.begin();
	while (enemyIter != enemy.end())
	{
		(*enemyIter)->update();
		++enemyIter;
	}

}

void BattleSetUp::cursorMove()
{
	//���w�̃G���A���̂݃L������u����
	if (cursor->pos.z > 28 && cursor->pos.x > 28 && cursor->pos.x + cursor->pos.z < 196)
	{
		//����I��
		if (keys[' '] == 1)
		{
			setUpScene = SetupScene::TypeChoice;

		}
	}


	//�J�[�\��
	cursor->setup();

	//�J����
	camera->setUp();
}

void BattleSetUp::typeChoice()
{
	//����
	if (keys['1'] == 1)
	{
		if (playerCounter < maxPlayerCounter)
		{
			Player *infantry = new Player();
			infantry->type = 1;
			infantry->Attack = 10;
			infantry->Defense = 20;
			infantry->attackRange = 10;
			infantry->speedCoefficient = 0.1f;
			infantry->pos = cursor->pos;
			infantry->ID = cursor->playerNum;
			player.push_back(infantry);

			playerCounter++;
		}
		cursor->playerNum += 1;
		setUpScene = SetupScene::CursorMove;
	}
	//�R��
	else if (keys['2'] == 1)
	{
		if (playerCounter < maxPlayerCounter)
		{
			Player *cavalry = new Player();
			cavalry->type = 2;
			cavalry->Attack = 20;
			cavalry->Defense = 7;
			cavalry->attackRange = 10;
			cavalry->speedCoefficient = 0.2f;
			cavalry->pos = cursor->pos;
			cavalry->ID = cursor->playerNum;
			player.push_back(cavalry);

			playerCounter++;
		}
		cursor->playerNum += 1;
		setUpScene = SetupScene::CursorMove;
	}
	//�|��
	else if (keys['3'] == 1)
	{
		if (playerCounter < maxPlayerCounter)
		{
			Player *archer = new Player();
			archer->type = 3;
			archer->Attack = 10;
			archer->Defense = 5;
			archer->attackRange = 20;
			archer->speedCoefficient = 0.1f;
			archer->pos = cursor->pos;
			archer->ID = cursor->playerNum;
			player.push_back(archer);

			playerCounter++;
		}
		cursor->playerNum += 1;
		setUpScene = SetupScene::CursorMove;
	}
	//���w
	else if (keys['4'] == 1)
	{
		if (campCounter < maxCampCounter)
		{
			PlayerCamp *camp = new PlayerCamp();
			camp->pos = cursor->pos;
			camp->ID = cursor->pCumpNum;
			playerCamp.push_back(camp);

			campCounter++;
		}
		cursor->pCumpNum += 1;
		setUpScene = SetupScene::CursorMove;
	}
	//�J����
	camera->setUp();
}

void BattleSetUp::draw()
{
	glColor3f(1, 1, 1);		//�F�̏�����
	glClearColor(0, 0.39f, 1, 0.5f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	playerSelectLine();

	//�t�B�[���h-----------------------------------------
	field->draw();

	//�J�[�\��------------------------------------------
	cursor->draw();

	//�v���C���[-----------------------------------------
	//�L�����N�^�[
	std::list< Player* >::const_iterator playerIter = player.begin();
	while (playerIter != player.end())
	{
		(*playerIter)->draw((*playerIter)->type);
		++playerIter;
	}

	//�{�w
	playerBase->draw();

	//���̐w�n
	std::list< PlayerCamp* >::const_iterator playerCampIter = playerCamp.begin();
	while (playerCampIter != playerCamp.end())
	{
		(*playerCampIter)->draw();
		++playerCampIter;
	}

	//�G�l�~�[-------------------------------------------
	//�L�����N�^�[
	std::list<Enemy* >::const_iterator enemyIter = enemy.begin();
	while (enemyIter != enemy.end())
	{
		(*enemyIter)->draw();
		++enemyIter;
	}

	//�{�w
	enemyBase->draw();

	//���̐w
	std::list< EnemyCamp* >::const_iterator enemyCampIter = enemyCamp.begin();
	while (enemyCampIter != enemyCamp.end())
	{
		(*enemyCampIter)->draw();
		++enemyCampIter;
	}


	//�J����---------------------------------------------
	camera->draw();
}

void BattleSetUp::playerSelectLine()
{
	glEnable(GL_DEPTH_TEST);
	glPushMatrix();
	{
		glColor3f(1, 1, 0);
		glBegin(GL_QUADS);
		{
			glVertex3f(28, 0, 28);
			glVertex3f(28, 0, 168);
			glVertex3f(28, 10, 168);
			glVertex3f(28, 10, 28);

			glVertex3f(28, 0, 28);
			glVertex3f(168, 0, 28);
			glVertex3f(168, 10, 28);
			glVertex3f(28, 10, 28);

			glVertex3f(28, 0, 168);
			glVertex3f(168, 0, 28);
			glVertex3f(168, 10, 28);
			glVertex3f(28, 10, 168);
		}
		glEnd();

	}
	glPopMatrix();
	glDisable(GL_DEPTH_TEST);
}