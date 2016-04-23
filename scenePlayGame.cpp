#include"scenePlayGame.h"


Field *field;
Player *player;
Texture *target;
Texture *smokeRing;
Texture *marker;
extern Camera *camera;
std::vector<Enemy> enemy;
extern std::list<Bullet>playerBullet;
extern std::list<Bullet>machineGun;
std::list<Bullet> enemyBullet;
std::list<Effect>damage;
std::list<Explotion>explotion;
extern GLuint textures[7];


void PlayGame::init() {
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

	while (10 > enemy.size()) {
		Enemy soldiers;
		soldiers.actionFlag = rand() % 60 - 60;
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

	glEnable(GL_CULL_FACE);		//カリング
	glEnable(GL_DEPTH_TEST);	//深度テスト

}


void PlayGame::update() {

	camera->update();

	camera->move();

	player->controller();

	//player->keyboard();

	glColor3f(1, 1, 1);		//色の初期化

	glClearColor(0, 0.39f, 1, 0.5f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	field->drawField();
	//プレイヤー--------------------------------------------

	player->update();

	player->draw();

	if (player->junpFlag == false) {
		glPushMatrix();
		{
			glDisable(GL_CULL_FACE);
			glDepthMask(GL_FALSE);

			player->drawDust();
			glDisable(GL_TEXTURE_2D);
			glEnable(GL_CULL_FACE);
			glDepthMask(GL_TRUE);
			glDisable(GL_BLEND);
		}
		glPopMatrix();
	}


	player->targetMaeker();

	//プレイヤーバレット
	//ライフル
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
			playerbulletIter->draw();
			++playerbulletIter;
		}
	}


	//マシンガン
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
			machineGunIter->draw();
			++machineGunIter;
		}
	}

	//エネミー----------------------------------------------

	for (int i = 0; i < enemy.size(); i++) {
		enemy[i].update();
		enemy[i].action();
		enemy[i].draw(i);
	}


	std::list<Bullet>::iterator enemybulletIter = enemyBullet.begin();

	while (enemybulletIter != enemyBullet.end()) {

		enemybulletIter->update();
		enemybulletIter->hitCharacter(player);

		if (enemybulletIter->onFlag == false) {
			enemybulletIter = enemyBullet.erase(enemybulletIter);
		}
		else {
			enemybulletIter->draw();
			++enemybulletIter;
		}
	}

	//エネミーリポップ-----------------------------------------

	for (auto enemyIter = enemy.begin();
	enemyIter != enemy.end();) {
		if (enemyIter->HP <= 0) {

			if (player->targetFlag == true) {

				int nextTargetNum = -1;
				float nextTarget = FLT_MIN;

				//現在のターゲット
				auto playerToTarget = enemy[player->targetNum].position - player->position;
				playerToTarget.y = 0;
				glm::vec3 playerDirec = glm::normalize(playerToTarget);
				float enemyToPlayer = 0;

				for (int i = 0; i < enemy.size(); i++) {

					//敵のターゲット切り替えのための計算
					if (player->targetNum != i) {

						//距離が遠い場合targetから外す
						enemyToPlayer = (player->position.x - enemy[i].position.x) * (player->position.z - enemy[i].position.z);

						if (enemyToPlayer <= 10000) {
							//現在のターゲットの他
							auto playerToAnother = enemy[i].position - player->position;
							playerToAnother.y = 0;
							glm::vec3 enemyDirec = glm::normalize(playerToAnother);

							//外積と内積で次のターゲットを計算
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
					//今のターゲットナンバーがイレースされるため
					//１つずれることを修正
					player->targetNum = nextTargetNum - 1;
				}


			}


			Enemy soldiers;
			soldiers.actionFlag = rand() % 60;
			soldiers.position.x = rand() % 200 + 28;
			soldiers.position.y = rand() % 5 + 10;
			soldiers.position.z = rand() % 200 + 28;
			soldiers.lastPosition = soldiers.position;
			soldiers.readModel("heri.x");
			enemy.push_back(soldiers);


		}
		++enemyIter;
	}

	//共通エフェクト--------------------------------------------------
	//ダメージ
	std::list<Effect>::iterator damageIter = damage.begin();

	for (int i = 0; i < damage.size(); i++) {

		damageIter->drawCount++;

		if (damageIter->drawCount == 20) {
			damageIter = damage.erase(damageIter);
		}
		else {
			damageIter->update();
			damageIter->draw();
			++damageIter;
		}
	}

	//爆発(炎と煙------------------------------------------------------
	std::list<Explotion>::iterator explotionIter = explotion.begin();

	while (explotionIter != explotion.end()) {
		explotionIter->drawExplotion();

		if (explotionIter->smoke.size() == 0 && explotionIter->fire.size() == 0) {
			explotionIter = explotion.erase(explotionIter);
		}
		else {
			++explotionIter;
		}

	}



	//敵の消滅判定--------------------------------------------------

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

	//正射影（２D）描画-----------------------------------------------
	camera->plane();
	player->show();


}