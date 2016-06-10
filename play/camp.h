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

	unsigned char ID;			//�ԍ�
	int HP;						//�ϋv�l
	unsigned int Defense;		//�h���
	unsigned int damage;		//�_���[�W��
	glm::vec3 size;				//�w�n�̑傫��

	bool OnDefense;				//�U�����󂯂Ă���
};

#endif