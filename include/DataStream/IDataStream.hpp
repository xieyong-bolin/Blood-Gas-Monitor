///////////////////////////////////////////////////////////
//  IDataStream.h
//  Implementation of the Interface IDataStream
//  Created on:      28-Jan-2022 10:40:19 AM
//  Original author: Richard Xie
///////////////////////////////////////////////////////////

#if !defined(EA_6FFDD1A2_3A9B_4308_B613_8645F9513A8F__INCLUDED_)
#define EA_6FFDD1A2_3A9B_4308_B613_8645F9513A8F__INCLUDED_

#include "datatype.h"
#include <time.h>
#include <vector>

using namespace std;

typedef struct sample
{

time_t timeStamp;

INT32 Value;

}Sample,*pSample;


class IDataStream
{

public:
	std::vector<Sample> dataBuffer;
public:
	IDataStream(){}
	virtual ~IDataStream(){}
	virtual Sample GetOneSample(int index) =0;
	virtual bool AttachOneSample(Sample sample) =0;

	virtual INT32 loadData() = 0;
	virtual bool saveData() = 0;
	virtual bool clearData() = 0;
};
#endif // !defined(EA_6FFDD1A2_3A9B_4308_B613_8645F9513A8F__INCLUDED_)
