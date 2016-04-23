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

	int HP;//�I�u�W�F�N�g�̗̑�
	float angle;//�I�u�W�F�N�g�̌���

	std::vector<float>vertex;//�I�u�W�F�N�g�̕`��̂���
	std::vector<float>normal;//
	std::vector<unsigned short>index;//

	glm::vec3 position;//�ʒu
	glm::vec3 lastPosition;//�O�̃t���[���̈ʒu

	glm::vec3 speed;//�ʒu�̈ړ�����

};

#endif
