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

	unsigned char targetType;	//0:Base 1:Camp 2:player の目標の種類分け
	unsigned char target;		//種類の中からの攻撃目標
	unsigned char pattern;		//0:攻撃を受けても進む 1:攻撃を受けたら立ち止まる

	void draw();

};

extern EnemyCamp *enemyBase;
extern std::list< EnemyCamp* > enemyCamp;

#endif