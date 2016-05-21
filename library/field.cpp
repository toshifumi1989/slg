#include "field.h"
#include"../glm/gtx/intersect.hpp"

Field *field;

/////////////////////////////
//�t�B�[���h����
/////////////////////////////
void Field::setup() 
{

	for (int z = 0; z < vtx; z++) 
	{
		for (int x = 0; x < vtx; x++) 
		{

			//texture
			tex.push_back((float)x / (vtx - 1));
			tex.push_back((float)z / (vtx - 1));

			//vertex
			vertex.push_back((float)x );
			vertex.push_back(0);
			vertex.push_back((float)z );

			//normal
			normal.push_back(0);
			normal.push_back(1);
			normal.push_back(0);
		}
	}

	for (int z = 0; z < vtx - 1; z++)
	{//�s�̐�
		for (int x = 0; x < vtx - 1; x++)
		{//��̐�

			//index
			index.push_back(vtx * z + x);
			index.push_back(vtx * z + x + vtx);
			index.push_back(vtx * z + x + 1);
			index.push_back(vtx * z + x + 1);
			index.push_back(vtx * z + x + vtx);
			index.push_back(vtx * z + x + vtx + 1);
		}
	}
}


////////////////////////////////////
//�t�B�[���h�`��
////////////////////////////////////
void Field::draw() 
{
	glPushMatrix();
	{
		glBindTexture(GL_TEXTURE_2D, textures[0]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glEnable(GL_TEXTURE_2D);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);

		const float *v = vertex.data();
		const float *n = normal.data();
		const unsigned int *ind = index.data();
		const float *t = tex.data();

		glVertexPointer(3, GL_FLOAT, 0, v);
		glNormalPointer(GL_FLOAT, 0, n);
		glTexCoordPointer(2, GL_FLOAT, 0, t);

		glDrawElements(GL_TRIANGLES, index.size(), GL_UNSIGNED_INT, ind);

		glDisable(GL_TEXTURE_2D);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);

	}
	glPopMatrix();
}

/////////////////////////////////
//�t�B�[���h�Ƃ̓����蔻��
/////////////////////////////////
void Field::intersect(glm::vec3 _pos) 
{

	glm::vec3 orig = glm::vec3(_pos.x, -1, _pos.z);//�n�_�ŁA������̔C�ӂ̓_
	glm::vec3 dir = glm::vec3(0, 1, 0);//�����̌����ŁA�������`����
	glm::vec3 vert0;//�ȉ��̂R�_�ŎO�p�`���`
	glm::vec3 vert1;
	glm::vec3 vert2;
	glm::vec3 distance = glm::vec3(0, 0, 0);//x�����o�ɁA�n�_��������_�̋������擾�����

	int temporaryX = _pos.x;//x���W�̐�������
	int temporaryZ = _pos.z;//z���W�̐�������
	float nowPosY = _pos.y;//���݂�y���W

	if ((_pos.x - temporaryX) + (_pos.z - temporaryZ) < 1)
	{

		//��̎O�p
		vert0 = glm::vec3(temporaryX, vertex[(vtx * temporaryZ + temporaryX) * 3 + 1], temporaryZ);
		vert1 = glm::vec3(temporaryX + 1, vertex[(vtx * temporaryZ + temporaryX + 1) * 3 + 1], temporaryZ);
		vert2 = glm::vec3(temporaryX, vertex[((vtx * (temporaryZ + 1)) + temporaryX) * 3 + 1], temporaryZ + 1);

		if (glm::intersectLineTriangle(orig, dir, vert0, vert1, vert2, distance))
		{
			if (_pos.y <= distance.x) 
			{
				charcterHeight = distance.x;
			}
		}
	}
	else
	{
		//���̎O�p
		vert0 = glm::vec3(temporaryX + 1, vertex[(vtx * temporaryZ + temporaryX + 1) * 3 + 1], temporaryZ);
		vert1 = glm::vec3(temporaryX, vertex[((vtx * (temporaryZ + 1)) + temporaryX) * 3 + 1], temporaryZ + 1);
		vert2 = glm::vec3(temporaryX + 1, vertex[((vtx * (temporaryZ + 1)) + temporaryX + 1) * 3 + 1], temporaryZ + 1);

		if (glm::intersectLineTriangle(orig, dir, vert0, vert1, vert2, distance))
		{
			if (_pos.y <= distance.x) 
			{
				charcterHeight = distance.x;
			}
		}
	}


	glm::vec3 intersect = orig + dir * distance.x;
	charcterHeight = intersect.y;
}