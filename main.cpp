
#include<stdio.h>
#include<stdlib.h>
#include"glut.h"
#include"library\Xinput.h"

#include"manager.h"
#include"library\camera.h"

#pragma comment(lib, "glut32.lib")


// 関数プロトタイプ（後に呼び出す関数名と引数の宣言）
void init(void);
void display(void);
void timer(int value);
void keyboard(unsigned char key, int x, int y);
void keyboardUp(unsigned char key, int x, int y);

CONTROLER_STATE joystic;

unsigned char keys[256] = {};
extern GLuint textures[7];

//////////////////////////////////////////////////
//メイン関数
//////////////////////////////////////////////////
int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitWindowSize(1000, 700);
	glutCreateWindow("game");

	glutDisplayFunc(display);
	glutTimerFunc(0, timer, 0);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);
	glutIgnoreKeyRepeat(GL_TRUE);

	init();
	glutMainLoop();
}

//////////////////////////////////////////////////
//キーボードのON、OFF
//////////////////////////////////////////////////
void keyboard(unsigned char key, int x, int y) {
	keys[key] = 1;
}
void keyboardUp(unsigned char key, int x, int y) {
	keys[key] = 0;
}

//////////////////////////////////////////////
//タイマー
//////////////////////////////////////////////
void timer(int value) {

	glutPostRedisplay();

	// 1000ミリ秒で 1 秒
	glutTimerFunc(1000 / 60, timer, 0);
}

/////////////////////////////////////////
//初期設定
/////////////////////////////////////////
void init(void) {
	glGenTextures(7, textures);

}

///////////////////////////////////////
//描画
////////////////////////////////////////
void display(void) {
	joystic.GetState(0);

	GameManager::getInstance()->update();

	glFlush();
}