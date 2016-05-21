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
		HP(100),
		Attack(20),
		Defense(10), 
		damage(0),
		selectedFlag(false)
	{}

	~Character(){}

	virtual void collisionCursor() = 0;
	unsigned int HP;				//耐久値
	unsigned int Attack;			//攻撃力
	unsigned int Defense;			//防御力
	int damage;						//被ダメージ
	bool selectedFlag;				//選択されている
};

#endif