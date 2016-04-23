#ifndef SCENERESULT_H
#define SCENERESULT_H

#include"library\Xinput.h"

class Result {
public:
	Result() :
		wordCount(0),
		sceneMove(false)
	{}
	~Result(){}

	unsigned char wordCount;
	bool sceneMove;
	void sceneInit();
	void sceneUpdate();

};

extern Result *result;

#endif
