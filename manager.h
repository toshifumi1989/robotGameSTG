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

	void update();//�X�V

	unsigned char selectScene = 0;//�ǂ̃V�[���Ȃ̂�

	void sceneTitle(float delta);//�V�[���^�C�g��
	void sceneSurvival(float delta);//�V�[���T�o�C�o�����[�h
	void sceneNormalMode(float delta);//�V�[���m�[�}�����[�h
	void sceneResult(float delta);//�V�[�����U���g

	static GameManager* getInstance();

	Scene<GameManager> _scene;

private:
	GameManager() {
		_scene.change(&GameManager::sceneTitle);
	}

	static GameManager* instance;

};



#endif