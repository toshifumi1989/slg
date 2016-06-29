#ifndef TEXTURE_H
#define TEXTURE_H

#include <stdlib.h>
#include <vector>
#include "../glut.h"

enum TEXTURE_ID {
	FIELD,
	FIELD_SETUP,
	BATTLE_SETUP,
	SELECT_TYPE,
	SETUP_CHOICE,
	TITLE,
	TITLE_NAME,
	TITLE_CON,
	PLAY,
	RESULT,
	VICTORY,
	VICTORYWORD,
	LOSE,
	LOSEWORD,
	TEXTURE_MAX,
};


class Texture
{
public:
	Texture() {}
	~Texture(){}

	void read(const char* _texture);//�ǂݍ���
	void read_alpha(const char* _texture);//�ǂݍ��݁i�A���t�@

protected:
	//�F��RGB�̒l
	typedef struct { unsigned char b, g, r; }RGB;

	std::vector<unsigned char>alpha; //�A���t�@�l

	std::vector<float>vertex;		//�ʒu
	std::vector<unsigned int>index;	//�ԍ�
	std::vector<float>normal;		//�@��
	std::vector<float>tex;			//�e�N�X�`���ԍ�

};

extern GLuint textures[TEXTURE_ID::TEXTURE_MAX];

#endif