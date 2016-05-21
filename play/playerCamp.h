#ifndef PLAYERCAMP_H
#define PLAYRECAMP_H

#include <list>
#include "camp.h"

class PlayerCamp : public Camp 
{
public:
	void update();
	void draw();

};

extern std::list< PlayerCamp > playerCamp;

#endif