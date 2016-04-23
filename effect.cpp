#include"effect.h"

/////////////////////////////////
//���t���[��
/////////////////////////////////
void Effect::update() {
	position += speed;
	speed *= 0.95;
}

////////////////////////////////
//���̕`��i�_���[�W�G�t�F�N�g
////////////////////////////////
void Effect::draw() {
	glPushMatrix();
	{
		glColor4f(1, 0.3f, 0, 0.5f);
		glTranslatef(position.x, position.y,position.z);
		glutSolidSphere(0.1f, 30, 30);
	}
	glPopMatrix();

}

///////////////////////////////////////
//�e�N�X�`���ݒ�
///////////////////////////////////////
void Effect::initSmokeTexture() {
	glBindTexture(GL_TEXTURE_2D, textures[3]);

	glTexParameteri(
		GL_TEXTURE_2D,//GLenum target, 
		GL_TEXTURE_MIN_FILTER,//GLenum pname, 
		GL_NEAREST);//GLint param

	glTexParameteri(
		GL_TEXTURE_2D,//GLenum target, 
		GL_TEXTURE_MAG_FILTER,//GLenum pname, 
		GL_NEAREST);//GLint param

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
}