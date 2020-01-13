#pragma once

#include "ISegmentedImageDataAccess.h"

namespace parcast
{

	class IDataBaseConnection;
	class ISegmentedImageQueryBuilder;

	class SegmentedImageDataAccess : public ISegmentedImageDataAccess
	{
	public:
		SegmentedImageDataAccess(const std::shared_ptr<IDataBaseConnection> dbConnection,
			const std::shared_ptr<ISegmentedImageQueryBuilder> dbQueryBuilder);

		std::vector<std::string> GetUidsBySolutionUid(const std::string & solutionUid) const;
		virtual void InsertOrUpdate(const SegmentedImageData & inImageData) override;
		virtual SegmentedImageData GetByImageUid(const std::string& imageUid) const override;
 
	private:
		std::shared_ptr<IDataBaseConnection> m_DbConnection;
		std::shared_ptr<ISegmentedImageQueryBuilder> m_QueryBuilder;
	};

}