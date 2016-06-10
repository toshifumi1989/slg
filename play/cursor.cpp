#include <stdlib.h>
#include "../scene/battleSetUp.h"
#include "../glut.h"
#include "cursor.h"
#include "../library/field.h"
#include "../library/camera.h"
#include "..//library/field.h"

Cursor *cursor;
extern Camera *camera;
extern Field *field;
extern unsigned char keys[256];

///////////////////////
//準備画面
///////////////////////
void Cursor::setup()
{	
	//z座標の移動
	if (keys['w'] == 1)
	{
		pos.z += speed.x * camera->cameraHeight;
	}
	else if (keys['s'] == 1)
	{
		pos.z -= speed.z * camera->cameraHeight;
		
	}

	//x座標の移動
	if (keys['a'] == 1)
	{
		pos.x += speed.x * camera->cameraHeight;
	}
	else if (keys['d'] == 1)
	{
		pos.x -= speed.x * camera->cameraHeight;
	}

	if (pos.x > field->size - 2 || pos.x < 0 || pos.z < 0 || pos.z > field->size - 2 )
	{
		pos = lastPos;
	}

	field->intersect(pos);
	pos.y = field->charcterHeight + 5;

	lastPos = pos;

}


///////////////////////
//更新
///////////////////////
void Cursor::update()
{
	//z座標の移動
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

	//x座標の移動
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


	if (pos.x > field->size / 2.f + 100 || pos.x < field->size / 2.f - 100 || pos.z > field->size / 2.f + 100 || pos.z < field->size / 2.f - 100)
	{
		pos = lastPos;

	}

	field->intersect(pos);
	pos.y = field->charcterHeight + 5;


	lastPos = pos;
}


//////////////////////
//描画
//////////////////////
void Cursor::draw()
{
	glPushMatrix();
	{
		glEnable(GL_DEPTH_TEST);

		glColor3f(fabs(sin(colorCounter)), 1.f - 0.2f * fabs(sin(colorCounter)), fabs(sin(colorCounter)));
		glTranslatef(pos.x, pos.y, pos.z);

		glRotatef(front, 0, 1, 0);
		glRotatef(90, 1, 0, 0);	//カーソルを下向きにする為
		glScalef(2.f, 2.f, 2.f);
		glutSolidCone(1.0f, 1.0f, 3, 2);//引数：(半径, 高さ, Z軸まわりの分割数, Z軸に沿った分割数)


		if (collision == true)
		{
			glColor3f(1, 0, 0);
			glutWireCone(1.0f, 1.0f, 3, 1);
		}


		cursor->front++;

		glDisable(GL_DEPTH_TEST);

	}
	glPopMatrix();
}