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

	const int MaxHP ;//HP�̍ő�l

	int shotGauge;//���݂̃V���b�g�Q�[�W
	int shotGaugeOver;//�V���b�g�Q�[�W�̍ő�l
	int shotGaugeUnder;//�V���b�g�Q�[�W�̍ŏ��l
	bool overHeat;//�V���b�g�Q�[�W��0�ɂȂ����Ƃ��I�[�o�[�q�[�g�ɂȂ�i�e�����ĂȂ��Ȃ�

	float heatDepth;//�����̓_�ł̂��߂̐���
	
	bool junpFlag;//���݃W�����v���Ă��邩

	unsigned int scorePoint;//�T�o�C�o�����[�h���̃X�R�A�l
	void readModel(const char* _model);//���f���ǂݍ���
	void update();//�X�V
	void draw();//�`��
	void show();//2D�`��
	void turn(bool _isRightTrun);//�^�[�Q�b�g�؂�ւ�

	glm::vec3 shootTarget;//�V���b�g�}�[�N�̈ʒu
	float updown;//�}�[�N�̏㉺

	bool targetFlag;//���b�N�I���̂��Ă��邩���Ȃ���
	int targetNum;//���Ԃ̓G���^�[�Q�b�g�Ƃ��Ă��邩
	float nextTargetCross;//�v���C���[��荶���ɂ��邩�E���ɂ��邩

	std::list<Effect>cloudOfDust;
	void initDust();//�y���̏����ݒ�
	void drawDust();//�y���̕`��

	void targetMaekerUpdate();//�^�[�Q�b�g�}�[�J�[�̍X�V
	void targetMaekerDraw();//�^�[�Q�b�g�}�[�J�[�̕`��
	//Xinput------------------------------	
	void controller();//�R���g���[���[�ł̓���

	
};

extern Player *player;



#endif
