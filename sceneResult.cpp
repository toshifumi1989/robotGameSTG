#include"sceneResult.h"
#include"manager.h"
#include"library\player.h"
#include"library\camera.h"
#include"library\explotion.h"
#include"library\texture.h"
#include"library\field.h"

extern unsigned char keys[256];

//////////////////////////////////////
//初期設定
///////////////////////////////////////
void Result::sceneInit() {
	if (player->HP <= 0) {
		Explotion playerBurst;
		playerBurst.position = player->position;
		playerBurst.initExplotion();
		explotion.push_back(playerBurst);
	}

}

/////////////////////////////////////////
//更新
////////////////////////////////////////
void Result::sceneUpdate() {
	const WORD pressedKeys = joystic.state.Gamepad.wButtons;					//押しているボタン
	const WORD releasedKeys = ~joystic.state.Gamepad.wButtons;				//離れたボタン
	const WORD changedKeys = joystic.lastkeys ^ pressedKeys;		//切り替わったボタン
	const WORD downKeys = changedKeys & pressedKeys;		//今押したボタン
	const WORD upKeys = changedKeys & releasedKeys;

	glColor3f(1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (timeMusic() >= 2) {
		stopMusic();
	}

	camera->yow -= 0.01f;
	camera->update();

	gluLookAt(
		player->position.x + 4 * sin(camera->yow), player->position.y + 2, player->position.z + 4 * cos(camera->yow),
		player->position.x, player->position.y, player->position.z,
		0, 1, 0);

	field->drawField();

	player->update();

	if (player->HP > 0) {
		player->draw();
	}
	else {
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
	}


	//文字------------------------------------

	camera->plane();
	wordCount++;

	if (GameManager::getInstance()->selectScene == selectSurvival) {
		glPushMatrix();
		{

			char score[] = "Score : ";
			glTranslatef(1650, 2900, 0);
			glScalef(2, 2, 0);
			glLineWidth(3);
			for (int i = 0; score[i] != 0; i++) {
				glutStrokeCharacter(
					GLUT_STROKE_ROMAN,			//void *font,int
					score[i]);						//character
			}


			char point[6];
			sprintf_s(point, "%d", player->scorePoint);
			glScalef(1.5f, 1.5f, 0);
			glLineWidth(3);
			for (int i = 0; point[i] != 0; i++) {
				glutStrokeCharacter(
					GLUT_STROKE_ROMAN,			//void *font,int
					point[i]);						//character
			}

		}
		glPopMatrix();
	}
	else {

		if (player->HP > 0) {
			glPushMatrix();
			{
				char Congratulations[] = " Mission Complete!!";
				glTranslatef(700, 2900, 0);
				glScalef(3, 3, 0);
				glLineWidth(3);
				for (int i = 0; Congratulations[i] != 0; i++) {
					glutStrokeCharacter(
						GLUT_STROKE_ROMAN,			//void *font,int
						Congratulations[i]);						//character
				}
			}
			glPopMatrix();

			glPushMatrix();
			{
				char clear[] = " Game Clear!!";
				glTranslatef(950, 2300, 0);
				glScalef(3, 3, 0);
				glLineWidth(3);
				for (int i = 0; clear[i] != 0; i++) {
					glutStrokeCharacter(
						GLUT_STROKE_ROMAN,			//void *font,int
						clear[i]);						//character
				}
			}
			glPopMatrix();
		}
		else {
			glPushMatrix();
			{
				char  failure[] = "Game Over";
				glTranslatef(1350, 2900, 0);
				glScalef(3, 3, 0);
				glLineWidth(5);
				for (int i = 0; failure[i] != 0; i++) {
					glutStrokeCharacter(
						GLUT_STROKE_ROMAN,			//void *font,int
						failure[i]);						//character
				}
			}
			glPopMatrix();
		}


	}


	if (wordCount < 40) {
		glPushMatrix();
		{
			char start[] = " Please Push Start";
			glTranslatef(1100, 1300, 0);
			glScalef(2, 2, 0);
			glLineWidth(4);
			for (int i = 0; start[i] != 0; i++) {
				glutStrokeCharacter(
					GLUT_STROKE_ROMAN,			//void *font,int
					start[i]);						//character
			}
		}
		glPopMatrix();

	}
	else if (wordCount >= 60) {
		wordCount = 0;
	}

	if (downKeys & XINPUT_GAMEPAD_START) {
		sceneMove = true;
	}
	if (keys[' '] == 1) {
		sceneMove = true;
	}

	joystic.lastkeys = joystic.state.Gamepad.wButtons;

}