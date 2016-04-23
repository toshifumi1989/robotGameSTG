#define _CRT_SECURE_NO_WARNINGS

#include<time.h>
#include"explotion.h"
extern GLuint textures[7];

//////////////////////////////////
//爆発エフェクト初期設定
//////////////////////////////////
void Explotion::initExplotion() {
	srand(time(NULL));
	for (int i = 0; i < 7; i++) {
		//炎エフェクト--------------------------------------------
		Effect fireDefault;

		//アルファ値の初期値
		fireDefault.alpha = 1.1f - rand() % 3 / 10.f;
		//アルファ値減少量
		fireDefault.alphaSpeed = 0.03 + rand() % 2 / 100.f;

		//炎の初期位置
		float fireInitPosX = rand() % 10 / 10.f - 0.5f;	//x座標
		float fireInitPosY = rand() % 10 / 10.f - 0.5f;	//y
		float fireInitPosZ = rand() % 10 / 10.f - 0.5f;	//z
		fireDefault.position = glm::vec3(fireInitPosX, fireInitPosY, fireInitPosZ);

		//炎の初期の大きさ
		float fireInitSclX = rand() % 4 / 2000.f;	//x座標
		float fireInitSclY = rand() % 4 / 2000.f;	//y
		float fireInitSclZ = rand() % 4 / 2000.f;	//z
		fireDefault.scale =  glm::vec3(fireInitSclX, fireInitSclY, fireInitSclZ);

		//炎の移動はなし
		float firePosSpeedX = 0;	//x座標
		float firePosSpeedY = 0;	//y
		float firePosSpeedZ = 0;	//z
		fireDefault.speed = glm::vec3(firePosSpeedX, firePosSpeedY, firePosSpeedZ);

		//炎の大きさ変更
		float fireSclSpeedX = 0.1f + rand() % 20 / 500.f;	//x座標
		float fireSclSpeedY = 0.1f + rand() % 20 / 500.f;	//y
		float fireSclSpeedZ = 0.1f + rand() % 20 / 500.f;	//z
		fireDefault.sclSpeed = glm::vec3(fireSclSpeedX, fireSclSpeedY, fireSclSpeedZ);

		fire.push_back(fireDefault);
	}
	for (int i = 0; i < 10; i++) {
		//煙エフェクト---------------------------------------------
		Effect smk;

		//アルファ値の初期値と減少量
		smk.alpha = 1.0f - rand() % 3 / 10.f;
		smk.alphaSpeed = 0.01f + rand() % 3 / 1000.f;

		//煙の初期位置
		float smkInitPosX = rand() % 10 / 10.f - 0.5f;	//x座標
		float smkInitPosY = rand() % 10 / 10.f - 0.5f;	//y
		float smkInitPosZ = rand() % 10 / 10.f - 0.5f;	//z
		smk.position = glm::vec3(smkInitPosX, smkInitPosY, smkInitPosZ);

		//煙の初期の大きさ
		float smkInitSclX = rand() % 10 / 5;	//x座標
		float smkInitSclY = rand() % 10 / 5;	//y
		float smkInitSclZ = rand() % 10 / 5;	//z
		smk.scale = glm::vec3(smkInitSclX, smkInitSclX, smkInitSclX);

		//煙の移動はやさ
		float smkPosSpeedX = (-0.5f + rand() % 10 / 10.f) / 50.f;	//x座標
		float smkPosSpeedY = 0.004f + rand() % 2 / 1000.f;			//y
		float smkPosSpeedZ = (-0.5f + rand() % 10 / 10.f) / 50.f;	//z

		smk.speed = glm::vec3(smkPosSpeedX, smkPosSpeedY, smkPosSpeedZ);

		//煙の大きさ
		smk.sclSpeed.x = 0.05f + rand() % 5 / 1000.f;
		smk.sclSpeed.y = 0.05f + rand() % 5 / 1000.f;
		smk.sclSpeed.z = 0.05f + rand() % 5 / 1000.f;

		smoke.push_back(smk);
	}

}


