#include <stdlib.h>
#include "../glut.h"
#include "player.h"
#include "../play/cursor.h"
#include "../play/enemyCamp.h"


std::list< Player > player;
extern Cursor *cursor;
extern std::list< EnemyCamp > enemyCamp;
extern unsigned char keys[];

//////////////////////////////////
//更新
//////////////////////////////////
void Player::update()
{
	if (moveOnFlag == true) {
		pos += speed;
	}

	lastPos = pos;
}

///////////////////////////////////
//描画
///////////////////////////////////
void Player::draw()
{
	//プレイヤーキャラクター
	glPushMatrix();
	{
		glEnable(GL_DEPTH_TEST);
		glColor3f(characterColor.r, characterColor.g, characterColor.b);
		glTranslatef(pos.x, pos.y, pos.z);
		glRotatef(front, 0, 1, 0);
		{
			glScalef(5.f, 1.f, 3.f);
			glutSolidCube(1);
		}
		glDisable(GL_DEPTH_TEST);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glEnable(GL_DEPTH_TEST);
		glColor3f(characterColor.r, characterColor.g, characterColor.b);
		glTranslatef(pos.x, pos.y, pos.z + 2);
		glRotatef(front, 0, 1, 0);
		{
			glScalef(2.f, 1.f, 3.f);
			glutSolidCube(1);
		}
		glDisable(GL_DEPTH_TEST);
	}
	glPopMatrix();


	//目標地点
	if (moveOnFlag == true)
	{
		glPushMatrix();
		{
			glEnable(GL_DEPTH_TEST);
			glColor3f(characterColor.r, characterColor.g, characterColor.b);
			glTranslatef(moveTargetPoint.x, moveTargetPoint.y, moveTargetPoint.z);
			glRotatef(90, 1, 0, 0);	//向きを変えるため
			glScalef(1.f, 1.f, 1.f);
			glutSolidTorus(1, 2, 10, 10);
			glDisable(GL_DEPTH_TEST);
		}
		glPopMatrix();

	}

}

/////////////////////////////////////////
//カーソルとの当たり判定
/////////////////////////////////////////
void Player::collisionCursor()
{
	//カーソルとプレイヤーキャラクタとの距離
	const float cursorToPlayer =
		(pos.x - cursor->pos.x) * (pos.x - cursor->pos.x)
		+ (pos.y - cursor->pos.y) * (pos.y - cursor->pos.y)
		+ (pos.z - cursor->pos.z) * (pos.z - cursor->pos.z);

	//もし距離が近ければ
	if (cursorToPlayer < 16)
	{
		cursor->collision = true;
		cursor->colorCounter += 0.05f;
		if (keys[' '])
		{
			selectedFlag = true;

		}
	}
	else
	{
		cursor->collision = false;
		cursor->colorCounter = 0;
		if (keys[' '])
		{
			selectedFlag = false;

		}
	}

}

///////////////////////////////////
//移動
///////////////////////////////////
void Player::move()
{
	//カーソルとプレイヤーの距離
	const float cursorToPlayer =
		(pos.x - cursor->pos.x) * (pos.x - cursor->pos.x)
		+ (pos.y - cursor->pos.y) * (pos.y - cursor->pos.y)
		+ (pos.z - cursor->pos.z) * (pos.z - cursor->pos.z);

	//プレイヤーキャラの選択時
	if (selectedFlag == true)
	{
		//キャラクターを黄色に
		characterColor = glm::vec3(1, 1, 0);
		if (keys[' '])
		{
			//移動の目的地設定
			if (cursorToPlayer > 25)
			{
				moveOnFlag = true;
				moveTargetPoint = glm::vec3(cursor->pos.x, pos.y, cursor->pos.z);	//目的地

				//移動のために、正規化
				glm::vec3 PlayerToTargetPoint(
					moveTargetPoint.x - pos.x,
					0,
					moveTargetPoint.z - pos.z);

				speed = glm::normalize(PlayerToTargetPoint) * 0.1f;

			}
		}
	}
	else
	{
		//青に戻す
		characterColor = glm::vec3(0.2f, 0.3f, 0.7f);
	}

	//目的地までの距離
	const float playerToTargetPoint =
		(pos.x - moveTargetPoint.x) * (pos.x - moveTargetPoint.x)
		+ (pos.y - moveTargetPoint.y) * (pos.y - moveTargetPoint.y)
		+ (pos.z - moveTargetPoint.z) * (pos.z - moveTargetPoint.z);


	//目的地に着いたとき
	if (playerToTargetPoint < 2)
	{
		//移動終わり
		moveOnFlag = false;
		speed = glm::vec3(0, 0, 0);

	}


}

///////////////////////////////////
//敵陣地に攻撃
///////////////////////////////////
void Player::attackToCamp() {

	std::list< EnemyCamp >::iterator enemyCampIter = enemyCamp.begin();

	while (enemyCampIter != enemyCamp.end())
	{
		const float playerToEnemyCamp =
			(pos.x - enemyCampIter->pos.x) * (pos.x - enemyCampIter->pos.x)
			+ (pos.y - enemyCampIter->pos.y) * (pos.y - enemyCampIter->pos.y)
			+ (pos.z - enemyCampIter->pos.z) * (pos.z - enemyCampIter->pos.z);

		if (playerToEnemyCamp < 100)
		{
			const int Damage = Attack - enemyCampIter->Defense;
			//enemyCampIter->damage = Damage / 10;
			enemyCampIter->HP -= Damage / 10;// enemyCampIter->damage;

			if (playerToEnemyCamp < 25)
			{
				pos = lastPos;
				moveOnFlag = false;
			}
		}
		else
		{
			enemyCampIter->damage = 0;
		}

		++enemyCampIter;
	}



}