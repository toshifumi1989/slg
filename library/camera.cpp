#include <stdlib.h>
#include "camera.h"
#include "../play/cursor.h"
#include "../glut.h"

Camera *camera;
extern Cursor *cursor;

void Camera::setUp()
{
	const float Height = 100;
	pos = glm::vec3(cursor->pos.x, Height, cursor->pos.z-10);

	target = cursor->pos;

}

void Camera::update()
{
	const int cameraDistance = 20;
	pos = glm::vec3(cursor->pos.x - cameraDistance, cursor->pos.y + cameraHeight, cursor->pos.z - cameraDistance);

	target = cursor->pos;

	if (specialKey == GLUT_KEY_UP)
	{
		cameraHeight += 0.5f;
	}
	else if (specialKey == GLUT_KEY_DOWN)
	{
		cameraHeight -= 0.5f;
	}
}

void Camera::draw()
{

	glMatrixMode(GL_PROJECTION);	// “Š‰e•ÏŠ·s—ñ‚Ìİ’è
	glLoadIdentity();				// •ÏŠ·s—ñ‚Ì‰Šú‰»

	//“§‹“Š‰e–@‚Ì‹‘ÌÏgluPerspactive(th, w/h, near, far);
	gluPerspective(angle, aspect, nearDraw, farDraw);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(
		pos.x, pos.y, pos.z,
		target.x, target.y, target.z,
		up.x, up.y, up.z);

}

void Camera::twoDimensionCamera()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(
		left, right,//GLdouble left,  right,
		bottom, top,//GLdouble bottom,  top, 
		10, -10);//GLdouble zNear,  zFar

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3f(1, 1, 1);
	

}