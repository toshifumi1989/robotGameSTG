#include"player.h"
#include"enemy.h"
#include"camera.h"
#include"bullet.h"
#include"field.h"
#include"../manager.h"
#include<float.h>
#include <assert.h>

#define DEADZONEPLUS (5000)
#define DEADZONEMINUS (-5000)

std::list<Bullet> playerBullet;
std::list<Bullet> machineGun;

extern std::vector<Enemy> enemy;
extern Camera *camera;
extern unsigned char keys[256];

void Player::controller() {
	const WORD pressedKeys = joystic.state.Gamepad.wButtons;//�����Ă���{�^��
	const WORD releasedKeys = ~joystic.state.Gamepad.wButtons;//����Ă���{�^��
	const WORD changedKeys = joystic.lastkeys ^ pressedKeys;//�؂�ւ�����{�^��
	const WORD downKeys = changedKeys & pressedKeys;//���������{�^��
	const WORD upKeys = changedKeys & releasedKeys;//���������{�^��

	//R2�{�^���̃g���K�[ONOFF
	joystic.leftTriger();
	joystic.rightTriger();

	//�E�X�e�B�b�N
	if (targetFlag == false) {
		//�X�e�B�b�N�̓��͂�����ꍇ�i����
		if (DEADZONEPLUS < joystic.state.Gamepad.sThumbRX ||
			DEADZONEMINUS > joystic.state.Gamepad.sThumbRX) {

			float rightStickYawQuantity = 15000;
			camera->yow -= joystic.state.Gamepad.sThumbRX / rightStickYawQuantity;

		}
		else if (keys['l'] == 1) {
			camera->yow -= 1;
		}
		else if (keys['j'] == 1) {
			camera->yow += 1;
		}

		//�X�e�B�b�N�̓��͂�����ꍇ�i����
		if (DEADZONEPLUS < joystic.state.Gamepad.sThumbRY ||
			DEADZONEMINUS > joystic.state.Gamepad.sThumbRY) {
			float rightStickQuantity = 32768;
			updown += joystic.state.Gamepad.sThumbRY / rightStickQuantity;


			char cameraLimit = 80;
			if (updown > cameraLimit) {
				updown = cameraLimit;
			}
			else if (updown < -cameraLimit) {
				updown = -cameraLimit;
			}

		}
		else if (keys['i'] == 1 || keys['k'] == 1) {
			if (keys['i'] == 1) {
				updown += 1;
			}
			else {
				updown -= 1;
			}

			char cameraLimit = 80;
			if (updown > cameraLimit) {
				updown = cameraLimit;
			}
			else if (updown < -cameraLimit) {
				updown = -cameraLimit;
			}
		}

	}

	static unsigned char tmpSpaceKeys = 0;

	//�^�[�Q�b�g��ON OFF
	if ((downKeys & XINPUT_GAMEPAD_B )
		|| (tmpSpaceKeys == 0 && keys[' '] == 1)) {
		targetNum = -1;
		if (targetFlag == true) {

			targetFlag = false;
		}
		else {
			targetFlag = true;

			int nextTargetNum = -1;
			float nextTarget = FLT_MIN;

			//���݂̃^�[�Q�b�g
			auto playerToCameraTarget = camera->target - position;
			playerToCameraTarget.y = 0;
			glm::vec3 playerDirec = glm::normalize(playerToCameraTarget);
			float enemyToPlayer = 0;

			for (int i = 0; i < enemy.size(); i++) {

				//�G�̃^�[�Q�b�g�؂�ւ��̂��߂̌v�Z
				if (targetNum != i) {

					//���݂̃^�[�Q�b�g�̑�
					auto playerToAnother = enemy[i].position - position;
					playerToAnother.y = 0;
					glm::vec3 enemyDirec = glm::normalize(playerToAnother);

					//�O�ςƓ��ςŎ��̃^�[�Q�b�g���v�Z
					float enemyDot = glm::dot(playerDirec, enemyDirec);

					//���̃^�[�Q�b�g���Ƃ̋��������������
					//���̔ԍ���ۑ�����
					if (nextTarget < enemyDot) {
						nextTarget = enemyDot;
						nextTargetNum = i;
					}

				}
			}
			if (nextTargetNum == -1) {//��₪�����ł��Ȃ������Ƃ�
				targetFlag = false;
			}
			else {//��₪�����ł����Ƃ��A�ۑ������ԍ��������
				targetNum = nextTargetNum;
			}

		}
	}

	static unsigned char tmpKey_q = 0;

	//�^�[�Q�b�g�؂�ւ�
	if ((downKeys & XINPUT_GAMEPAD_LEFT_SHOULDER)
		|| ( tmpKey_q == 0 && keys['q'] == 1 )) {//�{�^�����������Ƃ�
		if (targetFlag == true) {
			if (enemy.size() > 1) {
				turn(false);
			}
		}
	}

	static unsigned char tmpKey_o = 0;

	//�^�[�Q�b�g�؂�ւ�
	if ((downKeys & XINPUT_GAMEPAD_RIGHT_SHOULDER)
		|| (tmpKey_o == 0 && keys['o'] == 1)) {//�{�^�����������Ƃ�
		if (targetFlag == true) {
			if (enemy.size() > 1) {
				turn(true);
			}
		}
	}


	//�e�ōU��---------------------------------------------------------------
	if (overHeat == false) {//�v���C���[���I�[�o�[�q�[�g���Ă��Ȃ����
		//�V���b�g�Q�[�W�̏����l���P�O�O�O
		//������g�p���邽�тɌ�������
		if (shotGaugeOver <= shotGauge) {//�V���b�g�Q�[�W������̂Ƃ�
			shotGauge = 1000;
		}
		else if (shotGauge < shotGaugeOver && shotGaugeUnder < shotGauge) {
			//�V���b�g�Q�[�W���������Ă���Ƃ�
			
																		   
			//�Q�[�W��
			char recoveryShotGauge = 4;
			shotGauge += recoveryShotGauge;

		}
		else {
			//�V���b�g�Q�[�W���Ȃ��Ȃ����Ƃ�
			//�I�[�o�[�q�[�g����
			overHeat = true;
			heatDepth = 0;
		}
	}
	else {//�I�[�o�[�q�[�g���Ă���Ƃ�
		if (shotGaugeOver <= shotGauge) {
			//�V���b�g�Q�[�W������܂ŉ񕜂�����
			//�I�[�o�[�q�[�g������
			overHeat = false;
		}
		else {
			//�Q�[�W��
			char recoveryShotGauge = 3;
			shotGauge += recoveryShotGauge;
		}

	}


	//���C�t��--------------------------------------------------------------
	static unsigned char tmpKey_e = 0;

	if ((joystic.rightTrigerFlag == true)
		||(tmpKey_e == 0 && keys['e'] == 1)) {
		//�I�[�o�[�q�[�g�ł͂Ȃ���Ό��Ă�
		if (overHeat == false) {

			int downGauge = 150;//�Q�[�W�����
			shotGauge -= downGauge;

			Bullet bullet;
			bullet.onFlag = true;
			bullet.position = glm::vec3(position.x, position.y + 0.3f, position.z);

			if (targetFlag == true) {
				//���b�N�I����Ԃ̂Ƃ�
				//�e�̕����Ɛ��K���i���b�N�I���̓G�Ɍ������Ă���
				glm::vec3 bulletToEnemy(enemy[targetNum].position.x - position.x, enemy[targetNum].position.y - (position.y + 0.3f), enemy[targetNum].position.z - position.z);

				bullet.speed = glm::normalize(bulletToEnemy) * 1.5f;
				playerBullet.push_back(bullet);

			}
			else {
				//���b�N�I���ł͂Ȃ��Ƃ�
				//�e�̕����Ɛ��K���i�V���b�g�}�[�N�̂ق��Ɍ������Ă���
				glm::vec3 bulletToMarker(shootTarget.x - position.x, shootTarget.y - (position.y + 1), shootTarget.z - position.z);

				bullet.speed = glm::normalize(bulletToMarker) * 1.5f;
				playerBullet.push_back(bullet);

			}
		}

	}

	//�V���b�g�K��------------------------------------------------------------
	static unsigned char tmpKey_u = 0;
	
	if ((joystic.leftTrigerFlag == true)
		||(tmpKey_u == 0 && keys['u'] == 1)) {

		if (overHeat == false) {

			int downGauge = 150;//�Q�[�W����
			shotGauge -= downGauge;

			for (int i = 0; i < 15; i++) {
				Bullet bullet;
				bullet.onFlag = true;
				bullet.damageSize = 1;
				bullet.size = 0.03f;
				bullet.position = position;

				if (targetFlag == true) {
					//�e�̕����Ɛ��K��
					glm::vec3 bulletToEnemy((enemy[targetNum].position.x + rand() % 7 - 4) - position.x, (enemy[targetNum].position.y + rand() % 7 - 4) - position.y, (enemy[targetNum].position.z + rand() % 7 - 4) - position.z);

					bullet.speed = glm::normalize(bulletToEnemy) * 1.0f;
					machineGun.push_back(bullet);
				}
				else {
					glm::vec3 bulletToMarker((shootTarget.x + rand() % 7 - 4) - position.x, (shootTarget.y + rand() % 7 - 4) - position.y, (shootTarget.z + rand() % 7 - 4) - position.z);

					bullet.speed = glm::normalize(bulletToMarker) * 1.0f;
					machineGun.push_back(bullet);
				}
			}
		}
	}


	/////////////////////////////////////////////
	//����
	/////////////////////////////////////////////


	//�W�����v-----------------------------------------------------------------
	static unsigned char tmpKey_m = 0;
	if ((downKeys & XINPUT_GAMEPAD_A) 
		||(tmpKey_m == 0 && keys['m'] == 1)) {
		if (junpFlag == false) {
			junpFlag = true;
			speed.y = 1.4f;
		}
	}

	//�v���C���[�ړ�-----------------------------------------------------------
	//�v���C���[�̓��͊p�x
	float inputYow = 0;
	float playerRad = angle * (M_PI / 180.0f);

	glm::vec3 playerDirec = glm::vec3(-sin(playerRad), 0, -cos(playerRad));
	glm::vec3 targetDirec;

	float moveX = 0;
	if (keys['a'] == 1) {
		moveX = -32768.f;
	}
	else if (keys['d'] == 1) {
		moveX = 32768.f;
	}
	else {
		moveX = joystic.state.Gamepad.sThumbLX;
	}

	float moveY = 0;
	if (keys['w'] == 1) {
		moveY = 32768.f;
	}
	else if (keys['s'] == 1) {
		moveY = -32768.f;
	}
	else {
		moveY = joystic.state.Gamepad.sThumbLY;
	}

	glm::vec2 stickDirec(moveX, moveY);

	if (glm::dot(stickDirec, stickDirec) > INPUT_DEADZONE * INPUT_DEADZONE) {

		inputYow = -atan2(moveX / 32768.f, moveY / 32768.f) * 180 / M_PI + camera->yow;
		float targetRad = inputYow * (M_PI / 180.0f);
		targetDirec = glm::vec3(-sin(targetRad), 0, -cos(targetRad));

		//�v���C���[�ړ�
		speed.x += cos(camera->yow * M_PI / 180) * moveX / 1000000 - sin(camera->yow * M_PI / 180) * moveY / 2000000;
		speed.z += -cos(camera->yow * M_PI / 180) * moveY / 1000000 - sin(camera->yow * M_PI / 180) * moveX / 2000000;

		//�y���`��̐ݒ�
		if (junpFlag == false) {
			initDust();
		}


	}
	else {
		float cameraRad = camera->yow * (M_PI / 180.0f);
		targetDirec = glm::vec3(-sin(cameraRad), 0, -cos(cameraRad));
		inputYow = camera->yow;
	}

	float resultY = glm::cross(playerDirec, targetDirec).y;
	float resultDot = glm::dot(playerDirec, targetDirec);
	float torque = (-resultDot + 1) * 0.5f + 0.3f;

	if (resultY * resultY < (10 * M_PI / 180) * (10 * M_PI / 180)) {
		if (0 < resultDot) {
			angle = inputYow;
		}
	}
	else if (resultY > 0) {
		angle += 30.0f *torque;
	}
	else {
		angle -= 30.0f*torque;
	}

	camera->lastUpDown = camera->upDown;
	joystic.lastkeys = joystic.state.Gamepad.wButtons;					//���̃V�[���ŉ����Ă����{�^����ۑ����邽��

	tmpSpaceKeys = keys[' '];
	tmpKey_o = keys['o'];
	tmpKey_e = keys['e'];
	tmpKey_q = keys['q']; 
	tmpKey_u = keys['u'];
	tmpKey_m = keys['m'];
}

