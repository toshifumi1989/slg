#include "manager.h"

#include "../scene/tittle.h"
#include "../scene/battleSetUp.h"
#include "../scene/play.h"
#include "../scene/result.h"


Manager* Manager::instance = nullptr;
extern unsigned char keys[256];


//////////////////////////////////////
//�C���X�^���X
//////////////////////////////////////
Manager* Manager::getInstance() 
{
	if (nullptr == instance)
	{
		instance = new Manager();

	}
	return instance;
}

////////////////////////////////////////////
//�}�l�[�W���̍X�V
////////////////////////////////////////////
void Manager::update()
{
	_scene.run(this, 1.0f / 60.0f);
}


///////////////////////////////////////////
//�^�C�g���V�[��
///////////////////////////////////////////
void Manager::sceneTitle(float delta)
{
	if (_scene.getTime() == 0.0f)
	{		
		scene = new Tittle();
		scene->init();
	}

	scene->update();
	scene->draw();
}

//////////////////////////////////////////////
//�퓬�����V�[��
//////////////////////////////////////////////
void Manager::sceneSetUp(float delta)
{
	if (_scene.getTime() == 0.0f)
	{
		scene = new BattleSetUp();
		scene->init();

	}

	scene->update();
	scene->draw();


	if (keys[0x0d] == 1)
	{
		delete scene;
		_scene.change(&Manager::scenePlay);
	}
}

//////////////////////////////////////////////
//�v���C�V�[��
//////////////////////////////////////////////
void Manager::scenePlay(float delta) 
{
	if (_scene.getTime() == 0.0f)
	{
		scene = new Play();
	}

	scene->update();
	scene->draw();
}

/////////////////////////////////////////////
//���U���g�V�[��
/////////////////////////////////////////////
void Manager::sceneResult(float delta)
{
	if (_scene.getTime() == 0.0f)
	{

		scene = new Result();
		scene->init();
	}

	scene->update();
	scene->draw();
}

