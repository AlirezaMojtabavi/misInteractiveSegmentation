#pragma once

#include "misHomeSubSeq.h"
#include "misSequenceManager.h"

class misHomeProdecure : public misSequenceManager
{

public:
	misHomeProdecure(misStrctTabModel tabModel, std::shared_ptr<misSoftwareInformation> softwareInformation);
	~misHomeProdecure(void) = default;
	misGUIEventConvertor* GetGuiConvertorList();

	bool ProcessRequest(misGUIEvent* pEvent);
	std::shared_ptr<misHomeSubSeq> GetHomeSubSequence(void);


protected:
	std::shared_ptr<misHomeSubSeq> m_HomeSubSequence;
	void CheckTabRepresentationExistance(void);



};

