#include <stdio.h>

#include"manager.h"
#include"sceneSurvival.h"
#include"sceneTittle.h"
#include"sceneResult.h"
#include"sceneNormalMode.h"

GLuint textures[7];
Survival *survival;
NormalMode *normalMode;
SceneTitle *title;
Result *result;
Camera *camera;

GameManager* GameManager::instance = nullptr;

//////////////////////////////////////
//インスタンス
//////////////////////////////////////
GameManager* GameManager::getInstance() {
	if (nullptr == instance) {
		instance = new GameManager();
		
	}
	return instance;
}

////////////////////////////////////////////
//マネージャの更新
////////////////////////////////////////////
void GameManager::update() {
	_scene.run(this, 1.0f / 60.0f);
}

///////////////////////////////////////////
//タイトルシーン
///////////////////////////////////////////
void GameManager::sceneTitle(float delta) {
	if (0.0f == _scene.getTime()) {	
		camera = new Camera();		
		title = new SceneTitle();
		title->init();
	}

 	title->update();

	if (title->sceneMove == true && title->change == modeNormal) {
		title->sceneMove = false;
		_scene.change(&GameManager::sceneNormalMode);
		selectScene = selectNormal;
		delete title;
	}
	else if (title->sceneMove == true && title->change == modeSurvival) {
		title->sceneMove = false;
		_scene.change(&GameManager::sceneSurvival);
		selectScene = selectSurvival;
		delete title;
	}
	else {

	}
}

///////////////////////////////////////////////////
//ノーマルモードのシーン
///////////////////////////////////////////////////
void GameManager::sceneNormalMode(float delta) {
	if (0.0f == _scene.getTime()) {
		normalMode = new NormalMode();
		normalMode->init();
	}

	normalMode->update();
	normalMode->draw();

	if (player->HP <= 0 || enemy.size() == 0) {
		_scene.change(&GameManager::sceneResult);
		damage.clear();
		delete normalMode;
	}
}

//////////////////////////////////////////////
//サバイバルモードのシーン
//////////////////////////////////////////////
void GameManager::sceneSurvival(float delta) {
	if (0.0f == _scene.getTime()) {
		survival = new Survival();
		survival->init();	
	}

	survival->update();
	survival->draw();

	if (player->HP <= 0) {
		_scene.change(&GameManager::sceneResult);
		damage.clear();
		delete survival;
	}
}

///////////////////////////////////////////////
//リザルトのシーン
///////////////////////////////////////////////
void GameManager::sceneResult(float delta) {
	if (0.0f == _scene.getTime()) {
		result = new Result();
		result->sceneInit();
	}

	result->sceneUpdate();

	if (result->sceneMove == true) {

		_scene.change(&GameManager::sceneTitle);

		deleteMusic();
		delete result;
		delete camera;
		delete player;		
		delete field;
		delete target;
		delete smokeRing;
		enemy.clear();
		explotion.clear();
		enemyBullet.clear();
		playerBullet.clear();
	}

}


