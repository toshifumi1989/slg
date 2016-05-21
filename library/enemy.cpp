#include "enemy.h"
#include "../glut.h"

std::list< Enemy > enemy;


////////////////////////
//�X�V
////////////////////////
void Enemy::update() 
{

	lastPos = pos;
}

///////////////////////
//�`��
///////////////////////
void Enemy::draw()
{
	glPushMatrix();
	{
		glEnable(GL_DEPTH_TEST);
		glColor3f(0.7f, 0.3f, 0.2f);	//�G�l�~�[�p�̐�
		glTranslatef(pos.x, pos.y, pos.z);
		glRotatef(front, 0, 1, 0);
		{
			glScalef(5.f, 1.f, 3.f);
			glutSolidCube(1);
		}
		glDisable(GL_DEPTH_TEST);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glEnable(GL_DEPTH_TEST);
		glColor3f(0.7f, 0.3f, 0.2f);	//�G�l�~�[�p�̐�
		glTranslatef(pos.x, pos.y, pos.z + 2);
		glRotatef(front, 0, 1, 0);
		{
			glScalef(2.f, 1.f, 3.f);
			glutSolidCube(1);
		}
		glDisable(GL_DEPTH_TEST);
	}
	glPopMatrix();

}

////////////////////////
//
///////////////////////
void Enemy::collisionCursor()
{

}