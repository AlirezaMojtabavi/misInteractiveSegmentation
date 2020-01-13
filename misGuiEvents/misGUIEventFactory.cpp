#include "StdAfx.h"
#include "misGUIEventFactory.h"

#include "ReadNewSolutionEvent.h"
#include "misDataSelectionPackageDataSelectedEvent.h"
#include "misEventFromGui.h"
#include "misGuiEvent.h"
#include "misTabSelctionEvents.h"
#include "misViwingSliceChangeEvent.h"


misGUIEventFactory::misGUIEventFactory(void)
{
}


misGUIEventFactory::~misGUIEventFactory(void)
{
}

misGUIEvent* misGUIEventFactory::CreateElement( std::string type )
{

	if (type=="misSubTabSelectionChange")
	{
		return new misSubTabSelectionChange();
	}
	else if (type=="misViwingSliceChangeEvent")
		{
			return new misViwingSliceChangeEvent();
		}
	//
	else if (type=="misTabSelectionChange")
	{
		return new misTabSelectionChange();
	}
	else if (type=="ReadNewSolutionEvent")
	{
		return new ReadNewSolutionEvent();
	}
	else if (type=="misSliderEvent")
	{
		return new misSliderEvent();
	}

	else if (type=="misRequestVolumeTypeInRegistration")
	{
		return new misRequestVolumeTypeInRegistration();
	}
	else if (type=="misSetNormalizedVolumeThresholdEvent")
	{
		return new misSetNormalizedVolumeThresholdEvent();
	}
	else if (type=="misDataSelectionPackageDataSelectedEvent")
	{
		return new misDataSelectionPackageDataSelectedEvent();
	}
	else if (type=="misPackageListEvent")
	{
		return new misPackageListEvent();
	}
	else if (type=="UpdateAutomaticCaptureLandmarkSettingEvent")
	{
		return new UpdateAutomaticCaptureLandmarkSettingEvent();
	}
	else if (type=="misTakeSnapShotEvent")
	{
		return new misTakeSnapShotEvent();
	}

	
	return  NULL;

}
