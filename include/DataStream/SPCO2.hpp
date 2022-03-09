///////////////////////////////////////////////////////////
//  SPCO2.h
//  Implementation of the Class SPCO2
//  Created on:      28-Jan-2022 10:40:19 AM
//  Original author: Richard Xie
///////////////////////////////////////////////////////////

#if !defined(EA_91D14FA8_BA56_43d0_9C23_1A1C090DF69E__INCLUDED_)
#define EA_91D14FA8_BA56_43d0_9C23_1A1C090DF69E__INCLUDED_

#include "IDataStream.hpp"

class SPCO2 : public IDataStream
{

public:
	SPCO2();
	virtual ~SPCO2();

	virtual Sample GetOneSample(int index);
	virtual bool AttachOneSample(Sample sample);

	virtual INT32 loadData();
	virtual bool saveData();
	virtual bool clearData();
};
#endif // !defined(EA_91D14FA8_BA56_43d0_9C23_1A1C090DF69E__INCLUDED_)
