
#pragma once
#include "misHeader.h"
#include "misgoupviewerfourviwer.h"
#include "misSyncronViwer.h"
class misHybridInteractionObserver;

class MISDLLEXPORT misCompositeViewer : public misSyncronViwer
{

protected:

public:
	igstkStandardClassBasicTraitsMacro( misCompositeViewer, misGoupViewerFourViwer )   ;
	igstkNewMacro( Self );  

	virtual void InitilizeViewer();
	void AddAllPackageContent( misSimpleDataPackage* package );

	misCompositeViewer(void);
	~misCompositeViewer(void);
	

};
