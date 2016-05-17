#include <stdlib.h>
#include "cursor.h"
#include "../glut.h"

Cursor *cursor;

///////////////////////
//�X�V
///////////////////////
void Cursor::update() {

}


//////////////////////
//�`��
//////////////////////
void Cursor::draw() {
	glPushMatrix();
	{
		glEnable(GL_DEPTH_TEST);

		glColor3f(0, 0.8f, 0);
		glTranslatef(cursor->pos.x, cursor->pos.y, cursor->pos.z);

		glRotatef(cursor->front, 0, 1, 0);
		glRotatef(90, 1, 0, 0);	//�J�[�\�����������ɂ����
		glutSolidCone(1.0f, 1.0f, 3, 2);//�����F(���a, ����, Z���܂��̕�����, Z���ɉ�����������)

		cursor->front++;

		glDisable(GL_DEPTH_TEST);

	}
	glPopMatrix();
}