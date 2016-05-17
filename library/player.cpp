#include <stdlib.h>
#include "player.h"
#include "../glut.h"

std::list < Player > player;

void Player::update() {

}

void Player::draw() {
	glPushMatrix();
	{
		glTranslatef(pos.x, pos.y, pos.z);
		glutSolidSphere(2, 50, 50);

	}
	glPopMatrix();

}