/////////////////////////////////////////////////////////////
//���f���ǂݍ���
/////////////////////////////////////////////////////////////
void Player::readModel(const char* _model) {
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

/////////////////////////////////////////////////
//�s���̍X�V
/////////////////////////////////////////////////
void Player::update() {

	speed.x *= 0.95;
	speed.z *= 0.95;
	speed.y -= 0.05;
	position += speed;

	if (position.x >= 228 || position.x <= 28) {
		speed.x = 0;
		position.x = lastPosition.x;
	}
	if (position.z >= 228 || position.z <= 28) {
		speed.z = 0;
		position.z = lastPosition.z;
	}

	field->intersect(position);//�t�B�[���h�Ƃ̓����蔻��

	if (position.y < field->nextY + 1) {
		junpFlag = false;
		position.y = field->nextY + 1;
	}

	lastPosition = position;

}

///////////////////////////////////////////////////
//�v���C���[�`��
///////////////////////////////////////////////////
void Player::draw() {
	glPushMatrix();
	{
		glTranslatef(position.x, position.y, position.z);
		glRotatef(angle, 0, 1, 0);

		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnable(GL_NORMALIZE);

		glColor3f(0.3f, 0.3f, 0.8f);
		glRotatef(180, 0, 1, 0);
		glScalef(0.25f, 0.2f, 0.25f);

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


	}
	glPopMatrix();
}

////////////////////////////////////////////////
//2D�ł̕`��i�X�R�A�ƃQ�[�W
////////////////////////////////////////////////
void Player::show() {

	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);
	glColor3f(1, 1, 1);

	//�X�R�A�\��--------------------------------------------------------
	if (GameManager::getInstance()->selectScene == selectSurvival) {
		glPushMatrix();
		{

			char score[] = "Score : ";
			glTranslatef(350, 4000, 0);
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

	//�������------------------------------------------------------------
	glPushMatrix();
	{
		char move[] = "[LStick]:move";
		glTranslatef(150, 700, 0);
		glScalef(1.1f, 1.1f, 0);
		glLineWidth(2);
		for (int i = 0; move[i] != 0; i++) {
			glutStrokeCharacter(
				GLUT_STROKE_ROMAN,			//void *font,int
				move[i]);						//character
		}
	}
	glPopMatrix();
	glPushMatrix();
	{
		char shoot[] = "[R2]:Rifle";
		glTranslatef(150, 450, 0);
		glScalef(1.1f, 1.1f, 0);
		glLineWidth(2);
		for (int i = 0; shoot[i] != 0; i++) {
			glutStrokeCharacter(
				GLUT_STROKE_ROMAN,			//void *font,int
				shoot[i]);						//character
		}
	}
	glPopMatrix();
	glPushMatrix();
	{
		char machinegun[] = "[L2]:ShotGun";
		glTranslatef(150, 200, 0);
		glScalef(1.1f, 1.1f, 0);
		glLineWidth(2);
		for (int i = 0; machinegun[i] != 0; i++) {
			glutStrokeCharacter(
				GLUT_STROKE_ROMAN,			//void *font,int
				machinegun[i]);						//character
		}
	}
	glPopMatrix();
	glPushMatrix();
	{
		char target[] = "[B]:Lock-ON/OFF";
		glTranslatef(1100, 200, 0);
		glScalef(1.1f, 1.1f, 0);
		glLineWidth(2);
		for (int i = 0; target[i] != 0; i++) {
			glutStrokeCharacter(
				GLUT_STROKE_ROMAN,			//void *font,int
				target[i]);						//character
		}
	}
	glPopMatrix();
	glPushMatrix();
	{
		char Jump[] = "[A]:Jump";
		glTranslatef(1100, 450, 0);
		glScalef(1.1f, 1.1f, 0);
		glLineWidth(2);
		for (int i = 0; Jump[i] != 0; i++) {
			glutStrokeCharacter(
				GLUT_STROKE_ROMAN,			//void *font,int
				Jump[i]);						//character
		}
	}
	glPopMatrix();

	if (targetFlag == true) {
		glPushMatrix();
		{
			char turn[] = "[L1 or R1]:TargetChange";
			glTranslatef(1100, 700, 0);
			glScalef(1.1f, 1.1f, 0);
			glLineWidth(2);
			for (int i = 0; turn[i] != 0; i++) {
				glutStrokeCharacter(
					GLUT_STROKE_ROMAN,			//void *font,int
					turn[i]);						//character
			}
		}
		glPopMatrix();
	}
	else {
		glPushMatrix();
		{
			char cameraMove[] = "[RStick]:CameraMove";
			glTranslatef(1100, 700, 0);
			glScalef(1.1f, 1.1f, 0);
			glLineWidth(2);
			for (int i = 0; cameraMove[i] != 0; i++) {
				glutStrokeCharacter(
					GLUT_STROKE_ROMAN,			//void *font,int
					cameraMove[i]);						//character
			}
		}
		glPopMatrix();
	}

	//HP�\��------------------------------------------------------------
	glPushMatrix();
	{
		char HP[] = "HP";
		glTranslatef(3000, 550, 0);
		glScalef(2, 2, 0);
		glLineWidth(5);
		for (int i = 0; HP[i] != 0; i++) {
			glutStrokeCharacter(
				GLUT_STROKE_ROMAN,			//void *font,int
				HP[i]);						//character
		}
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(3500, 600, 0);

		glColor3f(1, 1, 1);
		glBegin(GL_QUADS);
		{
			glVertex2f(0, 0);
			glVertex2f(1000, 0);
			glVertex2f(1000, 200);
			glVertex2f(0, 200);
		}
		glEnd();

		if (HP > MaxHP / 2) {
			glColor3f(0, 1, 0);
		}
		else if (HP > MaxHP / 4) {
			glColor3f(1, 1, 0);
		}
		else {
			glColor3f(1, 0, 0);
		}

		if (HP > 0) {
			glBegin(GL_QUADS);
			{
				glVertex2f(0, 0);
				glVertex2f(1000 * HP / MaxHP, 0);
				glVertex2f(1000 * HP / MaxHP, 200);
				glVertex2f(0, 200);
			}
			glEnd();
		}

		glColor3f(1, 1, 1);

	}
	glPopMatrix();

	//�V���b�g�Q�[�W�\��-------------------------------------------------------

	glPushMatrix();
	{
		glTranslatef(3500, 200, 0);

		glColor3f(1, 1, 1);
		glBegin(GL_QUADS);
		{
			glVertex2f(0, 0);
			glVertex2f(1000, 0);
			glVertex2f(1000, 200);
			glVertex2f(0, 200);
		}
		glEnd();

		if (overHeat == false) {
			glColor3f(0, 1, 0);
		}
		else {
			glColor3f(1, 0, 0);
		}

		if (shotGauge > 0) {
			glBegin(GL_QUADS);
			{
				glVertex2f(0, 0);
				glVertex2f(shotGauge, 0);
				glVertex2f(shotGauge, 200);
				glVertex2f(0, 200);
			}
			glEnd();
		}

		glColor3f(1, 1, 1);

	}
	glPopMatrix();

	glPushMatrix();
	{
		char HP[] = "ShotCharge";
		glTranslatef(2800, 250, 0);
		glScalef(1, 2, 0);
		glLineWidth(2);
		for (int i = 0; HP[i] != 0; i++) {
			glutStrokeCharacter(
				GLUT_STROKE_ROMAN,			//void *font,int
				HP[i]);						//character
		}

		if (overHeat == true) {
			//�I�[�o�[�q�[�g�̕����̕`��
			//������_�ł�����
			heatDepth += 0.05f;
			glColor3f(1 * fabs(cos(heatDepth)), 0.5f * fabs(cos(heatDepth)), 0);
			char overheat[] = "OverHeat";
			glTranslatef(130, 0, 0);
			glScalef(1.5f, 1, 1);
			for (int i = 0; overheat[i] != 0; i++) {
				glutStrokeCharacter(
					GLUT_STROKE_ROMAN,			//void *font,int
					overheat[i]);						//character
			}
		}
	}
	glPopMatrix();

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
}

/////////////////////////////////////////////////////
//�y���̂��߂̏����ݒ�
///////////////////////////////////////////////////////
void Player::initDust() {
	for (int i = 0; i < 5; i++) {

		Effect smk;

		smk.alpha = 0.6f - rand() % 3 / 10.f;
		smk.alphaSpeed = 0.01f + rand() % 3 / 1000.f;

		smk.position = glm::vec3(position.x, position.y - 1, position.z);
		smk.scale = glm::vec3(rand() % 10 / 50.f, rand() % 10 / 50.f, rand() % 10 / 50.f);

		smk.speed.x = (-0.5f + rand() % 10 / 10.f) / 10000.f;
		smk.speed.y = 0.004f + rand() % 2 / 10000.f;
		smk.speed.z = (-0.5f + rand() % 10 / 10.f) / 10000.f;

		smk.sclSpeed.x = 0.02f + rand() % 5 / 1000.f;
		smk.sclSpeed.y = 0.02f + rand() % 5 / 1000.f;
		smk.sclSpeed.z = 0.02f + rand() % 5 / 1000.f;

		cloudOfDust.push_back(smk);
	}

}

///////////////////////////////////////////////
//�y���̕`��
///////////////////////////////////////////////
void Player::drawDust() {

	if (player->junpFlag == false) {

		glDisable(GL_CULL_FACE);
		glDepthMask(GL_FALSE);

		std::list < Effect > ::iterator smokeIterator = cloudOfDust.begin();

		while (smokeIterator != cloudOfDust.end()) {
			glPushMatrix();
			{
				smokeIterator->initSmokeTexture();
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

				glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
				//���̕`�����ɐ��ʂɌ�����i�r���{�[�h
				glm::mat4 view;
				glGetFloatv(
					GL_MODELVIEW_MATRIX,
					(float*)&view
					);

				glm::mat4 m = inverse(view);
				m[3][0] = m[3][1] = m[3][2] = 0;

				smokeIterator->alpha -= smokeIterator->alphaSpeed;
				smokeIterator->position += smokeIterator->speed;
				smokeIterator->scale += smokeIterator->sclSpeed;

				glColor4f(0.4, 0.4, 0.4, smokeIterator->alpha);
				glTranslatef(smokeIterator->position.x, smokeIterator->position.y, smokeIterator->position.z);

				glMultMatrixf((float*)&m);//const GL_FSloat *m

				glScalef(smokeIterator->scale.x, smokeIterator->scale.y, smokeIterator->scale.z);

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
					smokeIterator = cloudOfDust.erase(smokeIterator);
				}
				else {
					++smokeIterator;
				}

			}
			glPopMatrix();

		}
		glDisable(GL_TEXTURE_2D);
		glEnable(GL_CULL_FACE);
		glDepthMask(GL_TRUE);
		glDisable(GL_BLEND);

	}
}

///////////////////////////////////////////////
//�^�[�Q�b�g�}�[�J�[�̍X�V
///////////////////////////////////////////////
void Player::targetMaekerUpdate() {
	if (targetFlag == false) {

		shootTarget = glm::vec3(
			position.x - 70 * sin(camera->yow * M_PI / 180) * 1.0f * cos(updown * M_PI / 180),
			position.y + 70 * sin(updown * M_PI / 180),
			position.z - 70 * cos(camera->yow * M_PI / 180) * 1.0f * cos(updown * M_PI / 180));

	}

}

////////////////////////////////////////////
//�^�[�Q�b�g�}�[�J�[�̕`��
////////////////////////////////////////////
void Player::targetMaekerDraw() {
	if (targetFlag == false) {
		glPushMatrix();
		{
			glTranslatef(shootTarget.x, shootTarget.y, shootTarget.z);

			glBindTexture(GL_TEXTURE_2D, textures[4]);

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

			glm::mat4 view;
			glGetFloatv(GL_MODELVIEW_MATRIX, (float*)&view);

			glm::mat4 m = glm::inverse(view);
			m[3][0] = m[3][1] = m[3][2] = 0;

			glMultMatrixf((float*)&m);

			glScalef(12, 5, 1);
			glColor4f(1, 1, 1, 0.5f);

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

			glDisable(GL_TEXTURE_2D);
			glDisable(GL_BLEND);
			glEnable(GL_CULL_FACE);
			glEnable(GL_DEPTH_TEST);
		}
		glPopMatrix();
	}
}

//////////////////////////////////////////////
//�^�[�Q�b�g�؂�ւ�
/////////////////////////////////////////////
void Player::turn(bool _isRightTrun) {

	int nextTargetPlus = -1;
	int nextTargetMinus = -1;
	float targetPlus = FLT_MIN;
	float targetMinus = FLT_MIN;

	float enemyToPlayer = 0;

	for (int i = 0; i < enemy.size(); i++) {

		//�G�̃^�[�Q�b�g�؂�ւ��̂��߂̌v�Z
		if (targetNum != i) {

			//���݂̃^�[�Q�b�g
			auto playerToTarget = enemy[targetNum].position - position;
			playerToTarget.y = 0;
			glm::vec3 playerDirec = glm::normalize(playerToTarget);

			//���݂̃^�[�Q�b�g�̑�
			auto playerToAnother = enemy[i].position - position;
			playerToAnother.y = 0;
			glm::vec3 enemyDirec = glm::normalize(playerToAnother);

			//�O�ςƓ��ςŎ��̃^�[�Q�b�g���v�Z
			auto nextTargetCross = glm::cross(playerDirec, enemyDirec).y;
			float enemyDot = glm::dot(playerDirec, enemyDirec);

			if (nextTargetCross < 0) {
				if (targetPlus < enemyDot) {
					targetPlus = enemyDot;
					nextTargetPlus = i;
				}
			}
			else {
				if (targetMinus < enemyDot) {
					targetMinus = enemyDot;
					nextTargetMinus = i;
				}
			}
		}

	}
	int checkEarlier;
	int checkLater;

	if (_isRightTrun) {
		checkEarlier = nextTargetPlus;
		checkLater = nextTargetMinus;
	}
	else
	{
		checkEarlier = nextTargetMinus;
		checkLater = nextTargetPlus;
	}

	if (checkEarlier != -1) {
		targetNum = checkEarlier;
	}
	else {
		targetNum = checkLater;
	}

	if (targetNum == -1) {
		targetFlag = false;
	}
}