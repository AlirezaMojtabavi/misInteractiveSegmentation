#pragma once
#include "ILandamrkListCategorizer.h"
#include "misImageGeoProperties.h"

class misLandamrkListCategorizer : public ILandamrkListCategorizer
{
public:
	misLandamrkListCategorizer(std::shared_ptr<IImageGeoProperties> geoProp);
	misSimplePointListType GetLandamrks(misLandmarkType lndType,
	                                    const std::vector<std::shared_ptr<ILandmarkPointerRepresentation>>&) override;
private:
	std::shared_ptr<IImageGeoProperties> m_GeoProperties;
};
