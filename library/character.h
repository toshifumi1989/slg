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

	unsigned char type;				//���̎��(0:���� 1:���� 2:�R�� 3:�|��
	int HP;				//�ϋv�l
	unsigned int Attack;			//�U����
	unsigned int Defense;			//�h���
	float  attackRange;				//�U���͈�
	float speedCoefficient;			//�ړ����x�̌W��
	unsigned int damage;			//��_���[�W
	unsigned int food;				//����

	bool selectedFlag;				//�I������Ă���
	bool OnAttack;					//�U����

	float targetFront;				//�ڕW�ƂȂ�front�̒l

	glm::vec3 moveTargetPoint;		//�ړ��ڕW
};

#endif