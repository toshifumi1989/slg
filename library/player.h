#ifndef PLAYER_H
#define PLAYER_H

#include <list>
#include "character.h"
#include "field.h"

/////////////////////////////////////
//�v���C���[�L�����N�^�[class
/////////////////////////////////////
class Player : public Character 
{
public:
	Player() :
		characterColor(0.2f, 0.4f, 0.7f)
	{}
	~Player(){}

	glm::vec3 characterColor;		//�L�����N�^�[�̐F


	void update();					//�X�V
	void draw(unsigned char _type);	//�`��
	void collisionCursor();			//�J�[�\�������蔻��
	void move();					//�L�����N�^�[�ړ�
	void attackToBase();			//�G�w�n�ɍU��

	//list�Ǘ��̓G�ɍU��
	template < typename TempEnemy > void attackToObject(std::list< TempEnemy > _object)
	{
		std::list< TempEnemy >::iterator iter = _object.begin();
		
		while (iter != _object.end())
		{
			const float playerToObject =
				(pos.x - (*iter)->pos.x) * (pos.x - (*iter)->pos.x)
				+ (pos.y - (*iter)->pos.y) * (pos.y - (*iter)->pos.y)
				+ (pos.z - (*iter)->pos.z) * (pos.z - (*iter)->pos.z);

			if (playerToObject < 10 * attackRange)
			{
				OnAttack = true;
				(*iter)->OnDefense = true;
				(*iter)->damage = (Attack - (*iter)->Defense) / 10.f;

				(*iter)->HP -= (*iter)->damage;

				if (playerToObject < 5 * attackRange)
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

	};
	
};

extern std::list < Player* > player;

#endif