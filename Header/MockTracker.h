#pragma  once
#include "ITracker.h"

MOCK_BASE_CLASS(MockTracker, ITracker)
{
	MOCK_CONST_METHOD(InterferenceExists, 0, bool(void));
	MOCK_CONST_METHOD(GetUID, 0, std::string (void));
	MOCK_NON_CONST_METHOD(SetUID, 1, void (std::string));
	MOCK_NON_CONST_METHOD(StopTracking, 0, bool());
	MOCK_NON_CONST_METHOD(StartTracking, 0, bool());
	MOCK_CONST_METHOD(HasObserver, 1, bool (const itk::EventObject & ));
	MOCK_NON_CONST_METHOD(AddObserver, 2, unsigned long (const itk::EventObject & , itk::Command *));
	MOCK_NON_CONST_METHOD(AddObservers, 2,  unsigned long (const std::vector< itk::EventObject*>& events,
		itk::Command *) );
	MOCK_NON_CONST_METHOD(RemoveAllObservers, 0, void());
	MOCK_NON_CONST_METHOD(Connect, 1, bool(misStrctComConnectionOptions));
	MOCK_NON_CONST_METHOD(Reset, 0, bool());
	MOCK_NON_CONST_METHOD( Close, 0, bool() );
	MOCK_NON_CONST_METHOD(InvokeEvent, 1, void(const itk::EventObject &));
	MOCK_NON_CONST_METHOD(AddToolToTracker, 1, bool(std::shared_ptr<ITrackingTool>));
	MOCK_NON_CONST_METHOD(GetTracker, 0, igstk::Tracker*(void));

};