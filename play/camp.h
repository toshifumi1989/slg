#ifndef CAMP_H
#define CAMP_H

#include "../library/gameObject.h"

class Camp :public GameObject
{
public:
	Camp() :
		ID(0),
		HP(1000),
		Defense(10),
		damage(0),
		size(5,2,5),

		OnDefense(false)
	{}
	virtual ~Camp() {}

	unsigned char ID;			//”Ô†
	int HP;						//‘Ï‹v’l
	unsigned int Defense;		//–hŒä—Í
	unsigned int damage;		//ƒ_ƒ[ƒW—Ê
	glm::vec3 size;				//w’n‚Ì‘å‚«‚³

	bool OnDefense;				//UŒ‚‚ğó‚¯‚Ä‚¢‚é
};

#endif