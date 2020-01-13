#pragma once

#include "DentalSurgeryType.h"
#include "IDentalViewSideAnnotationTextBuilder.h"
#include "IPanoramicCoordinatesConverter.h"
#include "BusinessEntities\Vector.h"

namespace parcast
{

	class IDentalQuadrantFinder
	{
	public:
		virtual DentalQuadrant GetQuadrant(std::shared_ptr<const IPanoramicCoordinatesConverter> coordConv,
			bool isOblique, parcast::Vector<double, 3> planDirection, DentalSurgeryType surgeryType) const = 0;

		virtual ~IDentalQuadrantFinder() = default;
	};

}
