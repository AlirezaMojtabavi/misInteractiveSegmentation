#pragma once
#pragma once
#include "IImageContainedPropertiesDataAccess.h"
#include "IDataBaseConnection.h"
#include "IImageContainedPropertiesQueryBuilder.h"
#include "ImageContainedProperties.h"

namespace parcast
{

	class ImageContainedPropertiesDataAccess : public IImageContainedPropertiesDataAccess
	{
	public:
		ImageContainedPropertiesDataAccess(std::shared_ptr<IDataBaseConnection> dbConnection,
			std::shared_ptr<IImageContainedPropertiesQueryBuilder> queryBuilder);

		void Insert(const ImageContainedProperties& data) override;
		std::vector<ImageContainedProperties> GetByImageContainedUid(const std::string& uid) const override;

	private:
		std::shared_ptr<IImageContainedPropertiesQueryBuilder> m_QueryBuilder;
		std::shared_ptr<IDataBaseConnection> m_DbConnection;
	};

}
