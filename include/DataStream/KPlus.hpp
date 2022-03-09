///////////////////////////////////////////////////////////
//  K+.h
//  Implementation of the Class KPuls
//  Created on:      28-Jan-2022 10:40:20 AM
//  Original author: Richard Xie
///////////////////////////////////////////////////////////

#if !defined(EA_4186C686_B292_449a_ABB6_1523AE5A7DFC__INCLUDED_)
#define EA_4186C686_B292_449a_ABB6_1523AE5A7DFC__INCLUDED_

#include "IDataStream.hpp"

class KPlus : public IDataStream
{

public:
	KPlus();
	virtual ~KPlus();

	virtual Sample GetOneSample(int index);
	virtual bool AttachOneSample(Sample sample);

	virtual INT32 loadData();
	virtual bool saveData();
	virtual bool clearData();
};
#endif // !defined(EA_4186C686_B292_449a_ABB6_1523AE5A7DFC__INCLUDED_)
