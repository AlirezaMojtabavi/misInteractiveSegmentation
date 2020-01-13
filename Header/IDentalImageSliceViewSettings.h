#pragma once

class IPanoramicCoordinatesConverter;
enum class DentalSurgeryType;

class IDentalImageSliceViewSettings
{
public:
	virtual void SetPanoramicCoordinateConverter(std::shared_ptr<const IPanoramicCoordinatesConverter> coordinateConverter) = 0;
	virtual void SetDentalSurgeryType(DentalSurgeryType surgeryType) = 0;

	virtual ~IDentalImageSliceViewSettings() {}
};
