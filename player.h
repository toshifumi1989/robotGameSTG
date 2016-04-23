#ifndef PLAYER_H
#define PLAYER_H

#define _CRT_SECURE_NO_WARNINGS
#include"object.h"
#include"effect.h"
#include"Xinput.h"

class Player :public Object {
public:
	Player() :
		MaxHP(200),

		shotGauge(1000),
		shotGaugeOver(1000),
		shotGaugeUnder(0),
		overHeat(false),
		heatDepth(0),

		junpFlag(true),

		shootTarget(0, 0, 0),
		updown(0),

		targetFlag(false),
		targetNum(0),
		nextTargetCross(0),

		scorePoint(0)
	{}
	~Player(){}

	const int MaxHP ;//HPの最大値

	int shotGauge;//現在のショットゲージ
	int shotGaugeOver;//ショットゲージの最大値
	int shotGaugeUnder;//ショットゲージの最小値
	bool overHeat;//ショットゲージが0になったときオーバーヒートになる（弾が撃てなくなる

	float heatDepth;//文字の点滅のための数字
	
	bool junpFlag;//現在ジャンプしているか

	unsigned int scorePoint;//サバイバルモード時のスコア値
	void readModel(const char* _model);//モデル読み込み
	void update();//更新
	void draw();//描画
	void show();//2D描画
	void turn(bool _isRightTrun);//ターゲット切り替え

	glm::vec3 shootTarget;//ショットマークの位置
	float updown;//マークの上下

	bool targetFlag;//ロックオンのしているかいないか
	int targetNum;//何番の敵をターゲットとしているか
	float nextTargetCross;//プレイヤーより左側にいるか右側にいるか

	std::list<Effect>cloudOfDust;
	void initDust();//土埃の初期設定
	void drawDust();//土埃の描画

	void targetMaekerUpdate();//ターゲットマーカーの更新
	void targetMaekerDraw();//ターゲットマーカーの描画
	//Xinput------------------------------	
	void controller();//コントローラーでの動き

	
};

extern Player *player;



#endif
