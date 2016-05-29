#ifndef PLAYER_H
#define PLAYER_H

#include <list>
#include "character.h"
#include "field.h"

/////////////////////////////////////
//�v���C���[�L�����N�^�[class
/////////////////////////////////////
class Player : public Character 
{
public:
	Player() :
		characterColor(0.2f, 0.4f, 0.7f),
		moveOnFlag(false)
	{}
	~Player(){}

	void update();				//�X�V
	void draw();				//�`��
	void collisionCursor();		//�J�[�\�������蔻��
	void move();				//�L�����N�^�[�ړ�
	void attackToCamp();		//�G�w�n�ɍU��

	glm::vec3 characterColor;		//�L�����N�^�[�̐F

	bool moveOnFlag;			//�L�����N�^�[�ړ��w�������Ă��邩���Ȃ���
	
};

extern std::list < Player > player;

#endif