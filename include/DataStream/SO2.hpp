///////////////////////////////////////////////////////////
//  SO2.h
//  Implementation of the Class SO2
//  Created on:      28-Jan-2022 10:40:19 AM
//  Original author: Richard Xie
///////////////////////////////////////////////////////////

#if !defined(EA_E2ADB566_63C5_417d_B709_1D406B56B583__INCLUDED_)
#define EA_E2ADB566_63C5_417d_B709_1D406B56B583__INCLUDED_

#include "IDataStream.hpp"

class SO2 : public IDataStream
{

public:
	SO2();
	virtual ~SO2();

	virtual Sample GetOneSample(int index);
	virtual bool AttachOneSample(Sample sample);

	virtual INT32 loadData();
	virtual bool saveData();
	virtual bool clearData();
};
#endif // !defined(EA_E2ADB566_63C5_417d_B709_1D406B56B583__INCLUDED_)
