#ifndef CURSOR_H
#define CURSOR_H

#include "gameObject.h"

//////////////////////////////
//プレイヤーカーソルクラス
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