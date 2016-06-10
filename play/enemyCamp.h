#ifndef ENEMYCAMP_H
#define ENEMYCAMP_H

#include <list>
#include "camp.h"

class EnemyCamp :public Camp 
{

public:
	EnemyCamp():
		targetType(0),
		target(0),
		pattern(0)
	{}
	~EnemyCamp(){}

	unsigned char targetType;	//0:Base 1:Camp 2:player ‚Ì–Ú•W‚Ìí—Ş•ª‚¯
	unsigned char target;		//í—Ş‚Ì’†‚©‚ç‚ÌUŒ‚–Ú•W
	unsigned char pattern;		//0:UŒ‚‚ğó‚¯‚Ä‚ài‚Ş 1:UŒ‚‚ğó‚¯‚½‚ç—§‚¿~‚Ü‚é

	void draw();

};

extern EnemyCamp *enemyBase;
extern std::list< EnemyCamp* > enemyCamp;

#endif