#include <stdlib.h>
#include "enemyCamp.h"
#include "../glut.h"

std::list< EnemyCamp > enemyCamp;

void EnemyCamp::update()
{

	HP -= damage;

}

void EnemyCamp::draw()
{

	glPushMatrix();
	{
		glEnable(GL_DEPTH_TEST);
		glColor3f(0.7f, 0.3f, 0.2f);
		glTranslatef(pos.x, pos.y, pos.z);
		glScalef(size.x, size.y, size.z);
		glutSolidCube(1);
		glDisable(GL_DEPTH_TEST);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glEnable(GL_DEPTH_TEST);

		glm::mat4 view;
		glGetFloatv(GL_MODELVIEW_MATRIX, (float*)&view);

		glm::mat4 m = glm::inverse(view);
		m[3][0] = m[3][1] = m[3][2] = 0;

		glTranslatef(pos.x, pos.y + 4, pos.z);
		glScalef(2, 0.5f, 2);
		glMultMatrixf((float*)&m);

		glColor3f(.8f, .8f, 0);
		glBegin(GL_QUAD_STRIP);
		{
			glVertex3f(-1, 0, 0);
			glVertex3f(-1, 1, 0);
			glVertex3f(HP / 1000.f, 0, 0);
			glVertex3f(HP / 1000.f, 1, 0);
		}
		glEnd();

		glColor3f(1, 1, 1);

		glBegin(GL_QUAD_STRIP);
		{
			glVertex3f(-1, 0, 0);
			glVertex3f(-1, 1, 0);
			glVertex3f(1, 0, 0);
			glVertex3f(1, 1, 0);
		}
		glEnd();
		glDisable(GL_DEPTH_TEST);
	}
	glPopMatrix();
}