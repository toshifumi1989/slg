#define _USE_MATH_DEFINES

#include <math.h>
#include "enemy.h"
#include "../glut.h"
#include "field.h"

std::list< Enemy > enemy;


////////////////////////
//更新
////////////////////////
void Enemy::update()
{
	targetFront = atan2(pos.x - moveTargetPoint.x, pos.z - moveTargetPoint.z) * 180 / M_PI;
	front = front + (targetFront - front) / 10.f;

	field->intersect(pos);
	pos.y = field->charcterHeight + 1;

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
		}
		glEnd();

	}
	glPopMatrix();
	glDisable(GL_DEPTH_TEST);
}

void Enemy::AI()
{



}