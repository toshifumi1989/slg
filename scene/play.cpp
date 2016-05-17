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


	//�v���C���[�L�����N�^�[�ݒ�
	Player tentativePlayer;
	tentativePlayer.pos = glm::vec3(field->size / 2.f, 2, field->size / 2.f);
	player.push_back(tentativePlayer);

	//�v���C���[�J�[�\���ݒ�
	cursor = new Cursor();
	cursor->pos = glm::vec3(field->vtx / 2.f, 1, field->vtx / 2.f);


	//�J�����ݒ�
	camera = new Camera();
	camera->pos = glm::vec3(cursor->pos.x + 5, cursor->pos.y + 10, cursor->pos.z + 5);
	camera->target = cursor->pos;

}

void Play::update() {
	
	//�J�[�\��------------------------------
	cursor->update();

	//�v���C���[�L�����N�^�[----------------
	std::list < Player > ::iterator playerIter = player.begin();
	while (playerIter != player.end()) {
		playerIter->update();
		++playerIter;
	}

	//�J����--------------------------------
	camera->update();

}

void Play::draw() {
	glColor3f(1, 1, 1);		//�F�̏�����
	glClearColor(0, 0.39f, 1, 0.5f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//�t�B�[���h-----------------------------
	field->draw();
	
	//�J�[�\��-------------------------------
	cursor->draw();

	//�v���C���[�L�����N�^�[-----------------
	std::list < Player > ::iterator playerIter = player.begin();
	while ( playerIter != player.end() ) {
		playerIter->draw();
		++playerIter;
	}

	//�J����--------------------------------
	camera->draw();
}