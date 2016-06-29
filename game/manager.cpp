#include "manager.h"

#include "../scene/tittle.h"
#include "../scene/battleSetUp.h"
#include "../scene/play.h"
#include "../scene/result.h"

#include "../play/cursor.h"
#include "../library/player.h"
#include "../play/playerCamp.h"
#include "../library/enemy.h"
#include "../play/enemyCamp.h"

Manager* Manager::instance = nullptr;
extern unsigned char keys[256];

//////////////////////////////////////
//インスタンス
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
//マネージャの更新
////////////////////////////////////////////
void Manager::update()
{
	_scene.run(this, 1.0f / 60.0f);
}


///////////////////////////////////////////
//タイトルシーン
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

	if (keys[' '] == 1)
	{
		scene->pDelete();
		delete scene;
		_scene.change(&Manager::sceneSetUp);
	}
}

//////////////////////////////////////////////
//戦闘準備シーン
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
		scene->pDelete();
		delete scene;
		_scene.change(&Manager::scenePlay);
	}
}

//////////////////////////////////////////////
//プレイシーン
//////////////////////////////////////////////
void Manager::scenePlay(float delta) 
{
	if (_scene.getTime() == 0.0f)
	{
		scene = new Play();
		scene->init();
	}

	scene->update();
	scene->draw();


	if (playerBase->HP <= 0 ||		//本陣陥落
		player.empty() == true)	//プレイヤーキャラクター全滅
	{
		cursor->OnVictory = false;
		scene->pDelete();
		delete scene;
		_scene.change(&Manager::sceneResult);
	}
	else if(
		enemyBase->HP <= 0 ||		//敵本陣陥落
		enemy.empty() == true)		//敵キャラクター全滅
	{
		cursor->OnVictory = true;
		scene->pDelete();
		delete scene;
		_scene.change(&Manager::sceneResult);
	}

}

/////////////////////////////////////////////
//リザルトシーン
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


	if (keys[0x0d] == 1)
	{
		scene->pDelete();
		delete scene;
		_scene.change(&Manager::sceneTitle);
	}

}

