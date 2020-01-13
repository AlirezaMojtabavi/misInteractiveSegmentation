#pragma once
#pragma once
#include "IVolumeColormapDataAccess.h"

#include "IDataBaseConnection.h"
#include "IVolumeVisibiltyQueryBuilder.h"
#include "IPackageVolumeQueryBuilder.h"
#include "IVolumeColormapQueryBuilder.h"
#include "VolumeColormap.h"
 
namespace parcast
{

	class VolumeColormapDataAccess : public IVolumeColormapDataAccess
	{
	public:
		VolumeColormapDataAccess(std::shared_ptr<IDataBaseConnection> dbConnection,
			std::shared_ptr<IVolumeColormapQueryBuilder> queryBuilder);

		void Insert(const VolumeColormap& data) override;
		std::vector<VolumeColormap> GetByVolumeUid(const std::string& uid) const override;

	private:
		std::shared_ptr<IVolumeColormapQueryBuilder> m_QueryBuilder;
		std::shared_ptr<IDataBaseConnection> m_DbConnection;
	};

}
