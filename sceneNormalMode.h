#ifndef SCENENORMALMODE_H
#define SCENENORMALMODE_H

#include"library\bullet.h"
#include"library\effect.h"
#include"library\player.h"
#include"library\enemy.h"
#include"library\texture.h"
#include"library\camera.h"
#include"library\explotion.h"
#include"library\field.h"

class NormalMode {
public:
	void init();
	void update();
	void draw();
};

extern NormalMode *normalMode;

#endif