#include <stdlib.h>
#include <stdio.h>
#include "../glut.h"
#include "manager.h"
#include "../library/camera.h"
#include "../play/cursor.h"
#include "../library/texture.h"
#include "../library/wavFile.h"

extern Camera *camera;
extern Cursor *cursor;
unsigned char keys[256] = {};

////////////////////////////////////////////////////
// �֐��v���g�^�C�v�i��ɌĂяo���֐����ƈ����̐錾�j
////////////////////////////////////////////////////
void init(void);
void display(void);
void timer(int value);
void keyboard(unsigned char key, int x, int y);
void keyboardUp(unsigned char key, int x, int y);





/////////////////////////////////////////////////
//�}�E�X
/////////////////////////////////////////////////
void mouse(int button, int state, int x, int y) 
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) 
	{

	}


}

//�}�E�X�̃{�^���������ꂽ���
void motion(int x, int y) 
{

	//cursor->pos.x += (y - 350) / 1000.f;
	//cursor->pos.z += (x - 350) / 1000.f;

	glutPostRedisplay();
}

//�}�E�X�̃{�^����������Ă��Ȃ����
void passiveMotion(int x, int y) 
{

}


//////////////////////////////////////////////////
//�L�[�{�[�h��ON�AOFF
//////////////////////////////////////////////////
void keyboard(unsigned char key, int x, int y)
{
	keys[key] = 1;
}
void keyboardUp(unsigned char key, int x, int y) 
{
	keys[key] = 0;
}

void special(int key, int x, int y)
{
	camera->specialKey = key;

}

void specialUp(int key, int x, int y)
{
	camera->specialKey = 0;
}
////////////////////////////////////////////////////
//�^�C�}�[�֐�
////////////////////////////////////////////////////
void timer(int value) 
{

	glutPostRedisplay();

	// 1000�~���b�� 1 �b
	glutTimerFunc(1000 / 60, timer, 0);
}


////////////////////////////////////////////////////
//�����ݒ�
////////////////////////////////////////////////////
void init(void) 
{
	glGenTextures(TEXTURE_ID::TEXTURE_MAX, textures);
	initMusic();
}


///////////////////////////////////////
//�`��
////////////////////////////////////////
void display(void)
{

	Manager::getInstance()->update();

	glFlush();
}


////////////////////////////////////////////////////
//���C���֐�
////////////////////////////////////////////////////
int main(int argc, char *argv[])
{

	glutInit(&argc, argv);
	glutInitWindowSize(1000, 700);
	glutCreateWindow("game");

	glutDisplayFunc(display);
	glutTimerFunc(0, timer, 0);

	//�}�E�X����
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutPassiveMotionFunc(passiveMotion);

	//�L�[�{�[�h����
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);
	glutSpecialFunc(special);
	glutSpecialUpFunc(specialUp);

	glutIgnoreKeyRepeat(GL_TRUE);

	init();
	glutMainLoop();

}
