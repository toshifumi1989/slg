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

	unsigned char targetType;	//0:Base 1:Camp 2:player �̖ڕW�̎�ޕ���
	unsigned char target;		//��ނ̒�����̍U���ڕW
	unsigned char pattern;		//0:�U�����󂯂Ă��i�� 1:�U�����󂯂��痧���~�܂�

	void draw();

};

extern EnemyCamp *enemyBase;
extern std::list< EnemyCamp* > enemyCamp;

#endif