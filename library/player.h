#ifndef PLAYER_H
#define PLAYER_H

#include "gameObject.h"
#include <list>

/////////////////////////////////////
//�v���C���[�L�����N�^�[class
/////////////////////////////////////
class Player : public GameObject {
public:
	int HP = 100;		//�ϋv�l
	void update();		//�X�V
	void draw();		//�`��

};

extern std::list < Player > player;

#endif