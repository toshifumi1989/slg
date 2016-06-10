#define _USE_MATH_DEFINES

#include <math.h>
#include "enemy.h"
#include "player.h"
#include "../play/playerCamp.h"
#include "../play/enemyCamp.h"
#include "../glut.h"
#include "field.h"

std::list< Enemy* > enemy;

////////////////////////
//更新
////////////////////////
void Enemy::update()
{
	//向き
	targetFront = atan2(pos.x - moveTargetPoint.x, pos.z - moveTargetPoint.z) * 180 / M_PI;
	front = front + (targetFront - front) / 10.f;

	//y座標
	field->intersect(pos);
	pos.y = field->charcterHeight + 1;

	//兵糧の消費
	food--;

	glm::vec3 enemyToTarget(
		moveTargetPoint.x - pos.x,
		0,
		moveTargetPoint.z - pos.z);

	if (moveOnFlag == true)
	{
		speed = glm::normalize(enemyToTarget) * speedCoefficient;

		pos += speed;
	}


	lastPos = pos;
}

///////////////////////
//描画
///////////////////////
void Enemy::draw()
{
	glEnable(GL_DEPTH_TEST);
	glPushMatrix();
	{

		glColor3f(0.7f, 0.4f, 0.2f);	//エネミー用の赤
		glTranslatef(pos.x, pos.y, pos.z);
		glRotatef(front, 0, 1, 0);

		glPushMatrix();
		{
			glScalef(5.f, 1.f, 3.f);
			glutSolidCube(1);
		}
		glPopMatrix();

		glPushMatrix();
		{
			glTranslatef(0, 0, -2);
			glScalef(2.f, 1.f, 3.f);
			glutSolidCube(1);
		}
		glPopMatrix();

		//HP表示
		glm::mat4 view;
		glGetFloatv(GL_MODELVIEW_MATRIX, (float*)&view);

		glm::mat4 m = glm::inverse(view);
		m[3][0] = m[3][1] = m[3][2] = 0;

		glMultMatrixf((float*)&m);
		glTranslatef(-1.5f, 3, 0);
		glColor3f(0.8f, 0.8f, 0);
		glScalef(3.f, 2.f, 0);
		glBegin(GL_QUAD_STRIP);
		{

			glVertex3f(HP / 1000.f, 0.5f, 0);
			glVertex3f(0, 0.5f, 0);
			glVertex3f(HP / 1000.f, 0, 0);
			glVertex3f(0, 0, 0);

			if (OnDefense == true)
			{
				glColor3f(1, 0, 0);
				glVertex3f(HP / 1000.f + 0.1f, 0.6f, 0);
				glVertex3f(-0.1f, 0.6f, 0);
				glVertex3f(HP / 1000.f + 0.1f, -0.1f, 0);
				glVertex3f(-0.1f, -0.1f, 0);
			}
		}
		glEnd();

	}
	glPopMatrix();
	glDisable(GL_DEPTH_TEST);
}

void Enemy::attackToBase()
{

	const float enemyToObject =
		(pos.x - playerBase->pos.x) * (pos.x - playerBase->pos.x)
		+ (pos.y - playerBase->pos.y) * (pos.y - playerBase->pos.y)
		+ (pos.z - playerBase->pos.z) * (pos.z - playerBase->pos.z);

	if (enemyToObject < 10 * attackRange)
	{
		OnAttack = true;
		playerBase->OnDefense = true;
		playerBase->damage = (Attack - playerBase->Defense) / 10.f;

		playerBase->HP -= playerBase->damage;

		if (enemyToObject < 5 * attackRange)
		{
			pos = lastPos;
			moveOnFlag = false;
		}
	}
	else
	{
		OnAttack = false;
		playerBase->OnDefense = false;
		playerBase->damage = 0;
		moveOnFlag = true;
	}


}

void Enemy::AI(unsigned char _targetType, unsigned char _target, unsigned char _pattern)
{
	const float enemyToDefender =
		(pos.x - moveTargetPoint.x) * (pos.x - moveTargetPoint.x)
		+ (pos.y - moveTargetPoint.y) * (pos.y - moveTargetPoint.y)
		+ (pos.z - moveTargetPoint.z) * (pos.z - moveTargetPoint.z);

	//攻撃目標がBase
	if (_targetType == 0)
	{

		moveTargetPoint = playerBase->pos;

	}
	//攻撃目標がplayerCamp
	else if (_targetType == 1)
	{
		std::list< PlayerCamp* >::iterator playerCampIter = playerCamp.begin();
		while (playerCampIter != playerCamp.end())
		{
			if ((*playerCampIter)->ID == _target)
			{
				moveTargetPoint = (*playerCampIter)->pos;

			}

		}


		//陣をすべて壊したら本陣を目指す
		if (playerCamp.empty() == true)
		{
			enemyBase->targetType = 0;
		}
	}
	//攻撃目標がplayer
	else
	{

		std::list< Player* >::iterator playerIter = player.begin();
		while (playerIter != player.end())
		{
			if ((*playerIter)->ID == _target)
			{
				moveTargetPoint = (*playerIter)->pos;

			}	
		}
	}

}