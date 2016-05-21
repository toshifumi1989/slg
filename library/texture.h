#ifndef TEXTURE_H
#define TEXTURE_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <vector>
#include "../glut.h"

class Texture
{
public:
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

extern GLuint textures[1];

#endif