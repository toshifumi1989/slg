#include <stdlib.h>
#include "../glut.h"
#include "cursor.h"
#include "../library/field.h"
#include "../library/camera.h"

Cursor *cursor;
extern Camera *camera;
extern Field *field;
extern unsigned char keys[256];


///////////////////////
//�X�V
///////////////////////
void Cursor::update()
{
	//z���W�̈ړ�
	if (keys['w'] == 1)
	{
		pos.z += speed.z * camera->cameraHeight;
		pos.x += speed.x * camera->cameraHeight;
	}
	else if (keys['s'] == 1)
	{
		pos.z -= speed.z * camera->cameraHeight;
		pos.x -= speed.x * camera->cameraHeight;
	}

	//x���W�̈ړ�
	if (keys['a'] == 1)
	{
		pos.z -= speed.z * camera->cameraHeight;
		pos.x += speed.x * camera->cameraHeight;
	}
	else if (keys['d'] == 1)
	{
		pos.z += speed.z * camera->cameraHeight;
		pos.x -= speed.x * camera->cameraHeight;
	}


	if (pos.x > field->size / 2 + 100 || pos.x < field->size / 2 - 100 || pos.z > field->size / 2 + 100 || pos.z < field->size / 2 - 100) {
		pos = lastPos;

	}


	lastPos = pos;
}


//////////////////////
//�`��
//////////////////////
void Cursor::draw()
{
	glPushMatrix();
	{
		glEnable(GL_DEPTH_TEST);

		glColor3f(fabs(sin(colorCounter)), 1.f - 0.2f * fabs(sin(colorCounter)), fabs(sin(colorCounter)));
		glTranslatef(cursor->pos.x, cursor->pos.y, cursor->pos.z);

		glRotatef(cursor->front, 0, 1, 0);
		glRotatef(90, 1, 0, 0);	//�J�[�\�����������ɂ����
		glScalef(2.f, 2.f, 2.f);
		glutSolidCone(1.0f, 1.0f, 3, 2);//�����F(���a, ����, Z���܂��̕�����, Z���ɉ�����������)


		if (collision == true) {
			glColor3f(1, 0, 0);
			glutWireCone(1.0f, 1.0f, 3, 1);
		}


		cursor->front++;

		glDisable(GL_DEPTH_TEST);

	}
	glPopMatrix();
}