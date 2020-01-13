#pragma once
#include "IScrewPlanDisplayer.h"

MOCK_BASE_CLASS( MOckScrewDisplayer ,IScrewDisplayer)
{
	MOCK_NON_CONST_METHOD(ShowScrews, 1, void (std::shared_ptr<ISimpleDataPackage> package) );
 
};
