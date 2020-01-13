#pragma once

#include "misGUIEventConvertor.h"
#include "misSequenceManager.h"
#include "misSnapShotManager.h"

class misSnapShotProdecure :	public misSequenceManager
{
public:

	misSnapShotProdecure(misStrctTabModel tabModel, std::shared_ptr<misSoftwareInformation> softwareInformation);
	~misSnapShotProdecure(void);

	std::shared_ptr<misSnapShotManager> GetSnapShotManager(void);;
 
	bool ProcessRequest(misGUIEvent* pEvent);
	void Initialize(misStrctTabModel   dataTab,itk::Command* pCommand);


protected:
	std::shared_ptr<misSnapShotManager> m_SnapShotSubSequence;
	void CheckTabRepresentationExistance(void);


	misGUIEventConvertor* GetGuiConvertorList();
};

