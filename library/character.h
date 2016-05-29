#ifndef CHARACTER_H
#define CHARACTER_H

#include "gameObject.h"

///////////////////////////////
//キャラクタークラス
///////////////////////////////
class Character : public GameObject 
{

public:

	Character() :
		HP(1000),
		Attack(20),
		Defense(10), 
		damage(0),
		selectedFlag(false),
		OnAttack(false),

		targetFront(0),
		moveTargetPoint(0,0,0)
	{}

	~Character(){}

	unsigned int HP;				//耐久値
	unsigned int Attack;			//攻撃力
	unsigned int Defense;			//防御力
	int damage;						//被ダメージ
	bool selectedFlag;				//選択されている
	bool OnAttack;					//攻撃中

	float targetFront;				//目標となるfrontの値

	glm::vec3 moveTargetPoint;		//移動目標
};

#endif