#pragma once

#include "IDataBaseConnection.h"
#include "ISolutionDataAccess.h"
#include "ISolutionQueryBuilder.h"

namespace  parcast
{
	class SolutionDataAccess : public ISolutionDataAccess
	{
	public:
		SolutionDataAccess(
			const std::shared_ptr<IDataBaseConnection> dbConnection, const std::shared_ptr<ISolutionQueryBuilder> dbQueryBuilder);
		~SolutionDataAccess();

		virtual std::vector<SolutionData> GetAll() override;
		virtual void InsertOrUpdate(const SolutionData& inSolutionData) override;
		virtual SolutionData GetById(const misUID& id) override;
		virtual void DeleteAll() override;
		virtual void DeleteById(const misUID& id) override;
		virtual bool PatientUidExists(const misUID& id) override;
	
	private:
		std::shared_ptr<IDataBaseConnection> m_DbConnection;
		std::shared_ptr<ISolutionQueryBuilder> m_DbQueryBuilder;

		void BindForInsert(std::shared_ptr<IDataBaseCommand> dbCommand, const SolutionData & inSolutionData);
		void BindForUpdate(std::shared_ptr<IDataBaseCommand> dbCommand, const SolutionData & inSolutionData);

		void InsertWithoutOpen(const SolutionData & inSolutionData);
		void UpdateWithoutOpen(const SolutionData & inSolutionData);
	};
}


