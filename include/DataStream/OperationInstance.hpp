///////////////////////////////////////////////////////////
//  OperationInstance.h
//  Implementation of the Class OperationInstance
//  Created on:      28-Jan-2022 10:40:20 AM
//  Original author: Richard Xie
///////////////////////////////////////////////////////////

#if !defined(EA_A340E538_733B_49f0_88DA_FF5F15919275__INCLUDED_)
#define EA_A340E538_733B_49f0_88DA_FF5F15919275__INCLUDED_

#include "IBMOperation.hpp"
#include "WorkThread.hpp"

class OperationInstance : public IBMOperation, public WorkThread
{
private:
	OperationInstance();
public:

	virtual ~OperationInstance();

	virtual bool loadData();
	virtual INT32 saveData();
	bool clearData();

	static OperationInstance *getInstance();
protected:
	// You must implement this method
    INT32U run();
};
#endif // !defined(EA_A340E538_733B_49f0_88DA_FF5F15919275__INCLUDED_)
