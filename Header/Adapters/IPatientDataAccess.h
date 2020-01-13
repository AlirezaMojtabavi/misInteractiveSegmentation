#pragma once

#include "PatientData.h"

namespace parcast
{
	class IPatientDataAccess
	{
	public:

		virtual void Update(const PatientData & inPatientData) = 0;
		virtual void InsertOrUpdate(const PatientData & inPatientData) = 0;
		virtual void Insert(const PatientData & inPatientData) = 0;
		virtual PatientData GetByUid(const std::string& patientUid) const = 0;
		virtual void DeleteByUid(const std::string& patientUid) const = 0;
		virtual void DeleteAll() = 0;
		virtual ~IPatientDataAccess() {}
	};
}


