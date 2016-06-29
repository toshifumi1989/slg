#ifndef CAMERA_H
#define CAMERA_H

#include "../glm/glm.hpp"

class Camera
{
public:
	Camera() :
		angle(60.0f),
		aspect(1000.f / 700.f),
		nearDraw(1),
		farDraw(500),

		left(0),
		right(5000),
		bottom(0),
		top(5000),

		pos(0, 20, -4),
		target(0, 0, 0),
		up(0, 1, 0),

		cameraHeight(100),
		specialKey(0)
	{}

	float angle;		//�\���p�x
	float aspect;		//�A�X�y�N�g
	float nearDraw;		//�ǂꂭ�炢�߂��܂ŕ`�悷�邩
	float farDraw;		//�ǂꂭ�炢�����܂ŕ`�悷�邩

	float left;			//2D�̍���
	float right;		//2D�̉E��
	float bottom;		//2D�̉���
	float top;			//2D�̏㑤

	glm::vec3 pos;		//�J�����̈ʒu
	glm::vec3 target;	//�J�����̌���
	glm::vec3 up;		//�J�����̏�̌���

	float cameraHeight;	//�J�����̍���
	int specialKey;		//�L�[�{�[�h�́����̈�

	void setUp();		//�퓬�����p
	void update();		//�J�����̍X�V
	void draw();		//�J�����̕`��
	void twoDimensionCamera();//�Q�����̕`��
};

extern Camera *camera;

#endif