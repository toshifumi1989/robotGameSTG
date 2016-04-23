#ifndef BULLET_H
#define BULLET_H

#include"object.h"
#include"effect.h"
#include<list>


class Bullet :public Object {
public:
	Bullet():
		onFlag(true),
		size(0.1f),
		onCount(0),
		damageSize(4)
	{}
	~Bullet(){}

	bool onFlag;//on‚È‚ç’e‚ª‚ ‚é
	float size;//’e‚Ì‘å‚«‚³
	unsigned char onCount;//”ƒtƒŒ[ƒ€‚·‚·‚Ş‚Æ’e‚ªÁ‚¦‚é
	unsigned char damageSize;//ƒ_ƒ[ƒW—Ê

	void draw();//’e‚Ì•`‰æ
	void update();//’e‚ÌXV
	void hitCharacter(Object *_character);//’e‚Ì“–‚½‚è”»’è
};

extern std::list<Bullet> playerBullet;
extern std::list<Bullet> machineGun;
extern std::list<Bullet> enemyBullet;




#endif