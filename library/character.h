#ifndef CHARACTER_H
#define CHARACTER_H

#include "gameObject.h"

///////////////////////////////
//�L�����N�^�[�N���X
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
	unsigned int HP;				//�ϋv�l
	unsigned int Attack;			//�U����
	unsigned int Defense;			//�h���
	int damage;						//��_���[�W
	bool selectedFlag;				//�I������Ă���
};

#endif