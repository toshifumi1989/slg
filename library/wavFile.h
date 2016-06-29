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

extern WavFile *bgm;
extern void initMusic();

#endif