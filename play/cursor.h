#ifndef CURSOR_H
#define CURSOR_H

#include "../library/gameObject.h"

//////////////////////////////
//プレイヤーカーソルクラス
//////////////////////////////
class Cursor :public GameObject
{
public:
	Cursor():
		colorCounter(0),
		collision(false)
	{}
	~Cursor(){}

	void update();			//更新
	void draw();			//描画
	float colorCounter;		//当たり判定中の色変化のための変数
	bool collision;			//当たり判定
};

extern Cursor *cursor;

#endif