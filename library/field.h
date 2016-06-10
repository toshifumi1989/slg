#ifndef FIELD_H
#define FIELD_H

#include "texture.h"
#include "../glm/glm.hpp"

class Field : public Texture 
{
public:
	Field(){}
	~Field(){}

	int vtx = 256;						//�t�B�[���h�̃s�N�Z����
	int size = vtx ;					//�t�B�[���h�̍L��
	float charcterHeight = 0;			//�����蔻��̐��l�̑ҋ@�ꏊ

	void setup(const char* _texture);	//�`�揀��
	void draw();						//�`��
	void intersect(glm::vec3 _pos);		//�����蔻��

};

extern Field *field;

#endif