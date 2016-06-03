#ifndef ENEMYCAMP_H
#define ENEMYCAMP_H

#include <list>
#include "camp.h"

class EnemyCamp :public Camp 
{

public:

	void draw();

};

extern EnemyCamp *enemyBase;
extern std::list< EnemyCamp* > enemyCamp;

#endif