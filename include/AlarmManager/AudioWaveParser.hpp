/**
 * Copyright 2022-2032 by MICROPORT
 *
 * File Name:  	AudioWaveParse.hpp
 * File Path:
 * Author:		Richard Xie
 * Version:		1.0
 * Description:
 *
 * History:
 *  Date		Author			CR number	CR Title
 */

#ifndef AUDIOWAVEPARSER_H_
#define AUDIOWAVEPARSER_H_

#include <iostream>
#include <fstream>
#include "datatype.h"

using namespace std;

constexpr INT32 FileLen = 128;

struct RIFF
{
	INT8  riffId[4];         //contains identifier "RIFF"
	INT32 riffSize;         //File size minus 8 bytes
	INT8  riffFormat[4];     //contains identifier "WAVE"
};

struct FMT
{
	INT8 fmtId[4];          //contains identifier: "fmt " (with	space)
	INT32 fmtSize;          //contains the size of this block
};

struct WAVEFORM
{
	INT32	formatTag;         /* format type */
	INT32	channels;          /* number of channels (i.e. mono, stereo...) */

	INT32	samplesPerSec;     /* sample rate */
	INT32	avgBytesPerSec;    /* for buffer estimation */

	INT32	blockAlign;        /* block size of data */
	INT32	bitsPerSample;     /* number of bits per sample of mono data */
};

struct DATA
{
	char dataId[4];         	//contains identifier: "data"
	INT32 dataSize;            //data size
};


class AudioWaveParser
{

public:
	AudioWaveParser();
	~AudioWaveParser();
	void 	setFile(char *fileName);
	bool 	parseFile();
	bool 	parseHeader();
	INT32 	getChannel(){return channels;}
	INT32 	getSampleRate(){return samplesRate;}
	INT32	getBitSize(){return bitsPerSample;}
	INT32 	getData(INT8* buf, INT32 size);

private:
	bool readRiff();
	bool readFmt();
	bool readWave();
	bool readDataChunk();
	bool loadData();

private:
	ifstream 	fileStream;
	INT32		channels;           /* number of channels (i.e. mono, stereo...) */
	INT32       samplesRate;     	 /* sample rate */
	INT32       avgBytesPerSec;    /* for buffer estimation */
	INT32		blockAlign;        /* block size of data */
	INT32		bitsPerSample;    /* number of bits per sample of mono data */
	INT32       dataSize;
	INT8*       byteData;
	INT8		file[FileLen];
    FMT 		fmtStruct;	
};


#endif /* AUDIOWAVEPARSER_H_ */
