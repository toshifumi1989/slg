#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "../glm/glm.hpp"

////////////////////////////////////
//�Q�[���I�u�W�F�N�g�N���X
////////////////////////////////////
class GameObject 
{
public:
	GameObject() :
		pos(0, 0, 0),
		lastPos(0, 0, 0),
		speed(0, 0, 0),
		front(0)
	{}

	glm::vec3 pos;		//���ݒn
	glm::vec3 lastPos;	//�P�t���[���O�̈ʒu
	glm::vec3 speed;	//�ړ�����
	float front;		//�I�u�W�F�N�g�̌���

	virtual void update() = 0;	//�X�V
	virtual void draw() = 0;	//�`��


};

#endif