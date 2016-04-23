#ifndef EFFECT_H
#define EFFECT_H

#include<list>
#include"../glm/glm.hpp"
#include"object.h"

extern GLuint textures[7];

class Effect :public Object {
public:
	Effect() :
		alpha(1),
		alphaSpeed(0),
		drawCount(0),
		OnFlag(false),
		scale(1,1,1),
		sclSpeed(0,0,0)
	{}
	~Effect() {}

	float alpha;//�A���t�@�l
	float alphaSpeed;//�A���t�@�l�̕ύX���x
	unsigned int drawCount ;//�`��n�߂Ă���̃J�E���g
	bool OnFlag;//���G�t�F�N�g�����邩�̃t���O

	glm::vec3 scale;//�傫��
	glm::vec3 sclSpeed;//�傫���ύX���x

	void initSmokeTexture();//���`��̏����ݒ�
	void update();//�`��̍X�V
	void draw();//�`��

};

extern std::list<Effect>damage;


#endif