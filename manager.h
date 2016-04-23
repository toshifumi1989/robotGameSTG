#ifndef MANAGER_H
#define MANAGER_H

#include"scene.h"

enum MODE{
	selectNormal,
	selectSurvival
};

class GameManager {
public:

	~GameManager() {}

	void update();//更新

	unsigned char selectScene = 0;//どのシーンなのか

	void sceneTitle(float delta);//シーンタイトル
	void sceneSurvival(float delta);//シーンサバイバルモード
	void sceneNormalMode(float delta);//シーンノーマルモード
	void sceneResult(float delta);//シーンリザルト

	static GameManager* getInstance();

	Scene<GameManager> _scene;

private:
	GameManager() {
		_scene.change(&GameManager::sceneTitle);
	}

	static GameManager* instance;

};



#endif