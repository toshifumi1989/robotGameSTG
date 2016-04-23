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

	bool onFlag;//on�Ȃ�e������
	float size;//�e�̑傫��
	unsigned char onCount;//���t���[�������ނƒe��������
	unsigned char damageSize;//�_���[�W��

	void draw();//�e�̕`��
	void update();//�e�̍X�V
	void hitCharacter(Object *_character);//�e�̓����蔻��
};

extern std::list<Bullet> playerBullet;
extern std::list<Bullet> machineGun;
extern std::list<Bullet> enemyBullet;




#endif