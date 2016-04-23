#include"bullet.h"
#include"player.h"
#include"enemy.h"
#include"field.h"
#include"../glm/gtx/intersect.hpp"


////////////////////////////////////////////
//�e�̕`��
///////////////////////////////////////////
void Bullet::draw() {
	glPushMatrix();
	{
		glColor3f(1, 1, 0);
		glTranslatef(position.x, position.y, position.z);
		glutSolidSphere(size, 30, 30);
	}
	glPopMatrix();
}

//////////////////////////////////////////
//�e�Ƃ̓����蔻��
//////////////////////////////////////////
void Bullet::hitCharacter(Object *_character) {

	////////////////////////////////////////////
	//�e�ƃt�B�[���h�̓����蔻��
	////////////////////////////////////////////
	//���݂�x,z���W
	glm::vec3 orig = glm::vec3(position.x, -1, position.z);

	//y���̔���
	glm::vec3 dir = glm::vec3(0, 1, 0);

	//�O�p�`�i�t�B�[���h�j�̎O���_
	glm::vec3 vert0;
	glm::vec3 vert1;
	glm::vec3 vert2;

	glm::vec3 distance = glm::vec3(0, 0, 0);//distance��x�ɋ���������

	int temporaryX = position.x;
	int temporaryZ = position.z;
	float nowPosY = position.y;


	
	if ((position.x - temporaryX) + (position.z - temporaryZ) < 1)
	{//��̎O�p
			
		vert0 = glm::vec3(temporaryX,field->vertex[(VTX * temporaryZ + temporaryX) * 3 + 1],temporaryZ);

		vert1 = glm::vec3(temporaryX + 1, field->vertex[(VTX * temporaryZ + temporaryX + 1) * 3 + 1], temporaryZ);
		
		vert2 = glm::vec3(temporaryX, field->vertex[((VTX * (temporaryZ + 1)) + temporaryX) * 3 + 1], temporaryZ + 1);
		
		//�O�p�`�ƒe�̓����蔻��
		if (glm::intersectLineTriangle(orig, dir, vert0, vert1, vert2, distance)) {
			//��������y���W���e�ƃt�B�[���h�Ƃ̋������������ꍇ
			if (position.y <= distance.x) {
				onFlag = false;
			}
		}

	}
	else 
	{//���̎O�p
		
		vert0 = glm::vec3(temporaryX + 1,field->vertex[(VTX * temporaryZ + temporaryX + 1) * 3 + 1],temporaryZ);
		
		vert1 = glm::vec3(temporaryX, field->vertex[((VTX * (temporaryZ + 1)) + temporaryX) * 3 + 1], temporaryZ + 1);
		
		vert2 = glm::vec3(temporaryX + 1, field->vertex[((VTX * (temporaryZ + 1)) + temporaryX + 1) * 3 + 1], temporaryZ + 1);
		
		//�O�p�`�ƒe�̓����蔻��
		if (glm::intersectLineTriangle(orig, dir, vert0, vert1, vert2, distance)) {
			//��������y���W���e�ƃt�B�[���h�Ƃ̋������������ꍇ
			if (position.y <= distance.x) {
				onFlag = false;
			}
		}
	}


	///////////////////////////////////////////////
	//�e�ƃL�����N�^�[�̓����蔻��
	///////////////////////////////////////////////

	//�e�ƃL�����N�^�[�̋���
	const float bulletToCharacter =
		(position.x - _character->position.x) * (position.x - _character->position.x)
		+ (position.y - _character->position.y) * (position.y - _character->position.y)
		+ (position.z - _character->position.z) * (position.z - _character->position.z);

	//�L�����N�^�[�ƏՓ�
	if (bulletToCharacter <= 2) {
		for (int i = 0; i < 15; i++) {
			Effect proliferation;
			proliferation.position = _character->position;
			proliferation.speed.x = (rand() % 20 - 10) / 100.f;
			proliferation.speed.y = (rand() % 20 - 10) / 100.f;
			proliferation.speed.z = (rand() % 20 - 10) / 100.f;
			proliferation.drawCount = 0;

			damage.push_back(proliferation);
		}
		_character->HP -= damageSize;
		onFlag = false;
	}

}

///////////////////////////////////////////
//���t���[���̍X�V
//////////////////////////////////////////
void Bullet::update() {

	position += speed;

	//�t�B�[���h�O�ɂł�ƒe��������
	if (position.x >= 228 || position.x <= 28 ||
		position.z >= 228 || position.z <= 28) {
		onFlag = false;
	}

}





