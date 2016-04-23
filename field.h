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

	float nextY;//�����蔻�莞��Y���W��u���Ă����ꏊ

	void readField(const char* _texture);//�t�B�[���h�ǂݍ���
	void setup();//�`�悷�邽�߂̐ݒ菀��
	void drawField();//�`��

	void intersect(glm::vec3 _pos);//�t�B�[���h�Ƃ̓����蔻��
};

extern Field *field;

#endif