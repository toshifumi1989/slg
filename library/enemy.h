#ifndef ENEMY_H
#define ENEMY_H

#include <list>
#include "character.h"

///////////////////////////////////
//エネミーキャラクタークラス
///////////////////////////////////
class Enemy : public Character
{
public:
	void update();		//更新
	void draw();		//描画
	void AI();			//AI
};

extern std::list< Enemy* > enemy;

#endif