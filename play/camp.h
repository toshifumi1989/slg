#ifndef CAMP_H
#define CAMP_H

#include "../library/gameObject.h"

class Camp :public GameObject
{
public:

	Camp() :
		HP(1000),
		Defense(10),
		damage(0),
		size(5,2,5)
	{}
	~Camp(){}

	int HP;						//耐久値
	unsigned int Defense;	//防御力
	unsigned int damage;		//ダメージ量
	glm::vec3 size;				//陣地の大きさ
};

#endif