#ifndef SCENEPLAYGAME_H
#define SCENEPLAYGAME_H

#include"library\bullet.h"
#include"library\effect.h"
#include"library\player.h"
#include"library\enemy.h"
#include"library\texture.h"
#include"library\camera.h"
#include"library\explotion.h"
#include"library\field.h"

class PlayGame {
public:
	void init();
	void update();

};

extern PlayGame *playGame;

#endif
