///////////////////////////////////////////////////////////
//  Temp.h
//  Implementation of the Class Temp
//  Created on:      28-Jan-2022 10:40:19 AM
//  Original author: Richard Xie
///////////////////////////////////////////////////////////

#if !defined(EA_9C1C24CD_093A_4b3a_8CD5_407651ADBEA1__INCLUDED_)
#define EA_9C1C24CD_093A_4b3a_8CD5_407651ADBEA1__INCLUDED_

#include "IDataStream.hpp"

class Temp : public IDataStream
{

public:
	Temp();
	virtual ~Temp();

	virtual Sample GetOneSample(int index);
	virtual bool AttachOneSample(Sample sample);

	virtual INT32 loadData();
	virtual bool saveData();
	virtual bool clearData();
};
#endif // !defined(EA_9C1C24CD_093A_4b3a_8CD5_407651ADBEA1__INCLUDED_)
