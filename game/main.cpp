#include <stdlib.h>
#include <stdio.h>
#include "../glut.h"
#include "manager.h"
#include "../library/camera.h"

extern Camera *camera;

////////////////////////////////////////////////////
// 関数プロトタイプ（後に呼び出す関数名と引数の宣言）
////////////////////////////////////////////////////
void init(void);
void display(void);
void timer(int value);
void keyboard(unsigned char key, int x, int y);
void keyboardUp(unsigned char key, int x, int y);

unsigned char keys[256] = {};
extern GLuint textures[1];

/////////////////////////////////////////////////
//マウス
/////////////////////////////////////////////////
void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {

	}


}

//マウスのボタンが押された状態
void motion(int x, int y) {

	camera->pos.x += (y - 350) / 1000.f;
	camera->pos.z += (x - 350) / 1000.f;

	glutPostRedisplay();
}

//マウスのボタンが押されていない状態
void passiveMotion(int x, int y) {

}


//////////////////////////////////////////////////
//キーボードのON、OFF
//////////////////////////////////////////////////
void keyboard(unsigned char key, int x, int y) {
	keys[key] = 1;
}
void keyboardUp(unsigned char key, int x, int y) {
	keys[key] = 0;
}

////////////////////////////////////////////////////
//タイマー関数
////////////////////////////////////////////////////
void timer(int value) {

	glutPostRedisplay();

	// 1000ミリ秒で 1 秒
	glutTimerFunc(1000 / 60, timer, 0);
}


////////////////////////////////////////////////////
//初期設定
////////////////////////////////////////////////////
void init(void) {
	glGenTextures(1, textures);
}


///////////////////////////////////////
//描画
////////////////////////////////////////
void display(void) {

	Manager::getInstance()->update();

	glFlush();
}


////////////////////////////////////////////////////
//メイン関数
////////////////////////////////////////////////////
int main(int argc, char *argv[]) {

	glutInit(&argc, argv);
	glutInitWindowSize(1000, 700);
	glutCreateWindow("game");

	glutDisplayFunc(display);
	glutTimerFunc(0, timer, 0);

	//マウス操作
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutPassiveMotionFunc(passiveMotion);

	//キーボード操作
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);

	glutIgnoreKeyRepeat(GL_TRUE);

	init();
	glutMainLoop();

}
