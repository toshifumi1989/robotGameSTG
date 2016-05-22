#include"sceneNormalMode.h"

///////////////////////////////////////////////
//初期設定
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

	glEnable(GL_CULL_FACE);		//カリング
	glEnable(GL_DEPTH_TEST);	//深度テスト

	readSound("Explosion.wav");


}

////////////////////////////////////////////////
//更新
////////////////////////////////////////////////
void NormalMode::update() {

	if (timeMusic() >= 2) {
		stopMusic();
	}

	//プレイヤー--------------------------------------------
	player->controller();
	player->update();

	player->targetMaekerUpdate();

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
			++playerbulletIter;
		}
	}

	//ショットガン
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

	//エネミー----------------------------------------------

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

	//エネミー撃破時-----------------------------------------

	for (auto enemyIter = enemy.begin();
	enemyIter != enemy.end();) {
		if (enemyIter->HP <= 0) {

			playMusic();

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
			++damageIter;
		}
	}

	//爆発(炎と煙------------------------------------------------------
	std::list<Explotion>::iterator explotionIter = explotion.begin();

	while (explotionIter != explotion.end()) {
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



}

//////////////////////////////////////////
//描画
//////////////////////////////////////////
void NormalMode::draw() {
	glColor3f(1, 1, 1);		//色の初期化
	glClearColor(0, 0.39f, 1, 0.5f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//カメラ--------------------------------------------------------
	camera->update();
	camera->move();

	//フィールド----------------------------------------------------
	field->drawField();

	//プレイヤー------------------------------------------------------
	player->draw();
	player->drawDust();
	player->targetMaekerDraw();

	//ライフル
	std::list<Bullet>::iterator playerbulletIter = playerBullet.begin();
	while (playerbulletIter != playerBullet.end()) {
		playerbulletIter->draw();
		++playerbulletIter;
	}

	//ショットガン
	std::list<Bullet>::iterator machineGunIter = machineGun.begin();
	while (machineGunIter != machineGun.end()) {
		machineGunIter->draw();
		++machineGunIter;
	}

	//エネミー--------------------------------------------------------
	for (int i = 0; i < enemy.size(); i++) {
		enemy[i].draw(i);
	}

	//攻撃
	std::list<Bullet>::iterator enemybulletIter = enemyBullet.begin();
	while (enemybulletIter != enemyBullet.end()) {
		enemybulletIter->draw();
		++enemybulletIter;
	}

	//ダメージエフェクト---------------------------------------------

	std::list<Effect>::iterator damageIter = damage.begin();

	while (damageIter != damage.end()) {
		damageIter->draw();
		++damageIter;
	}

	//爆発エフェクト--------------------------------------------------

	std::list<Explotion>::iterator explotionIter = explotion.begin();

	while (explotionIter != explotion.end()) {
		explotionIter->drawExplotion();
		++explotionIter;
	}

	//正射影（２D）描画-----------------------------------------------
	camera->plane();
	player->show();
}