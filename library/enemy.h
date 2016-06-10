#ifndef ENEMY_H
#define ENEMY_H

#include <list>
#include "character.h"

///////////////////////////////////
//エネミーキャラクタークラス
///////////////////////////////////
class Enemy : public Character
{
public:
	Enemy() {}
	~Enemy() {}

	void update();				//更新
	void draw();				//描画
	void attackToBase();		//攻撃判定
	void AI(unsigned char _targetType, unsigned char _target, unsigned char _pattern);			//AI

	//list管理の敵に攻撃
	template< typename TempPlayer >
	void attackToObject(std::list< TempPlayer > _object)
	{
		std::list< TempPlayer >::iterator iter = _object.begin();


		while (iter != _object.end())
		{
			const float enemyToObject =
				(pos.x - (*iter)->pos.x) * (pos.x - (*iter)->pos.x)
				+ (pos.y - (*iter)->pos.y) * (pos.y - (*iter)->pos.y)
				+ (pos.z - (*iter)->pos.z) * (pos.z - (*iter)->pos.z);

			if (enemyToObject < 10 * attackRange)
			{
				OnAttack = true;
				(*iter)->OnDefense = true;
				(*iter)->damage = (Attack - (*iter)->Defense) / 10.f;

				(*iter)->HP -= (*iter)->damage;

				if (enemyToObject < 5 * attackRange)
				{
					pos = lastPos;
					moveOnFlag = false;

				}
			}
			else
			{
				OnAttack = false;
				(*iter)->OnDefense = false;
				(*iter)->damage = 0;
			}


			++iter;
		}

	}

};

extern std::list< Enemy* > enemy;

#endif