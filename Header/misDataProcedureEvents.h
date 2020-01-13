#ifndef __misdataProcedureEvents__
#define __misdataProcedureEvents__

#include "misCoreEvents.h"
#include "misDataProdecureEnum.h"
#include "misRotationInformation.h"
#include "misStrctImageData.h"

struct misCounter
{
		int SelectCounter;

		misCounter()
		{
			this->SelectCounter = -1;
		}
};

#pragma warning (push)
#pragma warning (disable : 4800)

//Data Uploading Event

//igstkLoadedEventMacro( misSetGUIState,					  misEvent,std::string );

igstkLoadedEventMacro(misSliderChangedClicked, misEvent,double );

//DataChecking Event

itkEventMacro(misRequestShowLoadedSeriInGUI,misEvent);

igstkLoadedEventMacro(misRotationData,misEvent,misRotationInformation);

//Image Correlation Event
itkEventMacro(misRequestShowLoadedSeriInCorrelationGUI,misEvent);

#pragma warning (push)

#endif
