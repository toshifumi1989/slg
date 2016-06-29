#include "result.h"
#include "../library/texture.h"
#include "../play/cursor.h"
#include "../library/player.h"
#include "../library/enemy.h"
#include "../library/camera.h"
#include "../library/wavFile.h"

Texture *victory;
Texture *victoryWord;
Texture *lose;
Texture *loseWord;

void Result::init()
{
	//‰¹Šy
	//bgm->playMusic(BGM::RESULT_BGM);

	//Ÿ—˜
	if (cursor->OnVictory == true)
	{
		glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_ID::VICTORY]);
		victory = new Texture();
		victory->read("victory.bmp");

		glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_ID::VICTORYWORD]);
		victoryWord = new Texture();
		victoryWord->read_alpha("victoryWord.bmp");
	}
	//”s–k
	else
	{
		glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_ID::LOSE]);
		lose = new Texture();
		lose->read("lose.bmp");

		glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_ID::LOSEWORD]);
		loseWord = new Texture();
		loseWord->read_alpha("loseWord.bmp");

	}


}

void Result::update()
{

}

void Result::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	camera->twoDimensionCamera();

	glEnable(GL_TEXTURE_2D);

	//”wŒi
	if (cursor->OnVictory == true)
	{
		glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_ID::VICTORY]);
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_ID::LOSE]);
	}

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

	
	//•¶Žš
	if (cursor->OnVictory == true)
	{
		glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_ID::VICTORYWORD]);
		glColor4f(0, 0, 1, 1);
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_ID::LOSEWORD]);
		glColor4f(1, 0, 0, 1);
	}
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glEnable(GL_BLEND);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


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
	
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}

void Result::pDelete()
{
	player.clear();
	enemy.clear();
	delete cursor;
	delete camera;
	delete victory;
	delete lose;
	delete loseWord;

	//bgm->stopMusic(BGM::RESULT_BGM);
	//bgm->deleteMusic();
}