#ifndef ENEMY_H
#define ENEMY_H

#include <list>
#include "character.h"

///////////////////////////////////
//�G�l�~�[�L�����N�^�[�N���X
///////////////////////////////////
class Enemy : public Character
{
public:
	void update();		//�X�V
	void draw();		//�`��
	void AI();			//AI
};

extern std::list< Enemy* > enemy;

#endif