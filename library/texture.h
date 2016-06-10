#ifndef TEXTURE_H
#define TEXTURE_H

#include <stdlib.h>
#include <vector>
#include "../glut.h"

enum TEXTURE_ID {
	FIELD,
	FIELD_SETUP,


	TEXTURE_MAX,
};


class Texture
{
public:
	Texture() {}
	~Texture(){}

	//�F��RGB�̒l
	typedef struct { unsigned char b, g, r; }RGB;

	std::vector<unsigned char>alpha; //�A���t�@�l

	std::vector<float>vertex;		//�ʒu
	std::vector<float>normal;		//�@��
	std::vector<unsigned int>index;	//�ԍ�
	std::vector<float>tex;			//�e�N�X�`���ԍ�

	void read(const char* _texture);//�ǂݍ���
	void read_alpha(const char* _texture);//�ǂݍ��݁i�A���t�@

};

extern GLuint textures[TEXTURE_ID::TEXTURE_MAX];

#endif