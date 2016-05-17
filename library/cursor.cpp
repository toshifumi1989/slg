#include <stdlib.h>
#include "cursor.h"
#include "../glut.h"

Cursor *cursor;

///////////////////////
//更新
///////////////////////
void Cursor::update() {

}


//////////////////////
//描画
//////////////////////
void Cursor::draw() {
	glPushMatrix();
	{
		glEnable(GL_DEPTH_TEST);

		glColor3f(0, 0.8f, 0);
		glTranslatef(cursor->pos.x, cursor->pos.y, cursor->pos.z);

		glRotatef(cursor->front, 0, 1, 0);
		glRotatef(90, 1, 0, 0);	//カーソルを下向きにする為
		glutSolidCone(1.0f, 1.0f, 3, 2);//引数：(半径, 高さ, Z軸まわりの分割数, Z軸に沿った分割数)

		cursor->front++;

		glDisable(GL_DEPTH_TEST);

	}
	glPopMatrix();
}