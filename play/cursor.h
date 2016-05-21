#ifndef CURSOR_H
#define CURSOR_H

#include "../library/gameObject.h"

//////////////////////////////
//�v���C���[�J�[�\���N���X
//////////////////////////////
class Cursor :public GameObject
{
public:
	Cursor():
		colorCounter(0),
		collision(false)
	{}
	~Cursor(){}

	void update();			//�X�V
	void draw();			//�`��
	float colorCounter;		//�����蔻�蒆�̐F�ω��̂��߂̕ϐ�
	bool collision;			//�����蔻��
};

extern Cursor *cursor;

#endif