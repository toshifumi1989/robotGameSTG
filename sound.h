#ifndef SOUND_H
#define SOUND_H

#include <math.h>
#include "../AL/al.h"
#include "../AL\alc.h"

#pragma comment(lib,"OpenAL32.lib") 

extern ALCdevice *device;
extern ALCcontext *context;
extern ALCuint bid;
extern ALuint sid;


class WavFile {
public:
	char fileID[4];//�t�@�C�����ʎq
	int fileSize;//�t�@�C���̃T�C�Y
	char RIFFID[4];//RIFF���ʎq

	char fmtChunkID[4];//�`�����N���ʎq
	int fmtChunkSize;//�`�����N�T�C�Y
	short formatType;//�t�H�[�}�b�g�̎��
	short channel;//�`�����l����
	int frequency;//���g��
	int dataSizePerSec;//�P�b������̃f�[�^�T�C�Y
	short blockSize;//�u���b�N�T�C�Y
	short bitType;//�r�b�g��

	char dataChunkID[4];//�`�����N���ʎq
	int dataChunkSize;//�`�����N�T�C�Y


};

extern void initMusic();
extern void readSound(const char* music);
extern void playMusic();
extern void deleteMusic();
extern const float timeMusic();
extern void stopMusic();

#endif