#include"sceneTittle.h"
#include"library\camera.h"

extern Camera *camera;
extern GLuint textures[7];
Texture *opening;
Texture *name;
Texture *modeSelect;
extern unsigned char keys[256];

//////////////////////////////////
//初期設定
//////////////////////////////////
void SceneTitle::init() {
	glBindTexture(GL_TEXTURE_2D, textures[2]);
	opening = new Texture();
	opening->read("title.bmp");
	glBindTexture(GL_TEXTURE_2D, textures[5]);
	name = new Texture();
	name->read_alpha("name.bmp");
	glBindTexture(GL_TEXTURE_2D, textures[6]);
	modeSelect = new Texture();
	modeSelect->read("select.bmp");
}

///////////////////////////////////
//更新
//////////////////////////////////
void SceneTitle::update() {
	const WORD pressedKeys = joystic.state.Gamepad.wButtons;					//押しているボタン
	const WORD releasedKeys = ~joystic.state.Gamepad.wButtons;				//離れたボタン
	const WORD changedKeys = joystic.lastkeys ^ pressedKeys;		//切り替わったボタン
	const WORD downKeys = changedKeys & pressedKeys;		//今押したボタン
	const WORD upKeys = changedKeys & releasedKeys;

	joystic.upKeys();
	joystic.downKeys();

	glColor3f(1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	camera->update();
	camera->plane();

	//タイトル画面--------------------------------------------------------------

	wordCount++;

	if (change == start) {
		glBindTexture(GL_TEXTURE_2D, textures[2]);
		glEnable(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glPushMatrix();
		{
			glBegin(GL_QUADS);
			{
				glTexCoord2d(0, 1);
				glVertex3d(0, 0, 0);
				glTexCoord2d(1, 1);
				glVertex3d(5000, 0, 0);
				glTexCoord2d(1, 0);
				glVertex3d(5000, 5000, 0);
				glTexCoord2d(0, 0);
				glVertex3d(0, 5000, 0);
			}
			glEnd();
		}

		glPopMatrix();
		if (moveSelect == false) {
			if (wordCount % 60 < 40) {
				glPushMatrix();
				{
					glDisable(GL_TEXTURE_2D);
					char start[] = " Please Push Start";
					glTranslatef(1200, 1300, 0);
					glScalef(2, 2, 0);
					glLineWidth(4);
					for (int i = 0; start[i] != 0; i++) {
						glutStrokeCharacter(
							GLUT_STROKE_ROMAN,			//void *font,int
							start[i]);						//character
					}
					glEnable(GL_TEXTURE_2D);
				}
				glPopMatrix();

			}
		}


		if ((downKeys & XINPUT_GAMEPAD_START)) {
			if (moveSelect == false) {
				wordCount = 0;
				moveSelect = true;
			}
		}
		else if (keys[' '] == 1) {
			wordCount = 0;
			moveSelect = true;
		}

		if (moveSelect == true) {
			camera->left += 10;
			camera->right -= 10;
			camera->bottom += 10;
			camera->top -= 10;
			mask += 1 / 60.f;

		}

		if (wordCount == 60 && moveSelect == true) {
			camera->left = 0;
			camera->right = 5000;
			camera->bottom = 0;
			camera->top = 5000;
			change = modeNormal;
		}

		if (moveSelect == false) {
			glBindTexture(GL_TEXTURE_2D, textures[5]);
			glEnable(GL_TEXTURE_2D);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


			glDisable(GL_CULL_FACE);
			glDisable(GL_DEPTH_TEST);

			glEnable(GL_BLEND);
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

			glBlendFunc(
				GL_SRC_ALPHA,           // GLenum sfactor
				GL_ONE_MINUS_SRC_ALPHA);// GLenum dfactor

			glTranslatef(150, 0, 0);

			glBegin(GL_QUADS);
			{
				glTexCoord2d(0, 1);
				glVertex3d(0, 0, 0);
				glTexCoord2d(1, 1);
				glVertex3d(5000, 0, 0);
				glTexCoord2d(1, 0);
				glVertex3d(5000, 5000, 0);
				glTexCoord2d(0, 0);
				glVertex3d(0, 5000, 0);
			}
			glEnd();
		}
		else {
			glDisable(GL_CULL_FACE);
			glDisable(GL_DEPTH_TEST);

			glEnable(GL_BLEND);
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

			glBlendFunc(
				GL_SRC_ALPHA,           // GLenum sfactor
				GL_ONE_MINUS_SRC_ALPHA);// GLenum dfacto

			glColor4f(0, 0, 0, mask);
			glBegin(GL_QUADS);
			{
				glVertex3d(0, 0, 0);
				glVertex3d(5000, 0, 0);
				glVertex3d(5000, 5000, 0);
				glVertex3d(0, 5000, 0);
			}
			glEnd();
		}


	}
	else {
		//選択画面------------------------------------------------------------------
		glBindTexture(GL_TEXTURE_2D, textures[6]);
		glEnable(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


		//背景画像-----------------------------------------------------
		glBegin(GL_QUADS);
		{
			glTexCoord2d(0, 1);
			glVertex3d(0, 0, 0);
			glTexCoord2d(1, 1);
			glVertex3d(5000, 0, 0);
			glTexCoord2d(1, 0);
			glVertex3d(5000, 5000, 0);
			glTexCoord2d(0, 0);
			glVertex3d(0, 5000, 0);
		}
		glEnd();

		if (joystic.upKeysFlag == true) {
			if (change == modeNormal) {
				change = modeSurvival;
			}
			else {
				change = modeNormal;
			}
		}
		else if (joystic.downKeysFlag == true) {
			if (change == modeNormal) {
				change = modeSurvival;
			}
			else {
				change = modeNormal;
			}
		}

		glPushMatrix();
		{
			glDisable(GL_TEXTURE_2D);
			char start[] = "[A] : select";
			glTranslatef(1750, 1000, 0);
			glScalef(1.5f, 1.5f, 0);
			glLineWidth(2);
			for (int i = 0; start[i] != 0; i++) {
				glutStrokeCharacter(
					GLUT_STROKE_ROMAN,			//void *font,int
					start[i]);						//character
			}
			glEnable(GL_TEXTURE_2D);
		}
		glPopMatrix();

		if (change == modeNormal) {
			//ノーマルモード選択時----------------------------------
			if (wordCount % 40 < 30) {
				glPushMatrix();
				{
					glDisable(GL_TEXTURE_2D);
					glColor3f(1, 1, 1);
					char playMode[] = " Normal Mode";
					glTranslatef(1100, 2000, 0);
					glScalef(2.5f, 2.5f, 0);
					glLineWidth(4);
					for (int i = 0; playMode[i] != 0; i++) {
						glutStrokeCharacter(
							GLUT_STROKE_ROMAN,			//void *font,int
							playMode[i]);						//character
					}
					glEnable(GL_TEXTURE_2D);
				}
				glPopMatrix();
			}

			glPushMatrix();
			{
				glDisable(GL_TEXTURE_2D);
				glColor3f(1, 1, 1);
				char playMode[] = " Survival Mode";
				glTranslatef(1100, 1500, 0);
				glScalef(2.5f, 2.5f, 0);
				glLineWidth(4);
				for (int i = 0; playMode[i] != 0; i++) {
					glutStrokeCharacter(
						GLUT_STROKE_ROMAN,			//void *font,int
						playMode[i]);						//character
				}
				glEnable(GL_TEXTURE_2D);
			}
			glPopMatrix();


		}
		if (change == modeSurvival) {
			//サバイバルモード選択時----------------------------------------
			glPushMatrix();
			{
				glDisable(GL_TEXTURE_2D);
				glColor3f(1, 1, 1);
				char playMode[] = " Normal Mode";
				glTranslatef(1100, 2000, 0);
				glScalef(2.5f, 2.5f, 0);
				glLineWidth(4);
				for (int i = 0; playMode[i] != 0; i++) {
					glutStrokeCharacter(
						GLUT_STROKE_ROMAN,			//void *font,int
						playMode[i]);						//character
				}
				glEnable(GL_TEXTURE_2D);
			}
			glPopMatrix();


			if (wordCount % 40 < 30) {
				glPushMatrix();
				{
					glDisable(GL_TEXTURE_2D);
					glColor3f(1, 1, 1);
					char playMode[] = " Survival Mode";
					glTranslatef(1100, 1500, 0);
					glScalef(2.5f, 2.5f, 0);
					glLineWidth(4);
					for (int i = 0; playMode[i] != 0; i++) {
						glutStrokeCharacter(
							GLUT_STROKE_ROMAN,			//void *font,int
							playMode[i]);						//character
					}
					glEnable(GL_TEXTURE_2D);
				}
				glPopMatrix();
			}
		}


		if ((downKeys & XINPUT_GAMEPAD_START) || (downKeys & XINPUT_GAMEPAD_A)) {
			wordCount = 0;
			sceneMove = true;
		}
		else if (keys[' '] == 1) {
			wordCount = 0;
			sceneMove = true;
		}
	}

	joystic.lastkeys = joystic.state.Gamepad.wButtons;
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}