
#include<stdio.h>
#include<stdlib.h>
#include"glut.h"
#include"library\Xinput.h"

#include"manager.h"
#include"library\camera.h"

#pragma comment(lib, "glut32.lib")


// �֐��v���g�^�C�v�i��ɌĂяo���֐����ƈ����̐錾�j
void init(void);
void display(void);
void timer(int value);
void keyboard(unsigned char key, int x, int y);
void keyboardUp(unsigned char key, int x, int y);

CONTROLER_STATE joystic;

unsigned char keys[256] = {};
extern GLuint textures[7];

//////////////////////////////////////////////////
//���C���֐�
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
//�L�[�{�[�h��ON�AOFF
//////////////////////////////////////////////////
void keyboard(unsigned char key, int x, int y) {
	keys[key] = 1;
}
void keyboardUp(unsigned char key, int x, int y) {
	keys[key] = 0;
}

//////////////////////////////////////////////
//�^�C�}�[
//////////////////////////////////////////////
void timer(int value) {

	glutPostRedisplay();

	// 1000�~���b�� 1 �b
	glutTimerFunc(1000 / 60, timer, 0);
}

/////////////////////////////////////////
//�����ݒ�
/////////////////////////////////////////
void init(void) {
	glGenTextures(7, textures);

}

///////////////////////////////////////
//�`��
////////////////////////////////////////
void display(void) {
	joystic.GetState(0);

	GameManager::getInstance()->update();

	glFlush();
}