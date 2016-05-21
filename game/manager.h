#ifndef MANAGER_H
#define MANAGER_H

#include "sequence.h"
#include "../scene/scene.h"

class Manager 
{
public:

	~Manager() {}

	void update();//�X�V

	static Manager* getInstance();

	void sceneTitle(float delta);//�V�[���^�C�g��
	void scenePlay(float delta);//�V�[���v���C
	void sceneResult(float delta);//�V�[�����U���g

	Sequence<Manager> _scene;

	Scene *scene;

private:
	Manager() 
	{
		_scene.change(&Manager::scenePlay);
	}

	static Manager* instance;
};

#endif