#ifndef CAMP_H
#define CAMP_H

#include "../library/gameObject.h"

class Camp :public GameObject
{
public:
	Camp() :
		ID(0),
		HP(1000),
		Defense(10),
		damage(0),
		size(5,2,5),

		OnDefense(false)
	{}
	virtual ~Camp() {}

	unsigned char ID;			//番号
	int HP;						//耐久値
	unsigned int Defense;		//防御力
	unsigned int damage;		//ダメージ量
	glm::vec3 size;				//陣地の大きさ

	bool OnDefense;				//攻撃を受けている
};

#endif