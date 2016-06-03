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
		Attack(10),
		Defense(10),
		attackRange(10),
		speedCoefficient(0.1f),
		damage(0),
		food(10000),

		selectedFlag(false),
		OnAttack(false),

		targetFront(0),
		moveTargetPoint(0,0,0)
	{}

	virtual ~Character(){}

	unsigned char type;				//兵の種類(0:混乱 1:歩兵 2:騎兵 3:弓兵
	int HP;				//耐久値
	unsigned int Attack;			//攻撃力
	unsigned int Defense;			//防御力
	float  attackRange;				//攻撃範囲
	float speedCoefficient;			//移動速度の係数
	unsigned int damage;			//被ダメージ
	unsigned int food;				//兵糧

	bool selectedFlag;				//選択されている
	bool OnAttack;					//攻撃中

	float targetFront;				//目標となるfrontの値

	glm::vec3 moveTargetPoint;		//移動目標
};

#endif