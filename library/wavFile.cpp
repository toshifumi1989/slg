#define _CRT_SECURE_NO_WARNINGS

#include "wavFile.h"
#include<assert.h>
#include<Windows.h>
#include<stdlib.h>
#include<stdio.h>

ALCdevice *device;
ALCcontext *context;
ALCuint bid[BGM::SOUND_MAX];
ALuint sid[BGM::SOUND_MAX];

WavFile *bgm;

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

	alGenBuffers(BGM::SOUND_MAX, bid);
	assert(alGetError() == AL_NO_ERROR);

	alGenSources(BGM::SOUND_MAX,sid);
	assert(alGetError() == AL_NO_ERROR);

	bgm = new WavFile();
	bgm->readSound("title.wav", BGM::TITLE_BGM);
	bgm->readSound("setup.wav", BGM::SETUP_BGM);
	bgm->readSound("battle.wav", BGM::BATTLE_BGM);
	//bgm->readSound("result.wav", BGM::RESULT_BGM);
}

void WavFile::readSound(const char* music,unsigned char sound) {

	FILE *pFile = fopen(music, "rb");

	WavFile wavfile;

	fread(&wavfile, sizeof(WavFile), 1, pFile);

	unsigned int dataSize = wavfile.dataChunkSize * sizeof(short);

	short *data = (short*)malloc(dataSize);

	fread(data, dataSize, 1, pFile);

	fclose(pFile);

 	if (wavfile.channel == 1) {
		//モノラル
		if (wavfile.bitType == 8) {
			//8ビット
			alBufferData(
				bid[sound],				//ALuint buffer
				AL_FORMAT_MONO8,	// ALenum format
				data,				//const ALvoid *data
				dataSize,			// ALsizei size
				wavfile.frequency);//ALsizei freq
		}
		else {
			//16ビット
			alBufferData(
				bid[sound],				//ALuint buffer
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
				bid[sound],				//ALuint buffer
				AL_FORMAT_STEREO8,	// ALenum format
				data,				//const ALvoid *data
				dataSize,		// ALsizei size
				wavfile.frequency);//ALsizei freq
		}
		else {
			//16ビット
			alBufferData(
				bid[sound],				//ALuint buffer
				AL_FORMAT_STEREO16,	// ALenum format
				data,				//const ALvoid *data
				dataSize,		// ALsizei size
				wavfile.frequency);//ALsizei freq
		}

	}
 	assert(alGetError() == AL_NO_ERROR);

	alSourcei(
		sid[sound],		//ALuint source
		AL_BUFFER,	//ALenum param
		bid[sound]);		//ALint value
	assert(alGetError() == AL_NO_ERROR);

	alSourcei(
		sid[sound],		//ALuint source
		AL_LOOPING,	//ALenum param
		AL_TRUE);	//ALint value

	assert(alGetError() == AL_NO_ERROR);

}


void WavFile::playMusic(unsigned char sound) {

	alSourcePlay(sid[sound]);//ALuint source
	assert(alGetError() == AL_NO_ERROR);

}


void WavFile::deleteMusic()
{
	alDeleteBuffers(
		BGM::SOUND_MAX,      // ALsizei n
		bid);  // const ALuint* buffers

	alDeleteSources(
		BGM::SOUND_MAX,          // ALsizei n
		sid);   // const ALuint* sources
}

const float WavFile::timeMusic(unsigned char sound) {

	float time;

	alGetSourcef(sid[sound], AL_SEC_OFFSET, &time);

	return time;

}

void WavFile::stopMusic(unsigned char sound) {

	alSourceStop(sid[sound]);	// ALuint source

}