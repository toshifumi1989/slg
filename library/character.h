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

	unsigned int HP;				//�ϋv�l
	unsigned int Attack;			//�U����
	unsigned int Defense;			//�h���
	int damage;						//��_���[�W
	bool selectedFlag;				//�I������Ă���
	bool OnAttack;					//�U����

	float targetFront;				//�ڕW�ƂȂ�front�̒l

	glm::vec3 moveTargetPoint;		//�ړ��ڕW
};

#endif