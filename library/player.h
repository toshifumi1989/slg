#ifndef PLAYER_H
#define PLAYER_H

#include "gameObject.h"
#include <list>

/////////////////////////////////////
//プレイヤーキャラクターclass
/////////////////////////////////////
class Player : public GameObject {
public:
	int HP = 100;		//耐久値
	void update();		//更新
	void draw();		//描画

};

extern std::list < Player > player;

#endif