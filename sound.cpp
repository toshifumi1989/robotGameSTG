#define _CRT_SECURE_NO_WARNINGS

#include"sound.h"
#include<assert.h>
#include<Windows.h>
#include<stdlib.h>
#include<stdio.h>

ALCdevice *device;
ALCcontext *context;
ALCuint bid;
ALuint sid;

void initMusic() {
	device = alcOpenDevice(NULL);//const ALCchar *devicename

	assert(alcGetError(device) == ALC_NO_ERROR);

	context =
		alcCreateContext(
			device,//ALCdevice *device,
			NULL); //const ALCint* attrlist

	assert(alcGetError(device) == ALC_NO_ERROR);

	alcMakeContextCurrent(context);//ALCcontext *context
	assert(alcGetError(device) == ALC_NO_ERROR);


}

void readSound(const char* music) {

	FILE *pFile = fopen(music, "rb");

	WavFile wavfile;

	fread(&wavfile, sizeof(WavFile), 1, pFile);

	int dataSize = wavfile.dataChunkSize * sizeof(short);

	short *data = (short*)malloc(dataSize);

	fread(data, dataSize, 1, pFile);

	fclose(pFile);

	alGenBuffers(
		1,		//ALsizei n
		&bid);//ALuint *buffers

	assert(alGetError() == AL_NO_ERROR);

	if (wavfile.channel == 1) {
		//モノラル
		if (wavfile.bitType == 8) {
			//8ビット
			alBufferData(
				bid,				//ALuint buffer
				AL_FORMAT_MONO8,	// ALenum format
				data,				//const ALvoid *data
				dataSize,			// ALsizei size
				wavfile.frequency);//ALsizei freq
		}
		else {
			//16ビット
			alBufferData(
				bid,				//ALuint buffer
				AL_FORMAT_MONO16,	// ALenum format
				data,				//const ALvoid *data
				dataSize,		// ALsizei size
				wavfile.frequency);//ALsizei freq
		}
	}
	else {
		//ステレオ
		if (wavfile.bitType == 8) {
			//8ビット
			alBufferData(
				bid,				//ALuint buffer
				AL_FORMAT_STEREO8,	// ALenum format
				data,				//const ALvoid *data
				dataSize,		// ALsizei size
				wavfile.frequency);//ALsizei freq
		}
		else {
			//16ビット
			alBufferData(
				bid,				//ALuint buffer
				AL_FORMAT_STEREO16,	// ALenum format
				data,				//const ALvoid *data
				dataSize,		// ALsizei size
				wavfile.frequency);//ALsizei freq
		}

	}
	assert(alGetError() == AL_NO_ERROR);

	alGenSources(
		1,		//ALsizei n,
		&sid);	//ALuint *sources
	assert(alGetError() == AL_NO_ERROR);

	alSourcei(
		sid,		//ALuint source
		AL_BUFFER,	//ALenum param
		bid);		//ALint value
	assert(alGetError() == AL_NO_ERROR);

	alSourcei(
		sid,		//ALuint source
		AL_LOOPING,	//ALenum param
		AL_TRUE);	//ALint value

	assert(alGetError() == AL_NO_ERROR);

}


void playMusic() {

	alSourcePlay(sid);//ALuint source
	assert(alGetError() == AL_NO_ERROR);

}


void deleteMusic()
{
	alDeleteBuffers(
		1,      // ALsizei n
		&bid);  // const ALuint* buffers

	alDeleteSources(
		1,          // ALsizei n
		&sid);   // const ALuint* sources
}

const float timeMusic() {

	float aaa;

	alGetSourcef(sid, AL_SEC_OFFSET, &aaa);

	return aaa;

}

void stopMusic() {

	alSourceStop(sid);	// ALuint source

}