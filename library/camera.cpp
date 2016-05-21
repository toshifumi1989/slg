#include <stdlib.h>
#include "camera.h"
#include "../play/cursor.h"
#include "../glut.h"

Camera *camera;
extern Cursor *cursor;

void Camera::update() 
{
	const int cameraDistance = 20;
	pos = glm::vec3(cursor->pos.x - cameraDistance, cursor->pos.y + cameraHeight, cursor->pos.z - cameraDistance);

	target = cursor->pos;
}

void Camera::draw() 
{

	glMatrixMode(GL_PROJECTION);	// eΟ·sρΜέθ
	glLoadIdentity();				// Ο·sρΜϊ»

	//§e@ΜΜΟgluPerspactive(th, w/h, near, far);
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

}