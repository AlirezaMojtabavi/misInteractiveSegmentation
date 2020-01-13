#pragma once
#include "ITrackerConfigure.h"

MOCK_BASE_CLASS(MockTrackerToolUtility, ITrackerConfigure)
{
	MOCK_NON_CONST_METHOD(DeleteTool, 1, void (misStrctSimpleToolProperties ) );
	MOCK_NON_CONST_METHOD(AddObserversAddTools, 1, void (misToolPropertiesListTypdef ));
	MOCK_NON_CONST_METHOD(MakeAndSendAddEvent, 1, void (std::shared_ptr<ITrackingTool>) );
	MOCK_NON_CONST_METHOD(AddToolList, 1,  std::vector<std::shared_ptr<ITrackingTool>> (misToolPropertiesListTypdef));
	MOCK_NON_CONST_METHOD(MakeTool, 1, std::shared_ptr<ITrackingTool>(misToolProperties));
	MOCK_NON_CONST_METHOD(ReconnectTracker, 0 , void());
	MOCK_NON_CONST_METHOD(ResetTracker, 0, bool ());
};