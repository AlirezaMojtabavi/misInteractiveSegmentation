#pragma once

#include "IImageContainedDataAccess.h"

#include "IDataBaseConnection.h"
#include "IImageContainedQueryBuilder.h"

namespace parcast
{

	class ImageContainedDataAccess : public IImageContainedDataAccess
	{
	public:
		ImageContainedDataAccess(std::shared_ptr<IDataBaseConnection> connection, std::shared_ptr<IImageContainedQueryBuilder> queryBuilder);

		void Insert(const ImageContainedData& data) override;
		std::vector<ImageContainedData> GetBySolutionUid(const std::string& uid) override;

	private:
		std::shared_ptr<IDataBaseConnection> m_DbConnection;
		std::shared_ptr<IImageContainedQueryBuilder> m_QueryBuilder;
	};

}
