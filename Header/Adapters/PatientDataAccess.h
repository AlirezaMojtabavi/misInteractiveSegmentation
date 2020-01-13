#pragma once

#include "IDataBaseConnection.h"
#include "IPatientDataAccess.h"
#include "IPatientQueryBuilder.h"

namespace parcast
{
	class PatientDataAccess : public IPatientDataAccess
	{
	public:
		PatientDataAccess(const std::shared_ptr<IDataBaseConnection> dbConnection, 
			const std::shared_ptr<IPatientQueryBuilder> dbQueryBuilder);
		~PatientDataAccess();

		virtual void Update(const PatientData & inPatientData) override;
		virtual void InsertOrUpdate(const PatientData & inPatientData) override;
		virtual void Insert(const PatientData & inPatientData) override;
		virtual PatientData GetByUid(const std::string& patientUid) const override;
		virtual void DeleteByUid(const std::string& patientUid) const override;
		virtual void DeleteAll() override;

	private:
		std::shared_ptr<IDataBaseConnection> m_DbConnection;
		std::shared_ptr<IPatientQueryBuilder> m_DbQueryBuilder;

		void BindCommandParameter(std::shared_ptr<IDataBaseCommand> dbCommand, const PatientData & inPatientData);
	};
}


