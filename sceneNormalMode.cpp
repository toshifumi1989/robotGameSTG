#include"sceneNormalMode.h"

///////////////////////////////////////////////
//�����ݒ�
//////////////////////////////////////////////
void NormalMode::init() {
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	field = new Field();
	field->readField("field.bmp");
	field->setup();

	glBindTexture(GL_TEXTURE_2D, textures[1]);
	target = new Texture();
	target->read_alpha("target.bmp");

	glBindTexture(GL_TEXTURE_2D, textures[3]);
	smokeRing = new Texture();
	smokeRing->read_alpha("smoke.bmp");

	glBindTexture(GL_TEXTURE_2D, textures[4]);
	marker = new Texture();
	marker->read_alpha("marker.bmp");

	while (3 > enemy.size()) {
		Enemy soldiers;
		soldiers.actionCount = rand() % 60 - 60;
		soldiers.position.x = rand() % 200 + 28;
		soldiers.position.y = rand() % 5 + 10;
		soldiers.position.z = rand() % 200 + 28;
		soldiers.lastPosition = soldiers.position;
		soldiers.readModel("heri.x");
		enemy.push_back(soldiers);
	}

	player = new Player();
	player->readModel("robo.x");
	player->HP = player->MaxHP;
	player->position = glm::vec3(29, 20, 29);
	player->angle = -135;

	camera->yow = -135;
	camera->target = player->shootTarget;

	glEnable(GL_CULL_FACE);		//�J�����O
	glEnable(GL_DEPTH_TEST);	//�[�x�e�X�g

	readSound("Explosion.wav");


}

////////////////////////////////////////////////
//�X�V
////////////////////////////////////////////////
void NormalMode::update() {

	if (timeMusic() >= 2) {
		stopMusic();
	}

	//�v���C���[--------------------------------------------
	player->controller();
	player->update();

	player->targetMaekerUpdate();

	//�v���C���[�o���b�g
	//���C�t��
	std::list<Bullet>::iterator playerbulletIter = playerBullet.begin();

	while (playerbulletIter != playerBullet.end()) {
		playerbulletIter->update();
		for (int i = 0; i < enemy.size(); i++) {
			playerbulletIter->hitCharacter(&enemy[i]);
		}

		if (playerbulletIter->onFlag == false) {
			playerbulletIter = playerBullet.erase(playerbulletIter);
		}
		else {
			++playerbulletIter;
		}
	}

	//�V���b�g�K��
	std::list<Bullet>::iterator machineGunIter = machineGun.begin();

	while (machineGunIter != machineGun.end()) {
		machineGunIter->update();
		machineGunIter->onCount++;
		for (int i = 0; i < enemy.size(); i++) {
			machineGunIter->hitCharacter(&enemy[i]);
		}

		if (machineGunIter->onFlag == false ||
			machineGunIter->onCount == 60) {
			machineGunIter = machineGun.erase(machineGunIter);
		}
		else {
			++machineGunIter;
		}
	}

	//�G�l�~�[----------------------------------------------

	for (int i = 0; i < enemy.size(); i++) {
		enemy[i].update();
		enemy[i].action();
	}

	std::list<Bullet>::iterator enemybulletIter = enemyBullet.begin();

	while (enemybulletIter != enemyBullet.end()) {

		enemybulletIter->update();
		enemybulletIter->hitCharacter(player);

		if (enemybulletIter->onFlag == false) {
			enemybulletIter = enemyBullet.erase(enemybulletIter);
		}
		else {
			++enemybulletIter;
		}
	}

	//�G�l�~�[���j��-----------------------------------------

	for (auto enemyIter = enemy.begin();
	enemyIter != enemy.end();) {
		if (enemyIter->HP <= 0) {

			playMusic();

			if (player->targetFlag == true) {

				int nextTargetNum = -1;
				float nextTarget = FLT_MIN;

				//���݂̃^�[�Q�b�g
				auto playerToTarget = enemy[player->targetNum].position - player->position;
				playerToTarget.y = 0;
				glm::vec3 playerDirec = glm::normalize(playerToTarget);
				float enemyToPlayer = 0;

				for (int i = 0; i < enemy.size(); i++) {

					//�G�̃^�[�Q�b�g�؂�ւ��̂��߂̌v�Z
					if (player->targetNum != i) {

						//�����������ꍇtarget����O��
						enemyToPlayer = (player->position.x - enemy[i].position.x) * (player->position.z - enemy[i].position.z);

						if (enemyToPlayer <= 10000) {
							//���݂̃^�[�Q�b�g�̑�
							auto playerToAnother = enemy[i].position - player->position;
							playerToAnother.y = 0;
							glm::vec3 enemyDirec = glm::normalize(playerToAnother);

							//�O�ςƓ��ςŎ��̃^�[�Q�b�g���v�Z
							float enemyDot = glm::dot(playerDirec, enemyDirec);

							if (nextTarget < enemyDot) {
								nextTarget = enemyDot;
								nextTargetNum = i;
							}
						}
					}
				}


				if (nextTargetNum == -1) {
					player->targetFlag = false;
				}
				else if (player->targetNum > nextTargetNum) {
					player->targetNum = nextTargetNum;
				}
				else {
					//���̃^�[�Q�b�g�i���o�[���C���[�X����邽��
					//�P����邱�Ƃ��C��
					player->targetNum = nextTargetNum - 1;
				}
			}

		}
		++enemyIter;
	}

	//���ʃG�t�F�N�g--------------------------------------------------
	//�_���[�W
	std::list<Effect>::iterator damageIter = damage.begin();

	for (int i = 0; i < damage.size(); i++) {

		damageIter->drawCount++;

		if (damageIter->drawCount == 20) {
			damageIter = damage.erase(damageIter);
		}
		else {
			damageIter->update();
			++damageIter;
		}
	}

	//����(���Ɖ�------------------------------------------------------
	std::list<Explotion>::iterator explotionIter = explotion.begin();

	while (explotionIter != explotion.end()) {
		if (explotionIter->smoke.size() == 0 && explotionIter->fire.size() == 0) {
			explotionIter = explotion.erase(explotionIter);
		}
		else {
			++explotionIter;
		}
	}

	//�G�̏��Ŕ���--------------------------------------------------

	for (auto enemyIter = enemy.begin();
	enemyIter != enemy.end();) {
		if (enemyIter->HP <= 0) {

			player->scorePoint += 10;

			Explotion burst;
			burst.position = enemyIter->position;
			burst.initExplotion();
			explotion.push_back(burst);

			enemyIter = enemy.erase(enemyIter);
		}
		else {
			++enemyIter;
		}
	}



}

