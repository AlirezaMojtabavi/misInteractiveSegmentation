#pragma once
#include "misHeader.h"
#include "misgoupviewerfourviwer.h"
#include "misGroupViewLandMark.h"
#include "misRegisterManagerTypes.h"
#include "misitkTypdef.h"


class MISDLLEXPORT misLandmarkRegistrationViewing:	public misGroupViewLandMark
{

protected:
	misSeedRepresentation::Pointer                m_RegisterdPointSeedRep;
	vector<misSeedRepresentation::Pointer>         m_SeedList;

public:

	misLandmarkRegistrationViewing();
	igstkStandardClassBasicTraitsMacro( misLandmarkRegistrationViewing,misGroupViewLandMark) ;
	igstkNewMacro(Self);

	// used for correct camera position
	void  SetRegistrationErrorLandmark(double* mainPosition , double* finalRegisteredPosition);
	//void  SetRegistrationErrorLandmark(double finalRegisteredPosition[3]);

	void  HideRegistrationErrorLandmark(void);

	void HideLandmarks(void);
	void HideVolume();
	void ShowVolume();

	void UpdateSurfaceLandmarks(misSurfaceLandMarkListType landmarkList);
	void ClearSurfcaeLandmarks(void);
	void DeleteLastSurfcaeLandmarks(void);
	void AddNewSurfaceLandmark(double position[3]);
	//virtual void InitilizeViewer();

 
	 
};
//===============
