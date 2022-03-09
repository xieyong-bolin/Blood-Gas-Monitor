///////////////////////////////////////////////////////////
//  HCT.h
//  Implementation of the Class HCT
//  Created on:      28-Jan-2022 10:40:19 AM
//  Original author: Richard Xie
///////////////////////////////////////////////////////////

#if !defined(EA_DAB40028_1D49_47ff_8437_D474A6E5A23E__INCLUDED_)
#define EA_DAB40028_1D49_47ff_8437_D474A6E5A23E__INCLUDED_

#include "IDataStream.hpp"

class HCT : public IDataStream
{

public:
	HCT();
	virtual ~HCT();

	virtual Sample GetOneSample(int index);
	virtual bool AttachOneSample(Sample sample);

	virtual INT32 loadData();
	virtual bool saveData();
	virtual bool clearData();
};
#endif // !defined(EA_DAB40028_1D49_47ff_8437_D474A6E5A23E__INCLUDED_)
