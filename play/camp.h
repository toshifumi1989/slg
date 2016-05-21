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

	int HP;						//�ϋv�l
	unsigned int Defense;	//�h���
	unsigned int damage;		//�_���[�W��
	glm::vec3 size;				//�w�n�̑傫��
};

#endif