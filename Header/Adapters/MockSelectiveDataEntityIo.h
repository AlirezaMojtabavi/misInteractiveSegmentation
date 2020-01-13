#pragma once

#include "ISelectiveDataEntityIo.h"

namespace parcast
{

	MOCK_BASE_CLASS(MockSelectiveDataEntityIo, ISelectiveDataEntityIo)
	{
		MOCK_NON_CONST_METHOD(GetAllSolutions, 0, std::vector<misSolutionProperty> ());
		MOCK_NON_CONST_METHOD(DeleteSolution, 1, void(const misUID& solutionUid));
		MOCK_NON_CONST_METHOD(SaveSolutionInformation, 0, void());
		MOCK_NON_CONST_METHOD(ReadSolutionInformation, 0, void());
		MOCK_NON_CONST_METHOD(SaveCoordSysCorrelations, 0, void());
		MOCK_NON_CONST_METHOD(ReadCoordSysCorrelations, 0, void());
		MOCK_NON_CONST_METHOD(SavePackages, 0, void());
		MOCK_NON_CONST_METHOD(ReadPackages, 0, void());
		MOCK_NON_CONST_METHOD(SaveImages, 0, void());
		MOCK_NON_CONST_METHOD(ReadImages, 0, void());
		MOCK_NON_CONST_METHOD(SaveImageContainedPolyDataList, 0, void());
		MOCK_NON_CONST_METHOD(ReadImageContainedPolyDataList, 0, void());
		MOCK_NON_CONST_METHOD(SaveVolumes, 0, void());
		MOCK_NON_CONST_METHOD(ReadVolumes, 0, void());
		MOCK_NON_CONST_METHOD(SavePlans, 0, void());
		MOCK_NON_CONST_METHOD(ReadPlans, 0, void());
		MOCK_NON_CONST_METHOD(SetImageSavingMode, 1, void(misSaveSolutionMode savingMode));
	};

}
