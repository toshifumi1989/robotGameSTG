#ifndef ENEMY_H
#define ENEMY_H

#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS

#include<vector>
#include<math.h>
#include"object.h"
#include"bullet.h"

class Enemy :public Object {
public:
	Enemy():		
	actionCount(0)
	{}

	~Enemy(){}

	char actionCount;//�s�����邽�߂̃J�E���g
	void readModel(const char* _model);//���f���ǂݍ���
	void update();//�X�V
	void draw(int _i);//�`��i�^�[�Q�b�g�}�[�J�[�̔ԍ�)
	void action();//�s���p�^�[��

};

extern std::vector<Enemy> enemy;

#endif