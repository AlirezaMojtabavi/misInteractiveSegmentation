#pragma once

#include "IDentalQuadrantFinder.h"
#include "IDentalViewSideAnnotationTextBuilder.h"
#include "BusinessEntities\Vector.h"

namespace parcast
{

	class DentalQuadrantFinder : public IDentalQuadrantFinder
	{
	public:
		DentalQuadrant GetQuadrant(std::shared_ptr<const IPanoramicCoordinatesConverter> coordConv,
			bool isOblique, parcast::Vector<double, 3> planDirection, DentalSurgeryType surgeryType) const override;

	private:
		bool IsUpperJaw(bool isOblique, parcast::Vector<double, 3> planDirection, DentalSurgeryType surgeryType) const;
	};

}
