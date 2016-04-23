#ifndef FIELD_H
#define FIELD_H

#include"../glm/glm.hpp"
#include"texture.h"

class Field : public Texture {
public:
	Field():
		nextY(0)
	{}
	~Field(){}

	RGB *pixelsField;

	float nextY;//当たり判定時のY座標を置いておく場所

	void readField(const char* _texture);//フィールド読み込み
	void setup();//描画するための設定準備
	void drawField();//描画

	void intersect(glm::vec3 _pos);//フィールドとの当たり判定
};

extern Field *field;

#endif