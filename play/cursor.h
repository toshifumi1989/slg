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
		collision(false),
		OnVictory(false),
		playerNum(0),
		pCampNum(0)
	{}
	~Cursor(){}

	void setup();			//�������

	void update();			//�X�V
	void draw();			//�`��

	float colorCounter;		//�����蔻�蒆�̐F�ω��̂��߂̕ϐ�
	bool collision;			//�����蔻��

	bool OnVictory;			//���s

	unsigned char playerNum;//playerID
	unsigned char pCampNum;	//playerCumpID
};

extern Cursor *cursor;

#endif