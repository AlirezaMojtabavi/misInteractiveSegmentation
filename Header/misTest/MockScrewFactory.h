#pragma once
#include "IScrewCreator.h"

MOCK_BASE_CLASS(MockScrewFactory, IScrewCreator)
{
	MOCK_NON_CONST_METHOD(CreateScrew, 3, std::weak_ptr<parcast::IPlan>(std::shared_ptr<ISimpleDataPackage>, const misColorStruct&, double));
};
