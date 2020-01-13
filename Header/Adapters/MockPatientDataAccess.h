#pragma once

#include "PatientData.h"
#include "IPatientDataAccess.h"

namespace parcast
{
	MOCK_BASE_CLASS(MockPatientDataAccess, IPatientDataAccess)
	{
		MOCK_NON_CONST_METHOD(Update, 1, void(const PatientData & inPatientData));
		MOCK_NON_CONST_METHOD(InsertOrUpdate, 1, void(const PatientData & inPatientData));
		MOCK_NON_CONST_METHOD(Insert, 1, void(const PatientData & inPatientData));
		MOCK_CONST_METHOD(GetByUid, 1, PatientData(const std::string& patientUid));
		MOCK_CONST_METHOD(DeleteByUid, 1, void(const std::string& patientUid));
		MOCK_NON_CONST_METHOD(DeleteAll, 0, void(void));
	};
}

