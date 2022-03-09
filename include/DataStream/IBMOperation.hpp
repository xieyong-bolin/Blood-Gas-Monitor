///////////////////////////////////////////////////////////
//  IOperation.h
//  Implementation of the Interface IOperation
//  Created on:      28-Jan-2022 10:40:20 AM
//  Original author: Richard Xie
///////////////////////////////////////////////////////////

#if !defined(EA_25E40C18_A663_4c1a_8877_BFBFAB447DCC__INCLUDED_)
#define EA_25E40C18_A663_4c1a_8877_BFBFAB447DCC__INCLUDED_

#include "Temp.hpp"
#include "HCT.hpp"
#include "KPlus.hpp"
#include "PH.hpp"
#include "SPO2.hpp"
#include "SPCO2.hpp"
#include "SO2.hpp"
#include "datatype.h"

enum class Parameter
{
	HCT,
	KPlus,
	PH,
	SO2,
	SPCO2,
	SPO2,
	Temp
};


class IBMOperation
{

public:
	IBMOperation() {

	}

	virtual ~IBMOperation() {

	}

	virtual bool loadData() = 0;
	virtual INT32 saveData() = 0;

public:
	Temp 	*temp;
	HCT 	*hct;
	KPlus 	*kplus;
	PH 		*ph;
	SPO2 	*spo2;
	SPCO2 	*spco2;
	SO2 	*so2;
};
#endif // !defined(EA_25E40C18_A663_4c1a_8877_BFBFAB447DCC__INCLUDED_)
