#ifndef BATTLESETUP_H
#define BATTLESETUP_H

#include "scene.h"

enum SetupScene{
	CursorMove,
	TypeChoice
};


class BattleSetUp : public Scene
{
public:
	BattleSetUp() :
		playerCounter(0),
		maxPlayerCounter(3),
		campCounter(0),
		maxCampCounter(2)
	{}
	~BattleSetUp() {}

	void init();
	void update();
	void cursorMove();				//�J�[�\���ړ��V�[��
	void typeChoice();				//����I���V�[��
	void draw();
	void playerSelectLine();		//�g���ɃL�����N�^�[��u����

	unsigned char playerCounter;	//�v���C���[�L�����̐�
	unsigned char maxPlayerCounter;	//�L�����̍ő吔

	unsigned char campCounter;		//���w�̐�
	unsigned char maxCampCounter;	//���w�̍ő吔

	unsigned char setUpScene = SetupScene::CursorMove;
};

#endif