#ifndef CAMERA_H
#define CAMERA_H

#include"../glm/glm.hpp"


class Camera {
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

		upDown(0),
		lastUpDown(0),
		yow(0),
		
		pos(0, 1, 4),
		target(0, 0, 0),
		up(0, 1, 0),
		lastPos(0, 1, 4),
		lastTarget(0,0,0)
	{}

	~Camera(){}

	float angle;//表示角度
	float aspect;//アスペクト
	float nearDraw;//どれくらい近くまで描画するか
	float farDraw;//どれくらい遠くまで描画するか

	float left;//2Dの左側
	float right;//2Dの右側
	float bottom;//2Dの下側
	float top;//2Dの上側

	float upDown;//カメラの上下の動き（上限をつけるため
	float lastUpDown;//前のフレームでのupDown
	float yow;//カメラの左右の動き

	glm::vec3 pos;//カメラの位置
	glm::vec3 target;//カメラの向き
	glm::vec3 up;//カメラの上の向き
	glm::vec3 lastPos;//前のフレームでの位置
	glm::vec3 lastTarget;//前のフレームでの向き

	void move();//カメラの移動
	void update();//カメラの更新
	void plane();//2D用のカメラ設定

};

extern Camera *camera;

#endif