//////////////////////////////////////////
//�`��
//////////////////////////////////////////
void NormalMode::draw() {
	glColor3f(1, 1, 1);		//�F�̏�����
	glClearColor(0, 0.39f, 1, 0.5f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//�J����--------------------------------------------------------
	camera->update();
	camera->move();

	//�t�B�[���h----------------------------------------------------
	field->drawField();

	//�v���C���[------------------------------------------------------
	player->draw();
	player->drawDust();
	player->targetMaekerDraw();

	//���C�t��
	std::list<Bullet>::iterator playerbulletIter = playerBullet.begin();
	while (playerbulletIter != playerBullet.end()) {
		playerbulletIter->draw();
		++playerbulletIter;
	}

	//�V���b�g�K��
	std::list<Bullet>::iterator machineGunIter = machineGun.begin();
	while (machineGunIter != machineGun.end()) {
		machineGunIter->draw();
		++machineGunIter;
	}

	//�G�l�~�[--------------------------------------------------------
	for (int i = 0; i < enemy.size(); i++) {
		enemy[i].draw(i);
	}

	//�U��
	std::list<Bullet>::iterator enemybulletIter = enemyBullet.begin();
	while (enemybulletIter != enemyBullet.end()) {
		enemybulletIter->draw();
		++enemybulletIter;
	}

	//�_���[�W�G�t�F�N�g---------------------------------------------

	std::list<Effect>::iterator damageIter = damage.begin();

	while (damageIter != damage.end()) {
		damageIter->draw();
		++damageIter;
	}

	//�����G�t�F�N�g--------------------------------------------------

	std::list<Explotion>::iterator explotionIter = explotion.begin();

	while (explotionIter != explotion.end()) {
		explotionIter->drawExplotion();
		++explotionIter;
	}

	//���ˉe�i�QD�j�`��-----------------------------------------------
	camera->plane();
	player->show();
}