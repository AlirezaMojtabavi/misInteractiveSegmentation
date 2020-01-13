#pragma once
#include "IConfirmedImageCounter.h"

MOCK_BASE_CLASS(MockConfirmedImageCounter, IConfirmedImageCounter)
{
	MOCK_NON_CONST_METHOD(IsThereAnyUnconfirmedImage, 1,bool (std::shared_ptr<ISimpleDataPackage>) );

};
