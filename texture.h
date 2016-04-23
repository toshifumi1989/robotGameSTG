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
	typedef struct { unsigned char b, g, r; }RGB;//色のRGBの値

	std::vector<unsigned char>alpha;//アルファ値

	std::vector<float>vertex;//位置
	std::vector<float>normal;//法線
	std::vector<unsigned int>index;//番号
	std::vector<float>tex;//テクスチャ番号

	void read(const char* _texture);//読み込み
	void read_alpha(const char* _texture);//読み込み（アルファ

};

extern Texture *target;
extern Texture *opening;
extern Texture *smokeRing;
extern Texture *marker;
extern Texture *name;
extern Texture *modeSelect;

#endif