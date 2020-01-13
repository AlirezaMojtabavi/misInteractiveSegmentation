#pragma once
#include "IVertebraScrewPlanDataIterator.h"

MOCK_BASE_CLASS( MockVertebraScrewPlanDataIterator ,IVertebraScrewPlanDataIterator)
{
	MOCK_NON_CONST_METHOD(DoForSelectedVertebraScrewPlan, 2, void (IVertebraScrewPlanDataIterator::FunctionType,
		std::shared_ptr<ISimpleDataPackage> )) ;

};
