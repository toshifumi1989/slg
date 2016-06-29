#ifndef WAVFILE_H
#define WAVFILE_H

#include "../AL/al.h"
#include "../AL\alc.h"

#pragma comment(lib,"OpenAL32.lib") 

enum BGM
{
	TITLE_BGM,
	SETUP_BGM,
	BATTLE_BGM,
	RESULT_BGM,
	SOUND_MAX
};

extern ALCdevice *device;
extern ALCcontext *context;
extern ALCuint bid[BGM::SOUND_MAX];
extern ALuint sid[BGM::SOUND_MAX];



class WavFile 
{
public:
	WavFile(){}
	~WavFile() {}

	void readSound(const char* music ,unsigned char sound);
	void playMusic(unsigned char sound);
	void deleteMusic();
	const float timeMusic(unsigned char sound);
	void stopMusic(unsigned char sound);

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

extern WavFile *bgm;
extern void initMusic();

#endif