#define _CRT_SECURE_NO_WARNINGS
#include"field.h"
#include"../glm/gtx/intersect.hpp"

/////////////////////////////////////////////
//フィールド読み込み
/////////////////////////////////////////////

void Field::readField(const char* _texture) {

	FILE *pFile = fopen(_texture, "rb");
	assert(pFile != NULL);

	BITMAPFILEHEADER bf;
	BITMAPINFOHEADER bi;

	fread(&bf, sizeof(BITMAPFILEHEADER), 1, pFile);
	fread(&bi, sizeof(BITMAPINFOHEADER), 1, pFile);

	//読み込んだフィールドの大きさを保存
	int size = bi.biWidth *bi.biHeight * sizeof(RGB);

	pixelsField = (RGB*)malloc(size);
	fread(pixelsField, size, 1, pFile);

	fclose(pFile);

	//RGBのRとBの入れ替え
	for (int i = 0; i < bi.biWidth * bi.biHeight; i++) {
		char sub = pixelsField[i].b;
		pixelsField[i].b = pixelsField[i].r;
		pixelsField[i].r = sub;
	}

	//画像の上下反転
	for (int p = 0; p < bi.biHeight / 2; p++) {
		for (int q = 0; q < bi.biWidth; q++) {
			RGB sub = pixelsField[bi.biWidth * p + q];
			pixelsField[bi.biWidth * p + q] = pixelsField[bi.biWidth *(bi.biHeight - 1 - p) + q];
			pixelsField[bi.biWidth *(bi.biHeight - 1 - p) + q] = sub;
		}
	}

	glTexImage2D(
		GL_TEXTURE_2D,		//GLenum target,
		0,					//GLint level,
		GL_RGB,				//GLint internalformat, 
		bi.biWidth, bi.biHeight,	//GLsizei width, GLsizei height, 
		0,					//GLint border, 
		GL_RGB,				//GLenum format, 
		GL_UNSIGNED_BYTE,	//GLenum type, 
		pixelsField);			//const GLvoid *pixels

}


/////////////////////////////////////////////////
//フィールドの場所を確保
/////////////////////////////////////////////////
void  Field::setup() {

	float y = 0;

	for (int z = 0; z < VTX; z++) {
		for (int x = 0; x < VTX; x++) {

			//texture
			tex.push_back((float)x / (VTX - 1));
			tex.push_back((float)z / (VTX - 1));

			y = (pixelsField[VTX * z * (256 / VTX) + x * (256 / VTX)].r + pixelsField[VTX * z * (256 / VTX) + x * (256 / VTX)].g + pixelsField[VTX * z * (256 / VTX) + x * (256 / VTX)].b) / 1.f / 100;

			//vertex
			vertex.push_back((float)x);
			vertex.push_back(y);
			vertex.push_back((float)z);

			//normal
			normal.push_back(0);
			normal.push_back(1);
			normal.push_back(0);
		}
	}

	for (int z = 0; z < VTX - 1; z++) {//行の数
		for (int x = 0; x < VTX - 1; x++) {//列の数
			index.push_back(VTX * z + x);
			index.push_back(VTX * z + x + VTX);
			index.push_back(VTX * z + x + 1);
			index.push_back(VTX * z + x + 1);
			index.push_back(VTX * z + x + VTX);
			index.push_back(VTX * z + x + VTX + 1);
		}
	}
}

////////////////////////////////////////////////
//フィールド描画
///////////////////////////////////////////////
void Field::drawField() {
	glPushMatrix();
	{
		glBindTexture(GL_TEXTURE_2D, textures[0]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);

		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		glEnable(GL_TEXTURE_2D);

		const float *v = vertex.data();
		const float *n = normal.data();
		const unsigned int *ind = index.data();
		const float *t = tex.data();

		glVertexPointer(3, GL_FLOAT, 0, v);
		glNormalPointer(GL_FLOAT, 0, n);
		glTexCoordPointer(2, GL_FLOAT, 0, t);

		glDrawElements(GL_TRIANGLES, index.size(), GL_UNSIGNED_INT, ind);

		glDisable(GL_CULL_FACE);

		//プレイヤーの移動できる端を描画
		glColor3f(1, 1, 0);
		glBegin(GL_QUADS);
		{
			glVertex3f(28, 0, 28);
			glVertex3f(228, 0, 28);
			glVertex3f(228, 2.2f, 28);
			glVertex3f(28, 2.2f, 28);

			glVertex3f(28, 0, 28);
			glVertex3f(28, 0, 228);
			glVertex3f(28, 2.2f, 228);
			glVertex3f(28, 2.2f, 28);

			glVertex3f(228, 0, 228);
			glVertex3f(28, 0, 228);
			glVertex3f(28, 2.2f, 228);
			glVertex3f(228, 2.2f, 228);

			glVertex3f(228, 0, 228);
			glVertex3f(228, 0, 28);
			glVertex3f(228, 2.2f, 28);
			glVertex3f(228, 2.2f, 228);
		}
		glEnd();

		glEnable(GL_CULL_FACE);
		

		glDisable(GL_TEXTURE_2D);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
	}
	glPopMatrix();
}


///////////////////////////////////////////////////
//フィールドとの当たり判定
///////////////////////////////////////////////////
void Field::intersect(glm::vec3 _pos) {

	glm::vec3 orig = glm::vec3(_pos.x, -1, _pos.z);//始点で、直線上の任意の点
	glm::vec3 dir = glm::vec3(0, 1, 0);//直線の向きで、直線を定義する
	glm::vec3 vert0;//以下の３点で三角形を定義
	glm::vec3 vert1;
	glm::vec3 vert2;
	glm::vec3 distance = glm::vec3(0, 0, 0);//xメンバに、始点から交差点の距離が取得される

	int temporaryX = _pos.x;//x座標の整数部分
	int temporaryZ = _pos.z;//z座標の整数部分
	float nowPosY = _pos.y;//現在のy座標

	if ((_pos.x - temporaryX) + (_pos.z - temporaryZ) < 1) {

		//上の三角
		vert0 = glm::vec3(temporaryX, vertex[(VTX * temporaryZ + temporaryX) * 3 + 1], temporaryZ);
		vert1 = glm::vec3(temporaryX + 1, vertex[(VTX * temporaryZ + temporaryX + 1) * 3 + 1], temporaryZ);
		vert2 = glm::vec3(temporaryX, vertex[((VTX * (temporaryZ + 1)) + temporaryX) * 3 + 1], temporaryZ + 1);

		if (glm::intersectLineTriangle(orig, dir, vert0, vert1, vert2, distance)) {
			if (_pos.y <= distance.x) {
				nextY = distance.x;
			}
		}
	}
	else {
		//下の三角
		vert0 = glm::vec3(temporaryX + 1, vertex[(VTX * temporaryZ + temporaryX + 1) * 3 + 1], temporaryZ);
		vert1 = glm::vec3(temporaryX, vertex[((VTX * (temporaryZ + 1)) + temporaryX) * 3 + 1], temporaryZ + 1);
		vert2 = glm::vec3(temporaryX + 1, vertex[((VTX * (temporaryZ + 1)) + temporaryX + 1) * 3 + 1], temporaryZ + 1);

		if (glm::intersectLineTriangle(orig, dir, vert0, vert1, vert2, distance)) {
			if (_pos.y <= distance.x) {
				nextY = distance.x;
			}
		}
	}


	glm::vec3 intersect = orig + dir * distance.x;

	nextY = intersect.y;

}