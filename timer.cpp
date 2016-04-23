#include <stdio.h>

#include"timer.h"
#include"../glut.h"

void Timer::update() {

	count += 100 / 60;

	ms = (int)count % 100;
	second = count / 100;
	minute = second / 60;

}

//void Timer::draw() {
//	glDisable(GL_CULL_FACE);
//	glDisable(GL_DEPTH_TEST);
//
//	glPushMatrix();
//	{
//
//		char score[] = "Score : ";
//		glTranslatef(350, 500, 0);
//		glScalef(2, 2, 0);
//		glLineWidth(3);
//		for (int i = 0; score[i] != 0; i++) {
//			glutStrokeCharacter(
//				GLUT_STROKE_ROMAN,			//void *font,int
//				score[i]);						//character
//		}
//
//
//		char point[6];
//		sprintf_s(point, "%d", player->scorePoint);
//		glScalef(1.5f, 1.5f, 0);
//		glLineWidth(3);
//		for (int i = 0; point[i] != 0; i++) {
//			glutStrokeCharacter(
//				GLUT_STROKE_ROMAN,			//void *font,int
//				point[i]);						//character
//		}
//
//	}
//	glPopMatrix();
//
//	glEnable(GL_CULL_FACE);
//	glEnable(GL_DEPTH_TEST);
//
//}