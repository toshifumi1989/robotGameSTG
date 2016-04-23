#include"joystic.h"

Joystic* Joystic::instance = nullptr;

Joystic* Joystic::getInstance() {

	if (nullptr == instance) {
		instance = new Joystic();
	}
	return instance;
}


void Joystic::input(unsigned int _buttonMask, int _x, int _y, int _z) {
	const int pressedKeys = buttonMask;					//押しているボタン
	const int releasedKeys = ~buttonMask;				//離れたボタン
	const int changedKeys = lastkeys ^ pressedKeys;		//切り替わったボタン
	const int downKeys = changedKeys & pressedKeys;		//今押したボタン
	const int upKeys = changedKeys & releasedKeys;		//今離れたボタン









	lastkeys = _buttonMask;
}