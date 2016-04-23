#define _USE_MATH_DEFINES

#include <stdio.h>
#include <math.h>
#include "camera.h"
#include "player.h"
#include "enemy.h"

extern Player *player;

//////////////////////////////////
//���t���[���̍X�V
/////////////////////////////////
void Camera::update() {

	glMatrixMode(GL_PROJECTION);          /* ���e�ϊ��s��̐ݒ� */
	glLoadIdentity();                     /* �ϊ��s��̏����� */
	gluPerspective(angle, aspect, nearDraw, farDraw); //�������e�@�̎��̐�gluPerspactive(th, w/h, near, far);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}


/////////////////////////////////////////
//�J�����̈ړ�
////////////////////////////////////////
void Camera::move() {

	//���b�N�I�������Ă���Ƃ�
	if (player->targetFlag == true) {

		//�ʒu----------------------------------------------------
		pos = glm::vec3(
			player->position.x + 4 * sin(yow * M_PI / 180) * 1.0f,
			player->position.y + 1,
			player->position.z + 4 * cos(yow * M_PI / 180) * 1.0f);


		//�p�x��⊮-----------------------------------------------

		//�v���C���[�ƃG�l�~�[�̊p�x
		float playerToEnemyAngle = 0;
		playerToEnemyAngle = atan2(player->position.x - enemy[player->targetNum].position.x, player->position.z - enemy[player->targetNum].position.z) * 180 / M_PI;

		float cameraRad = yow * (M_PI / 180.f);
		glm::vec3 cameraDirec = glm::vec3(-sin(cameraRad), 0, -cos(cameraRad));
		float targetRad = atan2(pos.x - enemy[player->targetNum].position.x, pos.z - enemy[player->targetNum].position.z);
		glm::vec3 targetDirec = glm::vec3(-sin(targetRad), 0, -cos(targetRad));

		float cameraCross = glm::cross(cameraDirec, targetDirec).y;
		float cameraDot = glm::dot(cameraDirec, targetDirec);

		//�J�����ƃ^�[�Q�b�g�Ƃ̊p�x���T�x���傫���Ƃ�
		if (cameraCross * cameraCross > (5 * M_PI / 180) * (5 * M_PI / 180)) {
			if (cameraCross > 0) {
				yow += 1.f * ((-cameraDot + 1) * 0.5f + 2.0f);
			}
			else {
				yow -= 1.f * ((-cameraDot + 1) * 0.5f + 2.0f);
			}

		}
		else {//�J�����ƃ^�[�Q�b�g�Ƃ̊p�x���T�x��菬�����Ƃ�
			yow = targetRad * 180 / M_PI;

		}

		//�^�[�Q�b�g�ʒu�̕⊮-------------------------------------

		//�G�̋���
		float enemyDistance = 0;
		enemyDistance = enemy[player->targetNum].position.x * enemy[player->targetNum].position.x + enemy[player->targetNum].position.z * enemy[player->targetNum].position.z;

		target.x = pos.x - sin(yow * M_PI / 180) * sqrt(enemyDistance);
		target.y = enemy[player->targetNum].position.y;
		target.z = pos.z - cos(yow * M_PI / 180) * sqrt(enemyDistance);
	}
	else {//���b�N�I�������Ă��Ȃ��Ƃ�
		pos = glm::vec3(
			player->position.x + 3 * sin(yow * M_PI / 180) * 1.0f,
			player->position.y + .5f,
			player->position.z + 3 * cos(yow * M_PI / 180) * 1.0f);

		target = player->shootTarget;
	}


	pos = lastPos + (pos - lastPos) * 0.4f;
	target = lastTarget + (target - lastTarget) * 0.05f;

	gluLookAt(
		pos.x, pos.y, pos.z,
		target.x, target.y, target.z,
		up.x, up.y, up.z);

	lastPos = pos;
	lastTarget = target;
}


////////////////////////////////////////
//�񎟌��̐ݒ�
///////////////////////////////////////
void Camera::plane() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(
		left, right,//GLdouble left,  right,
		bottom, top,//GLdouble bottom,  top, 
		10, -10);//GLdouble zNear,  zFar

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3f(1, 1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


}
