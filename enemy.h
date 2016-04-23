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

	char actionCount;//行動するためのカウント
	void readModel(const char* _model);//モデル読み込み
	void update();//更新
	void draw(int _i);//描画（ターゲットマーカーの番号)
	void action();//行動パターン

};

extern std::vector<Enemy> enemy;

#endif