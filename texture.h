#ifndef TEXTURE_H
#define TEXTURE_H

#define _CRT_SECURE_NO_WARNINGS
#define VTX (256)

#include<vector>
#include<assert.h>
#include<Windows.h>
#include<stdlib.h>
#include"../glut.h"

extern GLuint textures[7];

class Texture {
public:
	typedef struct { unsigned char b, g, r; }RGB;//�F��RGB�̒l

	std::vector<unsigned char>alpha;//�A���t�@�l

	std::vector<float>vertex;//�ʒu
	std::vector<float>normal;//�@��
	std::vector<unsigned int>index;//�ԍ�
	std::vector<float>tex;//�e�N�X�`���ԍ�

	void read(const char* _texture);//�ǂݍ���
	void read_alpha(const char* _texture);//�ǂݍ��݁i�A���t�@

};

extern Texture *target;
extern Texture *opening;
extern Texture *smokeRing;
extern Texture *marker;
extern Texture *name;
extern Texture *modeSelect;

#endif