#ifndef SCENETITLE_H
#define SCENETITLE_H

#include"library\Xinput.h"
#include"library\texture.h"
#include"glm\glm.hpp"

enum TITLE {
	start,
	modeNormal,
	modeSurvival
};

class SceneTitle {
public:
	SceneTitle() :
		moveSelect(false),
		titleScale(1, 1, 1),
		wordCount(0),
		change(start),
		sceneMove(false),
		mask(0)
	{}
	~SceneTitle() {}

	bool moveSelect;
	glm::vec3 titleScale;
	unsigned int wordCount;
	unsigned char change;
	bool sceneMove;
	float mask;

	void init();
	void update();

};

extern SceneTitle *title;

#endif