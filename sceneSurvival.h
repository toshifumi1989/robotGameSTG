#ifndef SCENESURVIVAL_H
#define SCENESURVIVAL_H

#include"library\bullet.h"
#include"library\effect.h"
#include"library\player.h"
#include"library\enemy.h"
#include"library\texture.h"
#include"library\camera.h"
#include"library\explotion.h"
#include"library\field.h"
#include"library\sound.h"

class Survival {
public:
	void init();
	void update();
	void draw();
};

extern Survival *survival;

#endif
