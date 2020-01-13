#pragma once

#include "IPulsDistributer.h"

MOCK_BASE_CLASS(MockPulsDistributer, IPulsDistributer)
{
	MOCK_NON_CONST_METHOD(SetSeqList, 1, void(sequenceListTypdef ));
	MOCK_NON_CONST_METHOD(SetIndependentSubSequenceList, 1, void(const std::vector<std::shared_ptr<misSubSequence>>& ));
	MOCK_NON_CONST_METHOD(PulsPublish, 0, void(void));
	MOCK_NON_CONST_METHOD(SetLiInfo, 1, void(LicenseInformation ));
	MOCK_NON_CONST_METHOD(ForceUpdateInternalSDDIU, 0, void(void));
	MOCK_NON_CONST_METHOD(UpdateMuteKey, 0, void(void));
};
