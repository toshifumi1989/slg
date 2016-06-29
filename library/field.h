#ifndef FIELD_H
#define FIELD_H

#include "texture.h"
#include "../glm/glm.hpp"

class Field : public Texture 
{
public:
	Field():
		vtx(256),
		size(vtx),
		charcterHeight(0)
	{}
	~Field(){}

	int vtx;				//�t�B�[���h�̃s�N�Z����
	int size;				//�t�B�[���h�̍L��
	float charcterHeight;	//�����蔻��̐��l�̑ҋ@�ꏊ

	void setup(const char* _texture);	//�`�揀��
	void draw();						//�`��
	void intersect(glm::vec3 _pos);		//�����蔻��

};

extern Field *field;

#endif