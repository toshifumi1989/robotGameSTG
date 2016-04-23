#ifndef EXPLOTION_H
#define EXPLOTION_H

#include"effect.h"

class Explotion : public Object {
public:

	std::list<Effect>smoke;
	std::list<Effect>fire;

	void initExplotion();//爆発エフェクトの初期化
	void drawExplotion();//爆発エフェクトの描画
	void smokeDraw();//煙エフェクトの描画
	void fireDraw();//炎エフェクトの描画
};

extern std::list<Explotion>explotion;

#endif