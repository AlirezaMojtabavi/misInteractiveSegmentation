#pragma once

#include "IVolumeDataAccess.h"

#include "IDataBaseConnection.h"
#include "IVolumeQueryBuilder.h"

namespace parcast
{

	class VolumeDataAccess : public IVolumeDataAccess
	{
	public:
		VolumeDataAccess(std::shared_ptr<IDataBaseConnection> connection, std::shared_ptr<IVolumeQueryBuilder> queryBuilder);

		void Insert(const VolumeData& data) override;
		std::vector<VolumeData> GetBySolutionUid(const std::string& uid) override;

	private:
		std::shared_ptr<IDataBaseConnection> m_DbConnection;
		std::shared_ptr<IVolumeQueryBuilder> m_QueryBuilder;
	};

}
