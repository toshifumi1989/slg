#define _USE_MATH_DEFINES

#include <stdlib.h>
#include <math.h>
#include "../glut.h"
#include "player.h"
#include "../play/cursor.h"
#include "../play/enemyCamp.h"
#include "field.h"

std::list< Player* > player;
extern Cursor *cursor;
extern std::list< EnemyCamp* > enemyCamp;
extern EnemyCamp *enemyBase;
extern unsigned char keys[];



//////////////////////////////////
//�X�V
//////////////////////////////////
void Player::update()
{
	//�v���C���[�̌�����ύX����
	//�����̖ڕW�ƌ��݂̍�
	float differenceFront = targetFront - front;
	targetFront = atan2(pos.x - moveTargetPoint.x, pos.z - moveTargetPoint.z) * 180 / M_PI;
	if (differenceFront > 0)
	{
		front = front + differenceFront / 10.f;
	}
	else
	{
		front = front + differenceFront / 10.f;
	}

	//�L�����̍���
	field->intersect(pos);
	pos.y = field->charcterHeight + 1;

	lastPos = pos;
}

///////////////////////////////////
//�`��
///////////////////////////////////
void Player::draw(unsigned char _type)
{
	glEnable(GL_DEPTH_TEST);
	//�v���C���[�L�����N�^�[
	glPushMatrix();
	{

		glColor3f(characterColor.r, characterColor.g, characterColor.b);
		glTranslatef(pos.x, pos.y, pos.z);
		glRotatef(front, 0, 1, 0);

		//����
		if (_type == 1)
		{
			glRotatef(90, 1, 0, 0);			//������ς��邽��
			glutSolidTorus(1, 2, 50, 50);
		}
		//�R��
		else if (_type == 2)
		{
			glRotatef(180, 0, 1, 0);			//������ς��邽��
			glutSolidCone(3, 5, 4, 4);
		}
		//�|��
		else if (_type == 3)
		{
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
		}



		//HP
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


	//�ڕW�n�_
	if (moveOnFlag == true)
	{
		glPushMatrix();
		{
			glColor3f(characterColor.r, characterColor.g, characterColor.b);
			glTranslatef(moveTargetPoint.x, moveTargetPoint.y, moveTargetPoint.z);
			
			glScalef(1.f, 1.f, 1.f);

		}
		glPopMatrix();

	}

}

/////////////////////////////////////////
//�J�[�\���Ƃ̓����蔻��
/////////////////////////////////////////
void Player::collisionCursor()
{
	//�J�[�\���ƃv���C���[�L�����N�^�Ƃ̋���
	const float cursorToPlayer =
		(pos.x - cursor->pos.x) * (pos.x - cursor->pos.x)
		+ (pos.y - cursor->pos.y) * (pos.y - cursor->pos.y)
		+ (pos.z - cursor->pos.z) * (pos.z - cursor->pos.z);

	//�����������߂����
	if (cursorToPlayer < 25)
	{
		cursor->collision = true;
		cursor->colorCounter += 0.05f;
		if (keys[' '])
		{
			selectedFlag = true;

		}
	}
	else
	{
		cursor->collision = false;
		cursor->colorCounter = 0;
		if (keys[' '])
		{
			selectedFlag = false;

		}
	}

}

///////////////////////////////////
//�ړ�
///////////////////////////////////
void Player::move()
{
	//�J�[�\���ƃv���C���[�̋���
	const float cursorToPlayer =
		(pos.x - cursor->pos.x) * (pos.x - cursor->pos.x)
		+ (pos.y - cursor->pos.y) * (pos.y - cursor->pos.y)
		+ (pos.z - cursor->pos.z) * (pos.z - cursor->pos.z);

	//�v���C���[�L�����̑I����
	if (selectedFlag == true)
	{
		//�L�����N�^�[�����F��
		characterColor = glm::vec3(1, 1, 0);

		if (keys[' '])
		{
			//�ړ��̖ړI�n�ݒ�
			if (cursorToPlayer > 25)
			{
				moveOnFlag = true;
				moveTargetPoint = glm::vec3(cursor->pos.x, pos.y, cursor->pos.z);	//�ړI�n

				//�ړ��̂��߂ɁA���K��
				glm::vec3 PlayerToTargetPoint(
					moveTargetPoint.x - pos.x,
					0,
					moveTargetPoint.z - pos.z);

				speed = glm::normalize(PlayerToTargetPoint) * speedCoefficient;



			}
		}
	}
	else
	{
		//�ɖ߂�
		characterColor = glm::vec3(0.2f, 0.4f, 0.7f);
	}

	//�ړI�n�܂ł̋���
	const float playerToTargetPoint =
		(pos.x - moveTargetPoint.x) * (pos.x - moveTargetPoint.x)
		+ (pos.y - moveTargetPoint.y) * (pos.y - moveTargetPoint.y)
		+ (pos.z - moveTargetPoint.z) * (pos.z - moveTargetPoint.z);


	//�ړI�n�ɒ������Ƃ�
	if (playerToTargetPoint < 4)
	{
		//�ړ��I���
		moveOnFlag = false;
		speed = glm::vec3(0, 0, 0);

	}

	if (moveOnFlag == true)
	{
		if (OnAttack == true)
		{
			pos += speed / 2.f;
		}
		else
		{
			pos += speed;
		}

	}

}

///////////////////////////////////
//�G�{�w�ɍU��
///////////////////////////////////
void Player::attackToBase()
{
	//�{�w
	const float playerToEnemyBase =
		(pos.x - enemyBase->pos.x) * (pos.x - enemyBase->pos.x)
		+ (pos.y - enemyBase->pos.y) * (pos.y - enemyBase->pos.y)
		+ (pos.z - enemyBase->pos.z) * (pos.z - enemyBase->pos.z);

	if (playerToEnemyBase < 20 * attackRange)
	{
		OnAttack = true;
		enemyBase->damage = (Attack - enemyBase->Defense) / 10.f;

		enemyBase->HP -= enemyBase->damage;

		if (playerToEnemyBase < 10 * attackRange)
		{
			pos = lastPos;
			moveOnFlag = false;
		}
	}
	else
	{
		OnAttack = false;
		enemyBase->damage = 0;
	}

}
