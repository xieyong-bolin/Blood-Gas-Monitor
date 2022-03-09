/**
 * Copyright 2022-2032 by MICROPORT
 *
 * File Name:  	AudioWaveParse.cpp
 * File Path:
 * Author:		Richard Xie
 * Version:		1.0
 * Description:
 *
 * History:
 *  Date		Author			CR number	CR Title
 */
#include <assert.h>
#include <string.h>
#include "AudioWaveParser.hpp"

AudioWaveParser::AudioWaveParser()
{
    byteData = NULL;
    memset(file, 0, sizeof(file));
}


AudioWaveParser::~AudioWaveParser()
{
    delete byteData;
    byteData = nullptr;
}


void AudioWaveParser::setFile(char* fileName)
{
	memset(file, 0, sizeof(file));
	snprintf(file, sizeof(file), "%s", fileName);
}

//read RIFF
bool AudioWaveParser::readRiff()
{
    RIFF riffStruct;

    memset(riffStruct.riffId,0x00,sizeof(riffStruct.riffId));
    memset(riffStruct.riffFormat,0x00,sizeof(riffStruct.riffFormat));
    fileStream.read(riffStruct.riffId,4);
    if (riffStruct.riffId[0] != 'R' || riffStruct.riffId[1] != 'I' || riffStruct.riffId[2] != 'F' || riffStruct.riffId[3] !='F')
    {
        fileStream.close();
        return false;
    }

    fileStream.read(reinterpret_cast<char*>(&riffStruct.riffSize), sizeof(riffStruct.riffSize));
    if ( riffStruct.riffSize <= 0 )
    {
        fileStream.close();
        return false;
    }

    fileStream.read(riffStruct.riffFormat,4);
    if (riffStruct.riffFormat[0] != 'W'||riffStruct.riffFormat[1] != 'A' || riffStruct.riffFormat[2] != 'V'|| riffStruct.riffFormat[3] != 'E')
    {
        fileStream.close();
        return false;
    }

    return true;
}


//read FMT
bool AudioWaveParser::readFmt()
{
    memset(fmtStruct.fmtId, 0x00, sizeof(fmtStruct.fmtId));
    fileStream.read(fmtStruct.fmtId,4);

    if (fmtStruct.fmtId[0]!= 'f' || fmtStruct.fmtId[1] != 'm' || fmtStruct.fmtId[2] != 't')
    {
        fileStream.close();
        return false;
    }

    fileStream.read(reinterpret_cast<char *>(&fmtStruct.fmtSize), sizeof(fmtStruct.fmtSize));
    if (fmtStruct.fmtSize != 18 && fmtStruct.fmtSize != 16)
    {
        fileStream.close();
        return false;
    }

    return true;
}


//read WAVFORMAT
bool AudioWaveParser::readWave()
{
    WAVEFORM  waveformStruct;

    fileStream.read(reinterpret_cast<char *>(&waveformStruct.formatTag),sizeof(waveformStruct.formatTag));
    if(waveformStruct.formatTag != 1)
    {
        fileStream.close();
        return false;
    }
    fileStream.read(reinterpret_cast<char *>(&waveformStruct.channels),sizeof(waveformStruct.channels));
    channels = waveformStruct.channels;

    fileStream.read(reinterpret_cast<char *>(&waveformStruct.samplesPerSec),sizeof(waveformStruct.samplesPerSec));
    samplesRate = waveformStruct.samplesPerSec;

    fileStream.read(reinterpret_cast<char *>(&waveformStruct.avgBytesPerSec),sizeof(waveformStruct.avgBytesPerSec));
    avgBytesPerSec  = waveformStruct.avgBytesPerSec;

    fileStream.read(reinterpret_cast<char *>(&waveformStruct.blockAlign),sizeof(waveformStruct.blockAlign));
    blockAlign = waveformStruct.blockAlign;

    fileStream.read(reinterpret_cast<char *>(&waveformStruct.bitsPerSample),sizeof(waveformStruct.bitsPerSample));
    bitsPerSample = waveformStruct.bitsPerSample;
    if (fmtStruct.fmtSize == 18)
    {
    	INT32 additionalInfo (0);
    	fileStream.read(reinterpret_cast<char *>(&additionalInfo),sizeof(additionalInfo));
    }

    return true;
}


bool AudioWaveParser::readDataChunk()
{
    DATA dataStruct;

    memset(dataStruct.dataId,0x00,sizeof(dataStruct.dataId));
    fileStream.read(dataStruct.dataId,4);

    if (dataStruct.dataId[0] != 'd' || dataStruct.dataId[1] != 'a' || dataStruct.dataId[2] != 't' || dataStruct.dataId[3] != 'a')
    {
        fileStream.close();
        return false;
    }

    fileStream.read(reinterpret_cast<char *>(&dataStruct.dataSize), sizeof(dataStruct.dataSize));
    if (dataStruct.dataSize <= 0)
    {
        fileStream.close();
        return false;
    }
    dataSize = dataStruct.dataSize;

    return true;
}


bool AudioWaveParser::loadData()
{
	delete byteData;
    byteData = nullptr;

	byteData = new INT8[dataSize];
	if (byteData == nullptr)
	{
		fileStream.close();
		return false;
	}
	fileStream.read(static_cast<char*>(byteData), dataSize);

    return true;
}


bool AudioWaveParser::parseFile()
{
	fileStream.open(file,ios::binary);
	if (fileStream.fail())
		return false;

    if( !readRiff() )
         return false;

    if (!readFmt())
        return false;

    if (!readWave())
        return false;

    if (!readDataChunk())
        return false;

    if (!loadData())
        return false;

    fileStream.close();
    return true;
}


//you should make sure the length is long enough.
int AudioWaveParser::getData(INT8* buf, INT32 size)
{
	assert( buf != nullptr );

	assert( static_cast<INT32U>(size) >= dataSize);
	memcpy(buf, byteData, dataSize);

	return dataSize;
}
