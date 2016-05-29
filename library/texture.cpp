#define _CRT_SECURE_NO_WARNINGS

#include "texture.h"
#include <assert.h>
#include <Windows.h>

GLuint textures[TEXTURE_ID::TEXTURE_MAX];

///////////////////////////////////////
//�e�N�X�`���ǂݍ���
///////////////////////////////////////
void Texture::read(const char* _texture)
{

	FILE *pFile = fopen(_texture, "rb");
	assert(pFile != NULL);

	BITMAPFILEHEADER bf;
	BITMAPINFOHEADER bi;

	RGB *pixels;

	fread(&bf, sizeof(BITMAPFILEHEADER), 1, pFile);
	fread(&bi, sizeof(BITMAPINFOHEADER), 1, pFile);

	int size = bi.biWidth *bi.biHeight * sizeof(RGB);
	pixels = (RGB*)malloc(size);
	fread(pixels, size, 1, pFile);

	fclose(pFile);

	//RGB��R��B�̓���ւ�
	for (int i = 0; i < bi.biWidth * bi.biHeight; i++) 
	{
		char sub = pixels[i].b;
		pixels[i].b = pixels[i].r;
		pixels[i].r = sub;
	}

	//�摜�̏㉺���]
	for (int p = 0; p < bi.biHeight / 2; p++)
	{
		for (int q = 0; q < bi.biWidth; q++) 
		{
			RGB sub = pixels[bi.biWidth * p + q];
			pixels[bi.biWidth * p + q] = pixels[bi.biWidth *(bi.biHeight - 1 - p) + q];
			pixels[bi.biWidth *(bi.biHeight - 1 - p) + q] = sub;
		}
	}

	glTexImage2D(
		GL_TEXTURE_2D,		//GLenum target,
		0,					//GLint level,
		GL_RGB,				//GLint internalformat, 
		bi.biWidth, bi.biHeight,	//GLsizei width, GLsizei height, 
		0,					//GLint border, 
		GL_RGB,				//GLenum format, 
		GL_UNSIGNED_BYTE,	//GLenum type, 
		pixels);			//const GLvoid *pixels

	free(pixels);

}

///////////////////////////////////////////
//�e�N�X�`���ǂݍ��݁i�A���t�@
//////////////////////////////////////////
void Texture::read_alpha(const char* _texture)
{
	BITMAPFILEHEADER bf;
	BITMAPINFOHEADER bi;

	RGB *pixels;

	FILE *pFile = fopen(_texture, "rb");
	assert(pFile != NULL);

	fread(&bf, sizeof(BITMAPFILEHEADER), 1, pFile);
	fread(&bi, sizeof(BITMAPINFOHEADER), 1, pFile);

	int size = bi.biWidth *bi.biHeight * sizeof(RGB);
	pixels = (RGB*)malloc(size);
	fread(pixels, size, 1, pFile);

	fclose(pFile);

	//�摜�̏㉺���]
	for (int p = 0; p < bi.biHeight / 2; p++)
	{
		for (int q = 0; q < bi.biWidth; q++)
		{
			RGB sub = pixels[bi.biWidth * p + q];
			pixels[bi.biWidth * p + q] = pixels[bi.biWidth *(bi.biHeight - 1 - p) + q];
			pixels[bi.biWidth *(bi.biHeight - 1 - p) + q] = sub;
		}
	}


	//RGB���A���t�@�ɐ؂�ւ�
	for (int i = 0; i < bi.biWidth * bi.biHeight; i++)
	{
		int sub = (pixels[i].r + pixels[i].g + pixels[i].b) / 3;
		alpha.push_back(sub);
	}

	glTexImage2D(
		GL_TEXTURE_2D,		//GLenum target,
		0,					//GLint level,
		GL_ALPHA,				//GLint internalformat, 
		bi.biWidth, bi.biHeight,	//GLsizei width, GLsizei height, 
		0,					//GLint border, 
		GL_ALPHA,				//GLenum format, 
		GL_UNSIGNED_BYTE,	//GLenum type, 
		alpha.data());			//const GLvoid *pixels

	free(pixels);
}