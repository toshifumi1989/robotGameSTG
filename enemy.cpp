

#include "enemy.h"
#include "player.h"
#include "../glut.h"

extern Player *player;
extern std::list<Bullet> enemyBullet;
extern GLuint textures[7];


//////////////////////////////////////
//�t���[���X�V
/////////////////////////////////////
void Enemy::update() {
	position += speed;
	speed *= 0.95f;
}


/////////////////////////////////////
//���f���ǂݍ���
/////////////////////////////////////
void Enemy::readModel(const char* _model) {
	float v = 0;
	unsigned short w = 0;
	float n = 0;

	int vertexNum;
	int indexNum;
	int normalsNum;

	FILE *pFile = fopen(_model, "r");
	assert(pFile != NULL);

	char buf[256];

	while (1) {
		int result = fscanf(pFile, "%s", buf);
		if (result == -1)break;

		if (strcmp(buf, "template") == 0) {
			while (1) {
				fscanf(pFile, "%s", buf);
				if (*buf == '}')break;
			}
		}

		if (strcmp(buf, "Mesh") == 0) {
			break;
		}
	}

	/*----------Mesh�ǂݍ���------------*/

	fscanf(pFile, "%s", buf);

	fscanf(pFile, "%d", &vertexNum);

	fscanf(pFile, "%s", buf);


	for (int i = 0; i < vertexNum; i++) {
		fscanf(pFile, "%f", &v);
		vertex.push_back(v);

		fscanf(pFile, "%s", buf);

		fscanf(pFile, "%f", &v);
		vertex.push_back(v);

		fscanf(pFile, "%s", buf);

		fscanf(pFile, "%f", &v);
		vertex.push_back(v);

		fscanf(pFile, "%s", buf);

	}

	/*-------------------------------------*/

	/*----------Index�ǂݍ���--------------*/
	fscanf(pFile, "%d", &indexNum);

	fscanf(pFile, "%s", buf);

	for (int i = 0; i < indexNum; i++) {
		fscanf(pFile, "%s", buf);

		fscanf(pFile, "%hu", &w);
		index.push_back(w);

		fscanf(pFile, "%s", buf);

		fscanf(pFile, "%hu", &w);
		index.push_back(w);

		fscanf(pFile, "%s", buf);

		fscanf(pFile, "%hu", &w);
		index.push_back(w);

		fscanf(pFile, "%s", buf);
	}
	/*-------------------------------------*/

	while (1) {
		int result = fscanf(pFile, "%s", buf);
		if (result == -1)break;

		if (strcmp(buf, "MeshNormals") == 0) {
			break;
		}
	}

	/*----------Normal�ǂݍ���--------------*/
	fscanf(pFile, "%s", buf);

	fscanf(pFile, "%d", &normalsNum);

	fscanf(pFile, "%s", buf);

	for (int i = 0; i < normalsNum; i++) {
		fscanf(pFile, "%f", &n);
		normal.push_back(n);

		fscanf(pFile, "%s", buf);

		fscanf(pFile, "%f", &n);
		normal.push_back(n);

		fscanf(pFile, "%s", buf);

		fscanf(pFile, "%f", &n);
		normal.push_back(n);

		fscanf(pFile, "%s", buf);
	}
	/*-------------------------------------*/

	fclose(pFile);
}

