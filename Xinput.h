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
	void leftTriger();//左トリガーのONかOFFか

	bool rightTrigerFlag;
	bool lastrightTriger;
	void rightTriger();//右トリガーのONかOFFか

	bool upKeysFlag;
	bool lastUpKeys;
	void upKeys();//左スティックの上でONかOFFか

	bool downKeysFlag;
	bool lastDownKeys;
	void downKeys();//左スティックの下でONかOFFか

	void GetState(int _i);//ジョイスティックの番号割り振り

	WORD lastkeys;

	//const WORD pressedKeys = joystic.state.Gamepad.wButtons;					//押しているボタン
	//const WORD releasedKeys = ~joystic.state.Gamepad.wButtons;				//離れたボタン
	//const WORD changedKeys = joystic.lastkeys ^ pressedKeys;		//切り替わったボタン
	//const WORD downKeys = changedKeys & pressedKeys;		//今押したボタン
	//const WORD upKeys = changedKeys & releasedKeys;

};

extern CONTROLER_STATE joystic;

#endif