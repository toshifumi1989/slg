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
	void cursorMove();				//カーソル移動シーン
	void typeChoice();				//兵種選択シーン
	void draw();
	void playerSelectLine();		//枠内にキャラクターを置ける

	unsigned char playerCounter;	//プレイヤーキャラの数
	unsigned char maxPlayerCounter;	//キャラの最大数

	unsigned char campCounter;		//自陣の数
	unsigned char maxCampCounter;	//自陣の最大数

	unsigned char setUpScene = SetupScene::CursorMove;
};

#endif