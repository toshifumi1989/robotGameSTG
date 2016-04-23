#ifndef EFFECT_H
#define EFFECT_H

#include<list>
#include"../glm/glm.hpp"
#include"object.h"

extern GLuint textures[7];

class Effect :public Object {
public:
	Effect() :
		alpha(1),
		alphaSpeed(0),
		drawCount(0),
		OnFlag(false),
		scale(1,1,1),
		sclSpeed(0,0,0)
	{}
	~Effect() {}

	float alpha;//アルファ値
	float alphaSpeed;//アルファ値の変更速度
	unsigned int drawCount ;//描画始めてからのカウント
	bool OnFlag;//今エフェクトがあるかのフラグ

	glm::vec3 scale;//大きさ
	glm::vec3 sclSpeed;//大きさ変更速度

	void initSmokeTexture();//煙描画の初期設定
	void update();//描画の更新
	void draw();//描画

};

extern std::list<Effect>damage;


#endif