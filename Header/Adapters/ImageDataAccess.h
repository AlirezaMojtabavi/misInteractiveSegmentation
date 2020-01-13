#pragma once

#include "IDataBaseConnection.h"
#include "IImageDataAccess.h"
#include "IImageQueryBuilder.h"

namespace parcast
{
	
	class ImageDataAccess : public IImageDataAccess
	{
	public:
		ImageDataAccess(
			const std::shared_ptr<IDataBaseConnection> dbConnection, const std::shared_ptr<IImageQueryBuilder> dbQueryBuilder);
		~ImageDataAccess();

		virtual void InsertOrUpdate(const ImageData & inImageData) override;
		virtual void Delete(const std::string& FK_SolutionUid, const std::string& ImageUid) override;
		virtual std::vector<ImageData> GetBySolutionUid(const std::string& solutionUid) const override;
		virtual std::vector<std::string> GetUidsBySolutionUid(const std::string& solutionUid) const override;
		
	private:
		std::shared_ptr<IDataBaseConnection> m_DbConnection;
		std::shared_ptr<IImageQueryBuilder> m_DbQueryBuilder;

		void BindParams(std::shared_ptr<IDataBaseCommand> dbCommand, const ImageData & inImageData);

		void InsertWithoutOpen(const ImageData & inImageData);
		void UpdateWithoutOpen(const ImageData & inImageData);
	};

}
