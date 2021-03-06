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

	bool onFlag;//onなら弾がある
	float size;//弾の大きさ
	unsigned char onCount;//数フレームすすむと弾が消える
	unsigned char damageSize;//ダメージ量

	void draw();//弾の描画
	void update();//弾の更新
	void hitCharacter(Object *_character);//弾の当たり判定
};

extern std::list<Bullet> playerBullet;
extern std::list<Bullet> machineGun;
extern std::list<Bullet> enemyBullet;




#endif