#include <stdlib.h>
#include "camera.h"
#include "cursor.h"
#include "../glut.h"

Camera *camera;
extern Cursor *cursor;

void Camera::update() {
	float cameraDistance = 5;
	float cameraHeight = 10;
	pos = glm::vec3(cursor->pos.x + cameraDistance, cursor->pos.y + cameraHeight, cursor->pos.z + cameraDistance);


}

void Camera::draw() {

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

void Camera::twoDimensionCamera() {

}