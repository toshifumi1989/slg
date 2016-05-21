#include <stdlib.h>
#include "playerCamp.h"
#include "../glut.h"


std::list< PlayerCamp > playerCamp;

void PlayerCamp::update()
{

}

void PlayerCamp::draw()
{

	glPushMatrix();
	{
		glEnable(GL_DEPTH_TEST);
		glColor3f(0.2f, 0.3f, 0.7f);
		glTranslatef(pos.x, pos.y, pos.z);
		glScalef(size.x, size.y, size.z);
		glutSolidCube(1);
		glDisable(GL_DEPTH_TEST);
	}
	glPopMatrix();

}