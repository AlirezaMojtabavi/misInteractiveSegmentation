#pragma once
//#include "mishybridlandmarkviewer.h"
#include "misEnums.h"
#include "misManModelViewer.h"

class MISDLLEXPORT misHybridPlanLandmarkViewer :	public misManModelViewer/*misHybridLandmarkViewer*/
{
public:
	igstkStandardClassBasicTraitsMacro(misHybridPlanLandmarkViewer,misManModelViewer/*misHybridLandmarkViewer*/);
	igstkNewMacro(misHybridPlanLandmarkViewer);
	void AddRepresentation( misRepresentation* pRepresentation );

private:

	misHybridPlanLandmarkViewer(void);
	~misHybridPlanLandmarkViewer(void);

	//mis3DLabeRepresentationl::Pointer CreateLabelTexture( int index, double * position, double * lndLabelPosition );

	void UpdateBiopsyLine(void);
	
};
