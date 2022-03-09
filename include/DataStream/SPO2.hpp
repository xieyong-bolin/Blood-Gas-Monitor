///////////////////////////////////////////////////////////
//  SPO2.h
//  Implementation of the Class SPO2
//  Created on:      28-Jan-2022 10:40:19 AM
//  Original author: Richard Xie
///////////////////////////////////////////////////////////

#if !defined(EA_2FB4F6C8_12FA_4075_90F5_C52DF6FF9150__INCLUDED_)
#define EA_2FB4F6C8_12FA_4075_90F5_C52DF6FF9150__INCLUDED_

#include "IDataStream.hpp"

class SPO2 : public IDataStream
{

public:
	SPO2();
	virtual ~SPO2();

	virtual Sample GetOneSample(int index);
	virtual bool AttachOneSample(Sample sample);

	virtual INT32 loadData();
	virtual bool saveData();
	virtual bool clearData();
};
#endif // !defined(EA_2FB4F6C8_12FA_4075_90F5_C52DF6FF9150__INCLUDED_)
