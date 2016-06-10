#ifndef PLAYERCAMP_H
#define PLAYRECAMP_H

#include <list>
#include "camp.h"

class PlayerCamp : public Camp 
{
public:
	PlayerCamp(){}
	~PlayerCamp(){}
	
	void draw();

};

extern PlayerCamp *playerBase;
extern std::list< PlayerCamp* > playerCamp;

#endif