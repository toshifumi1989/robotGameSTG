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
	char fileID[4];//ファイル識別子
	int fileSize;//ファイルのサイズ
	char RIFFID[4];//RIFF識別子

	char fmtChunkID[4];//チャンク識別子
	int fmtChunkSize;//チャンクサイズ
	short formatType;//フォーマットの種類
	short channel;//チャンネル数
	int frequency;//周波数
	int dataSizePerSec;//１秒あたりのデータサイズ
	short blockSize;//ブロックサイズ
	short bitType;//ビット数

	char dataChunkID[4];//チャンク識別子
	int dataChunkSize;//チャンクサイズ


};

extern void initMusic();
extern void readSound(const char* music);
extern void playMusic();
extern void deleteMusic();
extern const float timeMusic();
extern void stopMusic();

#endif