#include "play.h"
#include "../library/field.h"
#include "../library/camera.h"
#include "../library/player.h"
#include "../library/cursor.h"

void Play::init() {
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	field = new Field();
	field->read("field.bmp");
	field->setup();


	//プレイヤーキャラクター設定
	Player tentativePlayer;
	tentativePlayer.pos = glm::vec3(field->size / 2.f, 2, field->size / 2.f);
	player.push_back(tentativePlayer);

	//プレイヤーカーソル設定
	cursor = new Cursor();
	cursor->pos = glm::vec3(field->vtx / 2.f, 1, field->vtx / 2.f);


	//カメラ設定
	camera = new Camera();
	camera->pos = glm::vec3(cursor->pos.x + 5, cursor->pos.y + 10, cursor->pos.z + 5);
	camera->target = cursor->pos;

}

void Play::update() {
	
	//カーソル------------------------------
	cursor->update();

	//プレイヤーキャラクター----------------
	std::list < Player > ::iterator playerIter = player.begin();
	while (playerIter != player.end()) {
		playerIter->update();
		++playerIter;
	}

	//カメラ--------------------------------
	camera->update();

}

void Play::draw() {
	glColor3f(1, 1, 1);		//色の初期化
	glClearColor(0, 0.39f, 1, 0.5f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//フィールド-----------------------------
	field->draw();
	
	//カーソル-------------------------------
	cursor->draw();

	//プレイヤーキャラクター-----------------
	std::list < Player > ::iterator playerIter = player.begin();
	while ( playerIter != player.end() ) {
		playerIter->draw();
		++playerIter;
	}

	//カメラ--------------------------------
	camera->draw();
}