///////////////////////////////////////////////////////////
//  PH.h
//  Implementation of the Class PH
//  Created on:      28-Jan-2022 10:40:19 AM
//  Original author: Richard Xie
///////////////////////////////////////////////////////////

#if !defined(EA_57949B85_8F02_4e29_89A8_B9F6E9DEC548__INCLUDED_)
#define EA_57949B85_8F02_4e29_89A8_B9F6E9DEC548__INCLUDED_

#include "IDataStream.hpp"

class PH : public IDataStream
{

public:
	PH();
	virtual ~PH();

	virtual Sample GetOneSample(int index);
	virtual bool AttachOneSample(Sample sample);

	virtual INT32 loadData();
	virtual bool saveData();
	virtual bool clearData();
};
#endif // !defined(EA_57949B85_8F02_4e29_89A8_B9F6E9DEC548__INCLUDED_)
