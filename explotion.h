#ifndef EXPLOTION_H
#define EXPLOTION_H

#include"effect.h"

class Explotion : public Object {
public:

	std::list<Effect>smoke;
	std::list<Effect>fire;

	void initExplotion();//�����G�t�F�N�g�̏�����
	void drawExplotion();//�����G�t�F�N�g�̕`��
	void smokeDraw();//���G�t�F�N�g�̕`��
	void fireDraw();//���G�t�F�N�g�̕`��
};

extern std::list<Explotion>explotion;

#endif