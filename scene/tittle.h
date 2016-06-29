#ifndef TITTLE_H
#define TITTLE_H

#include "scene.h"

class Tittle :public Scene
{
public:
	Tittle(){}
	~Tittle(){}

	void init();
	void update();
	void draw();
	void pDelete();
};


#endif