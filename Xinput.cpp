#include"Xinput.h"

/////////////////////////////////////////////
//Xinputを使用するためのジョイスティック番号
/////////////////////////////////////////////
void CONTROLER_STATE::GetState(int _i) {
	DWORD dwResult;
	{
		// Simply get the state of the controller from XInput.
		dwResult = XInputGetState(_i, &state);

		if (dwResult == ERROR_SUCCESS)
			bConnected = true;
		else
			bConnected = false;
	}
}

//////////////////////////////////////////////
//ジョイスティックの左トリガをONかOFFにするため
//////////////////////////////////////////////
void CONTROLER_STATE::leftTriger() {
	bool trigerFlag;

	if (state.Gamepad.bLeftTrigger > 100) {
		trigerFlag = true;
	}
	else {
		trigerFlag = false;
	}

	const bool changedtriger = lastleftTriger ^ trigerFlag;
	leftTrigerFlag = changedtriger & trigerFlag;
	lastleftTriger = trigerFlag;

}

/////////////////////////////////////////////////
//ジョイスティックの右トリガをONかOFFにするため
/////////////////////////////////////////////////
void CONTROLER_STATE::rightTriger() {
	bool trigerFlag;
	
	if (state.Gamepad.bRightTrigger > 100) {
		trigerFlag = true;
	}
	else {
		trigerFlag = false;
	}

	const bool changedtriger = lastrightTriger ^ trigerFlag;
	rightTrigerFlag = changedtriger & trigerFlag;
	lastrightTriger = trigerFlag;
}

//////////////////////////////////////////////////
//左スティックの上をONかOFFにするため
//////////////////////////////////////////////////
void CONTROLER_STATE::upKeys() {
	bool stickFlag;

	if (state.Gamepad.sThumbLY > 5000) {
		stickFlag = true;
	}
	else {
		stickFlag = false;
	}

	const bool changedUpKeys = lastUpKeys ^ stickFlag;
	upKeysFlag = changedUpKeys & stickFlag;
	lastUpKeys = stickFlag;
}

//////////////////////////////////////////////
//左スティックの下をONかOFFにするため
///////////////////////////////////////////////
void CONTROLER_STATE::downKeys() {
	bool stickFlag;

	if (state.Gamepad.sThumbLY < -5000) {
		stickFlag = true;
	}
	else {
		stickFlag = false;
	}

	const bool changedDownKeys = lastDownKeys ^ stickFlag;
	downKeysFlag = changedDownKeys & stickFlag;
	lastDownKeys = stickFlag;
}