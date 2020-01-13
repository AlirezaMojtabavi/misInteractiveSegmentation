#pragma once

#include "misEntSpineNavigationSubSequence.h"
#include "misSequenceManager.h"

class misEntSpineNavigationSequence : public misSequenceManager
{
public:

	igstkStandardClassBasicTraitsMacro( misEntSpineNavigationSequence, misSequenceManager );
 
	virtual void Initialize(misStrctTabModel   dataTab,itk::Command* pCommand);
	misEntSpineNavigationSubSequence*  GetNavigationManager(void){return this->m_NavigationSubSequence;};

	static Pointer New();


protected:
	misEntSpineNavigationSubSequence::Pointer    m_NavigationSubSequence;


	misEntSpineNavigationSequence();
	~misEntSpineNavigationSequence();

private:


public:
	virtual bool ProcessRequest(misGUIEvent* pEvent);
//	 virtual void UpdateStatus();
	misGUIEventConvertor* GetGuiConvertorList();

};



