#include "tittle.h"
#include "../library/camera.h"
#include "../library/texture.h"
#include "../library/wavFile.h"

Texture *titleBackGround;
Texture *titleName;
Texture *titleCon;

void Tittle::init()
{
	//カメラ生成
	camera = new Camera();

	//テクスチャ設定
	titleBackGround = new Texture();
	titleName = new Texture();
	titleCon = new Texture();

	glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_ID::TITLE]);
	titleBackGround->read("title.bmp");

	glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_ID::TITLE_NAME]);
	titleName->read_alpha("titleName.bmp");

	glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_ID::TITLE_CON]);
	titleCon->read_alpha("titleCon.bmp");

	//ＢＧＭ
	bgm->playMusic(BGM::TITLE_BGM);
}

void Tittle::update()
{


}

void Tittle::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	camera->twoDimensionCamera();

	//タイトル画面背景
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_ID::TITLE]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


	glBegin(GL_QUADS);
	{
		glTexCoord2d(0, 1);
		glVertex3d(camera->left, camera->bottom, 0);
		glTexCoord2d(1, 1);
		glVertex3d(camera->right, camera->bottom, 0);
		glTexCoord2d(1, 0);
		glVertex3d(camera->right, camera->top, 0);
		glTexCoord2d(0, 0);
		glVertex3d(camera->left, camera->top, 0);
	}
	glEnd();

	
	//タイトル文字
	glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_ID::TITLE_NAME]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glEnable(GL_BLEND);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	glColor4f(0, 1, 0.1f, 1);
	glBegin(GL_QUADS);
	{
		glTexCoord2d(0, 1);
		glVertex3d(camera->left, camera->bottom, 0);
		glTexCoord2d(1, 1);
		glVertex3d(camera->right, camera->bottom, 0);
		glTexCoord2d(1, 0);
		glVertex3d(camera->right, camera->top, 0);
		glTexCoord2d(0, 0);
		glVertex3d(camera->left, camera->top, 0);
	}
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_ID::TITLE_CON]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glColor4f(1, 1, 1, 1);
	glBegin(GL_QUADS);
	{
		glTexCoord2d(0, 1);
		glVertex3d(camera->left, camera->bottom, 0);
		glTexCoord2d(1, 1);
		glVertex3d(camera->right, camera->bottom, 0);
		glTexCoord2d(1, 0);
		glVertex3d(camera->right, camera->top, 0);
		glTexCoord2d(0, 0);
		glVertex3d(camera->left, camera->top, 0);
	}
	glEnd();	

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);

}

void Tittle::pDelete()
{

	//画像削除
	delete titleBackGround;
	delete titleName;
	delete titleCon;

	//音楽処理
	bgm->stopMusic(BGM::TITLE_BGM);
}