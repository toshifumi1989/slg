#include <stdlib.h>
#include "enemyCamp.h"
#include "../glut.h"

std::list< EnemyCamp > enemyCamp;
EnemyCamp *enemyBase;

void EnemyCamp::draw()
{
	glEnable(GL_DEPTH_TEST);

	glPushMatrix();
	{

		glColor3f(0.4f, 0.2f, 0.1f);
		glTranslatef(pos.x, pos.y, pos.z);
		glScalef(size.x, size.y, size.z);
		glutSolidCube(1);


		//HP
		glm::mat4 view;
		glGetFloatv(GL_MODELVIEW_MATRIX, (float*)&view);

		glm::mat4 m = glm::inverse(view);
		m[3][0] = m[3][1] = m[3][2] = 0;

		glMultMatrixf((float*)&m);
		glTranslatef(-1.5f, 3, 0);
		glColor3f(0.8f, 0.8f, 0);
		glScalef(3.f, 2.f, 0);
		glBegin(GL_QUAD_STRIP);
		{

			glVertex3f(HP / 1000.f, 0.5f, 0);
			glVertex3f(0, 0.5f, 0);
			glVertex3f(HP / 1000.f, 0, 0);
			glVertex3f(0, 0, 0);
		}
		glEnd();
	}
	glPopMatrix();

	glDisable(GL_DEPTH_TEST);

}
