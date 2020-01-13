#pragma once
#include "misgoupviewerfourviwer.h"
#include "misHybridInteractionObserver.h"
#include "misHybridLandmarkViewer.h"
#include "misViwerObserevr.h"
#include "misGroupViewLandMark.h"
#include "misHeader.h"
//================================================================================
class MISDLLEXPORT misLandmarlSelectionViewer :
	 public misGroupViewLandMark
{
public:

	igstkStandardClassBasicTraitsMacro( misLandmarlSelectionViewer,misGroupViewLandMark) ;
	igstkNewMacro( Self );  
	virtual ~misLandmarlSelectionViewer();


};
//=================================================================================