#ifndef OBJECT_H
#define OBJECT_H

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<vector>
#include"../glut.h"
#include"../glm/glm.hpp"

class Object {
public:
	Object() :
		HP(20),
		angle(0),
		position(0,0,0),
		lastPosition(0,0,0),
		speed(0,0,0)
	{}

	~Object(){}

	int HP;//オブジェクトの体力
	float angle;//オブジェクトの向き

	std::vector<float>vertex;//オブジェクトの描画のため
	std::vector<float>normal;//
	std::vector<unsigned short>index;//

	glm::vec3 position;//位置
	glm::vec3 lastPosition;//前のフレームの位置

	glm::vec3 speed;//位置の移動速さ

};

#endif
