#include "stdafx.h"
#include "misLandamrkListCategorizer.h"
#include "I3DImageRenderer.h"
#include "misImageGeoProperties.h"

misLandamrkListCategorizer::misLandamrkListCategorizer(std::shared_ptr<IImageGeoProperties> geoProp)
	:m_GeoProperties(geoProp)
{
}

misSimplePointListType misLandamrkListCategorizer::GetLandamrks(misLandmarkType lndType,
	const std::vector<std::shared_ptr<ILandmarkPointerRepresentation>>& landMarkList, const std::shared_ptr<IImage> pImage)
{
	misSimplePointListType  res;
	for (auto landmark : landMarkList)
	{
		misSimplePointType seed;

		if (landmark->GetCategory() == lndType)
		{

			double pos[3];
			landmark->GetPosition(pos);
			int*  indexes = m_GeoProperties->GetIndexes(pos);
			seed[0] = indexes[0];
			seed[1] = indexes[1];
			seed[2] = indexes[2];
			seed.validity = landmark->IsValid();
			res.push_back(seed);
		}

	}
	return  res;
}
