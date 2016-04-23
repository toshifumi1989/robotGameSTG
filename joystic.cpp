#include"joystic.h"

Joystic* Joystic::instance = nullptr;

Joystic* Joystic::getInstance() {

	if (nullptr == instance) {
		instance = new Joystic();
	}
	return instance;
}


void Joystic::input(unsigned int _buttonMask, int _x, int _y, int _z) {
	const int pressedKeys = buttonMask;					//�����Ă���{�^��
	const int releasedKeys = ~buttonMask;				//���ꂽ�{�^��
	const int changedKeys = lastkeys ^ pressedKeys;		//�؂�ւ�����{�^��
	const int downKeys = changedKeys & pressedKeys;		//���������{�^��
	const int upKeys = changedKeys & releasedKeys;		//�����ꂽ�{�^��









	lastkeys = _buttonMask;
}