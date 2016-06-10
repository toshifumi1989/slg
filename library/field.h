#ifndef FIELD_H
#define FIELD_H

#include "texture.h"
#include "../glm/glm.hpp"

class Field : public Texture 
{
public:
	Field(){}
	~Field(){}

	int vtx = 256;						//フィールドのピクセル数
	int size = vtx ;					//フィールドの広さ
	float charcterHeight = 0;			//当たり判定の数値の待機場所

	void setup(const char* _texture);	//描画準備
	void draw();						//描画
	void intersect(glm::vec3 _pos);		//当たり判定

};

extern Field *field;

#endif