#pragma once
#include "IUpdateLayoutToDynamicLayout.h"
MOCK_BASE_CLASS(MockUpdateLayoutToDynamicLayout, IUpdateLayoutToDynamicLayout)
{
	MOCK_NON_CONST_METHOD(Update, 5, void (const std::string& , double , bool ,std::shared_ptr<ISimpleDataPackage>, std::shared_ptr< IVolumeCropping>) );

};