///////////////////////////////////////////
//�G�l�~�[�`��
///////////////////////////////////////////
void Enemy::draw(int _i) {
	glPushMatrix();
	{
		angle = atan2(position.x - player->position.x, position.z - player->position.z) * 180 / M_PI;

		glTranslatef(position.x, position.y, position.z);
		glRotatef(angle, 0, 1, 0);

		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnable(GL_NORMALIZE);

		glColor3f(0.3f, 0.3f, 0.3f);
		glRotatef(180, 0, 1, 0);
		glScalef(0.5f, 0.5f, 0.5f);

		const float *ver = vertex.data();
		const float *nor = normal.data();
		const unsigned short *ind = index.data();

		glVertexPointer(3, GL_FLOAT, 0, ver);

		glNormalPointer(GL_FLOAT, 0, nor);

		glDrawElements(GL_TRIANGLES, index.size(), GL_UNSIGNED_SHORT, ind);

		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisable(GL_NORMALIZE);

		//�r���{�[�h�s��----------------------------------
		glm::mat4 view;
		glGetFloatv(GL_MODELVIEW_MATRIX, (float*)&view);

		glm::mat4 m = glm::inverse(view);
		m[3][0] = m[3][1] = m[3][2] = 0;

		glMultMatrixf((float*)&m);

		//���b�N�I�������Ă���Ƃ�
		//�^�[�Q�b�g�}�[�J�[��`�悷��
		if (player->targetFlag == true) {
			if (_i == player->targetNum) {

				glBindTexture(GL_TEXTURE_2D, textures[1]);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

				glEnable(GL_TEXTURE_2D);

				glDisable(GL_CULL_FACE);
				glDisable(GL_DEPTH_TEST);

				glEnable(GL_BLEND);
				glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

				glBlendFunc(
					GL_SRC_ALPHA,           // GLenum sfactor
					GL_ONE_MINUS_SRC_ALPHA);// GLenum dfactor

				glColor3f(1, 1, 0);
				glScalef(2, 2, 0);

				glBegin(GL_QUADS);
				{
					glTexCoord2d(0, 1);
					glVertex3d(-1.0, -1.0, 0.0);
					glTexCoord2d(1, 1);
					glVertex3d(1.0, -1.0, 0.0);
					glTexCoord2d(1, 0);
					glVertex3d(1.0, 1.0, 0.0);
					glTexCoord2d(0, 0);
					glVertex3d(-1.0, 1.0, 0.0);

				}
				glEnd();

				glDisable(GL_BLEND);
			}
		}

		//�G�l�~�[��HP�`��-----------------
		glTranslatef(-1, 2, 0);

		glColor3f(1, 1, 0);
		glBegin(GL_QUAD_STRIP);
		{

			glVertex3f(enemy[_i].HP / 10.f, 0.25f, 0);
			glVertex3f(0, 0.25f, 0);
			glVertex3f(enemy[_i].HP / 10.f, -0.25f, 0);
			glVertex3f(0, -0.25f, 0);
		}
		glEnd();

		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);

		glDisable(GL_TEXTURE_2D);

	}
	glPopMatrix();
}


//////////////////////////////////
//�G�l�~�[�̍s���iAI
/////////////////////////////////
void Enemy::action() {

	//�G�̓���

	actionCount++;//�s���̊Ԋu���L���邽�߂ɃJ�E���g

	char enemyActionTime = 120;//�s������^�C�~���O

	//�G�l�~�[�������Ƃ�----------------------
	if (actionCount == enemyActionTime) {

		char actionPoint = 50;

		//�G�̍s�����o���o���ɂ��邽��
		//�����l���΂�΂�ɍĐݒ�
		actionCount = rand() % actionPoint;
		speed = glm::vec3(0, 0, 0);

		//�s���p�^�[���𕪂���
		int random = rand() % 8;

		//����0��1�̏ꍇ
		//x���W�ňړ�����
		if (random == 0 || random == 1) {
			if (random == 0) {
				speed.x = 1;
			}
			else {
				speed.x = -1;
			}

		}
		else if (random == 2 || random == 3)
		{//����2��3�̏ꍇ
		 //z���W�ňړ�����
			if (random == 2) {
				speed.z = 1;
			}
			else {
				speed.z = -1;
			}

		}
		else 
		{//����4�`7�̏ꍇ
		 //�G���e������


			//�o���b�g(�G�l�~�[
			Bullet bullet;
			bullet.position = position;

			glm::vec3 bulletToPlayer(player->position.x - position.x, player->position.y - position.y, player->position.z - position.z);

			float bulletSpeed = 1.2f;
			bullet.speed = glm::normalize(bulletToPlayer) * bulletSpeed;

			enemyBullet.push_back(bullet);
		}

	}

	//�t�B�[���h�̊O�ɏo�Ȃ��悤�ɂ��邽��
	if (position.x > 228 || position.x < 28 ||
		position.z > 228 || position.z < 28) {
		position = lastPosition;
	}

	//�G�ƃv���C���[�̓����蔻��
	float enemyToPlayer =
		(position.x - player->position.x) * (position.x - player->position.x)
		+ (position.y - player->position.y) * (position.y - player->position.y)
		+ (position.z - player->position.z) * (position.z - player->position.z);

	if (enemyToPlayer < 1) {
		player->speed.x = -player->speed.x;
		player->speed.z = -player->speed.z;
	}


	lastPosition = position;

}
