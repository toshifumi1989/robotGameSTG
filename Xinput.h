#ifndef XINPUT_H
#define XINPUT_H

#define INPUT_DEADZONE  ( 0.24f * FLOAT(0x7FFF) ) 
#define MAX_CONTROLLERS 1

#include<windows.h>
#include<Xinput.h>
#pragma comment (lib,"XInput.lib")

class CONTROLER_STATE {
public:
	CONTROLER_STATE():
		leftTrigerFlag(false),
		lastleftTriger(false),
		rightTrigerFlag(false),
		lastrightTriger(false)
	{}

	XINPUT_STATE state;
	bool bConnected;

	bool leftTrigerFlag;
	bool lastleftTriger;
	void leftTriger();//���g���K�[��ON��OFF��

	bool rightTrigerFlag;
	bool lastrightTriger;
	void rightTriger();//�E�g���K�[��ON��OFF��

	bool upKeysFlag;
	bool lastUpKeys;
	void upKeys();//���X�e�B�b�N�̏��ON��OFF��

	bool downKeysFlag;
	bool lastDownKeys;
	void downKeys();//���X�e�B�b�N�̉���ON��OFF��

	void GetState(int _i);//�W���C�X�e�B�b�N�̔ԍ�����U��

	WORD lastkeys;

	//const WORD pressedKeys = joystic.state.Gamepad.wButtons;					//�����Ă���{�^��
	//const WORD releasedKeys = ~joystic.state.Gamepad.wButtons;				//���ꂽ�{�^��
	//const WORD changedKeys = joystic.lastkeys ^ pressedKeys;		//�؂�ւ�����{�^��
	//const WORD downKeys = changedKeys & pressedKeys;		//���������{�^��
	//const WORD upKeys = changedKeys & releasedKeys;

};

extern CONTROLER_STATE joystic;

#endif