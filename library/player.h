#ifndef PLAYER_H
#define PLAYER_H

#include <list>
#include "character.h"

/////////////////////////////////////
//プレイヤーキャラクターclass
/////////////////////////////////////
class Player : public Character 
{
public:
	Player() :
		characterColor(0.2f, 0.3f, 0.7f),

		moveOnFlag(false),
		moveTargetPoint(0, 0, 0)
	{}
	~Player(){}

	void update();				//更新
	void draw();				//描画
	void collisionCursor();		//カーソル当たり判定
	void move();				//キャラクター移動
	void attackToCamp();		//敵陣地に攻撃

	glm::vec3 characterColor;		//キャラクターの色

	bool moveOnFlag;			//キャラクター移動指示をしているかいないか
	glm::vec3 moveTargetPoint;	//移動目標
};

extern std::list < Player > player;

#endif