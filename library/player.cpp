#include <stdlib.h>
#include "../glut.h"
#include "player.h"
#include "../play/cursor.h"
#include "../play/enemyCamp.h"


std::list< Player > player;
extern Cursor *cursor;
extern std::list< EnemyCamp > enemyCamp;
extern unsigned char keys[];

//////////////////////////////////
//�X�V
//////////////////////////////////
void Player::update()
{
	if (moveOnFlag == true) {
		pos += speed;
	}

	lastPos = pos;
}

///////////////////////////////////
//�`��
///////////////////////////////////
void Player::draw()
{
	//�v���C���[�L�����N�^�[
	glPushMatrix();
	{
		glEnable(GL_DEPTH_TEST);
		glColor3f(characterColor.r, characterColor.g, characterColor.b);
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
		glColor3f(characterColor.r, characterColor.g, characterColor.b);
		glTranslatef(pos.x, pos.y, pos.z + 2);
		glRotatef(front, 0, 1, 0);
		{
			glScalef(2.f, 1.f, 3.f);
			glutSolidCube(1);
		}
		glDisable(GL_DEPTH_TEST);
	}
	glPopMatrix();


	//�ڕW�n�_
	if (moveOnFlag == true)
	{
		glPushMatrix();
		{
			glEnable(GL_DEPTH_TEST);
			glColor3f(characterColor.r, characterColor.g, characterColor.b);
			glTranslatef(moveTargetPoint.x, moveTargetPoint.y, moveTargetPoint.z);
			glRotatef(90, 1, 0, 0);	//������ς��邽��
			glScalef(1.f, 1.f, 1.f);
			glutSolidTorus(1, 2, 10, 10);
			glDisable(GL_DEPTH_TEST);
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
	if (cursorToPlayer < 16)
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

				speed = glm::normalize(PlayerToTargetPoint) * 0.1f;

			}
		}
	}
	else
	{
		//�ɖ߂�
		characterColor = glm::vec3(0.2f, 0.3f, 0.7f);
	}

	//�ړI�n�܂ł̋���
	const float playerToTargetPoint =
		(pos.x - moveTargetPoint.x) * (pos.x - moveTargetPoint.x)
		+ (pos.y - moveTargetPoint.y) * (pos.y - moveTargetPoint.y)
		+ (pos.z - moveTargetPoint.z) * (pos.z - moveTargetPoint.z);


	//�ړI�n�ɒ������Ƃ�
	if (playerToTargetPoint < 2)
	{
		//�ړ��I���
		moveOnFlag = false;
		speed = glm::vec3(0, 0, 0);

	}


}

///////////////////////////////////
//�G�w�n�ɍU��
///////////////////////////////////
void Player::attackToCamp() {

	std::list< EnemyCamp >::iterator enemyCampIter = enemyCamp.begin();

	while (enemyCampIter != enemyCamp.end())
	{
		const float playerToEnemyCamp =
			(pos.x - enemyCampIter->pos.x) * (pos.x - enemyCampIter->pos.x)
			+ (pos.y - enemyCampIter->pos.y) * (pos.y - enemyCampIter->pos.y)
			+ (pos.z - enemyCampIter->pos.z) * (pos.z - enemyCampIter->pos.z);

		if (playerToEnemyCamp < 100)
		{
			const int Damage = Attack - enemyCampIter->Defense;
			//enemyCampIter->damage = Damage / 10;
			enemyCampIter->HP -= Damage / 10;// enemyCampIter->damage;

			if (playerToEnemyCamp < 25)
			{
				pos = lastPos;
				moveOnFlag = false;
			}
		}
		else
		{
			enemyCampIter->damage = 0;
		}

		++enemyCampIter;
	}



}