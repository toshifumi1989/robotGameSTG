#ifndef CAMERA_H
#define CAMERA_H

#include"../glm/glm.hpp"


class Camera {
public:
	Camera() :
		angle(60.0f),
		aspect(1000.f / 700.f),
		nearDraw(1),
		farDraw(500),

		left(0),
		right(5000),
		bottom(0),
		top(5000),

		upDown(0),
		lastUpDown(0),
		yow(0),
		
		pos(0, 1, 4),
		target(0, 0, 0),
		up(0, 1, 0),
		lastPos(0, 1, 4),
		lastTarget(0,0,0)
	{}

	~Camera(){}

	float angle;//�\���p�x
	float aspect;//�A�X�y�N�g
	float nearDraw;//�ǂꂭ�炢�߂��܂ŕ`�悷�邩
	float farDraw;//�ǂꂭ�炢�����܂ŕ`�悷�邩

	float left;//2D�̍���
	float right;//2D�̉E��
	float bottom;//2D�̉���
	float top;//2D�̏㑤

	float upDown;//�J�����̏㉺�̓����i��������邽��
	float lastUpDown;//�O�̃t���[���ł�upDown
	float yow;//�J�����̍��E�̓���

	glm::vec3 pos;//�J�����̈ʒu
	glm::vec3 target;//�J�����̌���
	glm::vec3 up;//�J�����̏�̌���
	glm::vec3 lastPos;//�O�̃t���[���ł̈ʒu
	glm::vec3 lastTarget;//�O�̃t���[���ł̌���

	void move();//�J�����̈ړ�
	void update();//�J�����̍X�V
	void plane();//2D�p�̃J�����ݒ�

};

extern Camera *camera;

#endif