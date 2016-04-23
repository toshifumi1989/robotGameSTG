#include"bullet.h"
#include"player.h"
#include"enemy.h"
#include"field.h"
#include"../glm/gtx/intersect.hpp"


////////////////////////////////////////////
//弾の描画
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
//弾との当たり判定
//////////////////////////////////////////
void Bullet::hitCharacter(Object *_character) {

	////////////////////////////////////////////
	//弾とフィールドの当たり判定
	////////////////////////////////////////////
	//現在のx,z座標
	glm::vec3 orig = glm::vec3(position.x, -1, position.z);

	//y軸の判定
	glm::vec3 dir = glm::vec3(0, 1, 0);

	//三角形（フィールド）の三頂点
	glm::vec3 vert0;
	glm::vec3 vert1;
	glm::vec3 vert2;

	glm::vec3 distance = glm::vec3(0, 0, 0);//distanceのxに距離が入る

	int temporaryX = position.x;
	int temporaryZ = position.z;
	float nowPosY = position.y;


	
	if ((position.x - temporaryX) + (position.z - temporaryZ) < 1)
	{//上の三角
			
		vert0 = glm::vec3(temporaryX,field->vertex[(VTX * temporaryZ + temporaryX) * 3 + 1],temporaryZ);

		vert1 = glm::vec3(temporaryX + 1, field->vertex[(VTX * temporaryZ + temporaryX + 1) * 3 + 1], temporaryZ);
		
		vert2 = glm::vec3(temporaryX, field->vertex[((VTX * (temporaryZ + 1)) + temporaryX) * 3 + 1], temporaryZ + 1);
		
		//三角形と弾の当たり判定
		if (glm::intersectLineTriangle(orig, dir, vert0, vert1, vert2, distance)) {
			//もし今のy座標より弾とフィールドとの距離が小さい場合
			if (position.y <= distance.x) {
				onFlag = false;
			}
		}

	}
	else 
	{//下の三角
		
		vert0 = glm::vec3(temporaryX + 1,field->vertex[(VTX * temporaryZ + temporaryX + 1) * 3 + 1],temporaryZ);
		
		vert1 = glm::vec3(temporaryX, field->vertex[((VTX * (temporaryZ + 1)) + temporaryX) * 3 + 1], temporaryZ + 1);
		
		vert2 = glm::vec3(temporaryX + 1, field->vertex[((VTX * (temporaryZ + 1)) + temporaryX + 1) * 3 + 1], temporaryZ + 1);
		
		//三角形と弾の当たり判定
		if (glm::intersectLineTriangle(orig, dir, vert0, vert1, vert2, distance)) {
			//もし今のy座標より弾とフィールドとの距離が小さい場合
			if (position.y <= distance.x) {
				onFlag = false;
			}
		}
	}


	///////////////////////////////////////////////
	//弾とキャラクターの当たり判定
	///////////////////////////////////////////////

	//弾とキャラクターの距離
	const float bulletToCharacter =
		(position.x - _character->position.x) * (position.x - _character->position.x)
		+ (position.y - _character->position.y) * (position.y - _character->position.y)
		+ (position.z - _character->position.z) * (position.z - _character->position.z);

	//キャラクターと衝突
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
//毎フレームの更新
//////////////////////////////////////////
void Bullet::update() {

	position += speed;

	//フィールド外にでると弾が消える
	if (position.x >= 228 || position.x <= 28 ||
		position.z >= 228 || position.z <= 28) {
		onFlag = false;
	}

}





