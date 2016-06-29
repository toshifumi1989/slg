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

	float angle;		//表示角度
	float aspect;		//アスペクト
	float nearDraw;		//どれくらい近くまで描画するか
	float farDraw;		//どれくらい遠くまで描画するか

	float left;			//2Dの左側
	float right;		//2Dの右側
	float bottom;		//2Dの下側
	float top;			//2Dの上側

	glm::vec3 pos;		//カメラの位置
	glm::vec3 target;	//カメラの向き
	glm::vec3 up;		//カメラの上の向き

	float cameraHeight;	//カメラの高さ
	int specialKey;		//キーボードの↑↓の為

	void setUp();		//戦闘準備用
	void update();		//カメラの更新
	void draw();		//カメラの描画
	void twoDimensionCamera();//２次元の描画
};

extern Camera *camera;

#endif