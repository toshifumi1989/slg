#ifndef CURSOR_H
#define CURSOR_H

#include "gameObject.h"

//////////////////////////////
//�v���C���[�J�[�\���N���X
//////////////////////////////
class Cursor :public GameObject{
public:
	Cursor(){}

	~Cursor(){}

	void update();
	void draw();
	

};

extern Cursor *cursor;

#endif