////////////////////////////////////////////////
//爆発エフェクトの描画
////////////////////////////////////////////////
void Explotion::drawExplotion() {
	glPushMatrix();
	{
		glDisable(GL_CULL_FACE);
		glDepthMask(GL_FALSE);
		glTranslatef(position.x, position.y, position.z);
		smokeDraw();
		fireDraw();
		glDisable(GL_TEXTURE_2D);
		glEnable(GL_CULL_FACE);
		glDepthMask(GL_TRUE);
		glDisable(GL_BLEND);
	}
	glPopMatrix();

}

/////////////////////////////////////////
//煙エフェクトの描画
/////////////////////////////////////////
void Explotion::smokeDraw() {

	std::list < Effect > ::iterator smokeIterator = smoke.begin();

	while (smokeIterator != smoke.end()) {
		glPushMatrix();
		{
			smokeIterator->initSmokeTexture();
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

			//////////////////////
			//煙の描画を常に正面に向ける（ビルボード
			glm::mat4 view;
			glGetFloatv(
				GL_MODELVIEW_MATRIX,
				(float*)&view
				);

			glm::mat4 m = inverse(view);
			m[3][0] = m[3][1] = m[3][2] = 0;
			glMultMatrixf((float*)&m);//const GL_FSloat *m
			/////////////////////
			
			smokeIterator->alpha -= smokeIterator->alphaSpeed;
			smokeIterator->position += smokeIterator->speed;
			smokeIterator->scale += smokeIterator->sclSpeed;

			glColor4f(0.4, 0.4, 0.4, smokeIterator->alpha);
			glScalef(smokeIterator->scale.x, smokeIterator->scale.y, smokeIterator->scale.z);
			glTranslatef(smokeIterator->position.x, smokeIterator->position.y, smokeIterator->position.z);


			float v[] = {
				-1,2,
				-1,0,
				1,2,
				1,0
			};

			glEnableClientState(GL_VERTEX_ARRAY);//(GLenum array);

			glVertexPointer(2, GL_FLOAT, 0, v);

			float t[] = {
				0,0,
				0,1,
				1,0,
				1,1
			};

			glPixelStorei(
				GL_UNPACK_ALIGNMENT,// GLenum pname
				1);                 // GLint param

			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glTexCoordPointer(2, GL_FLOAT, 0, t);

			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

			if (smokeIterator->alpha <= 0) {
				smokeIterator = smoke.erase(smokeIterator);
			}
			else {
				++smokeIterator;
			}

		}
		glPopMatrix();
	}

}

//////////////////////////////////////////
//炎エフェクトの描画
/////////////////////////////////////////
void Explotion::fireDraw() {

	std::list < Effect > ::iterator fireIterator = fire.begin();

	while (fireIterator != fire.end()) {

		glPushMatrix();
		{
			fireIterator->initSmokeTexture();
			glBlendFunc(GL_SRC_ALPHA, GL_ONE);

			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			//煙の描画を常に正面に向ける（ビルボード
			glm::mat4 view;
			glGetFloatv(
				GL_MODELVIEW_MATRIX,
				(float*)&view
				);

			glm::mat4 m = inverse(view);
			m[3][0] = m[3][1] = m[3][2] = 0;
			glMultMatrixf((float*)&m);//const GL_FSloat *m
			fireIterator->alpha -= fireIterator->alphaSpeed;
			fireIterator->position += fireIterator->speed;
			fireIterator->scale += fireIterator->sclSpeed;

			glColor4f(1, 0.4, 0.2, fireIterator->alpha);
			glScalef(fireIterator->scale.x, fireIterator->scale.y, fireIterator->scale.z);
			glTranslatef(fireIterator->position.x, fireIterator->position.y, fireIterator->position.z);


			float v[] = {
				-1,2,
				-1,0,
				1,2,
				1,0
			};

			glEnableClientState(GL_VERTEX_ARRAY);//(GLenum array);

			glVertexPointer(2, GL_FLOAT, 0, v);

			float t[] = {
				0,0,
				0,1,
				1,0,
				1,1
			};

			glPixelStorei(
				GL_UNPACK_ALIGNMENT,// GLenum pname
				1);                 // GLint param

			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glTexCoordPointer(2, GL_FLOAT, 0, t);

			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

			if (fireIterator->alpha <= 0) {
				fireIterator = fire.erase(fireIterator);
			}
			else {
				++fireIterator;
			}

		}
		glPopMatrix();
	}
	
}

