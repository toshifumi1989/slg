#ifndef PLAY_H
#define PLAY_H

#include <list>
#include "scene.h"


class Play : public Scene
{
public:
	void init();
	void update();
	void draw();

	template < typename TempDead > void dead(std::list< TempDead > _object)
	{
		std::list< TempDead >::iterator iter = _object.begin();
		while (iter != _object.end())
		{
			if ((*iter)->HP <= 0)
			{
				delete (*iter);
				iter = _object.erase(iter);
				continue;
			}
			//else
			//{
			//	++iter;
			//}


			++iter;
		}
	};
};


#endif