#ifndef PLAYER_H
#define PLAYER_H

#include <list>
#include "character.h"
#include "field.h"

/////////////////////////////////////
//プレイヤーキャラクターclass
/////////////////////////////////////
class Player : public Character 
{
public:
	Player() :
		characterColor(0.2f, 0.4f, 0.7f),
		moveOnFlag(false)
	{}
	~Player(){}

	void update();				//更新
	void draw();				//描画
	void collisionCursor();		//カーソル当たり判定
	void move();				//キャラクター移動
	void attackToCamp();		//敵陣地に攻撃

	glm::vec3 characterColor;		//キャラクターの色

	bool moveOnFlag;			//キャラクター移動指示をしているかいないか
	
};

extern std::list < Player > player;

#endif