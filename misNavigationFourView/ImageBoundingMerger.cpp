#include "stdafx.h"

#include "ImageBoundingMerger.h"
#include "misImageIOProperties.h"

using namespace parcast;

ImageBoundingProperty ImageBoundingMerger::Merge(std::shared_ptr<IImage> image1, std::shared_ptr<IImage> image2)
{
	auto ioProps1 = image1->GetImageIOProperties();
	auto ioProps2 = image2->GetImageIOProperties();

	ImageBoundingProperty mergedBound;

	auto image1ExtentToSpacingRatioX = (ioProps1.extent[1] - ioProps1.extent[0]) * ioProps1.spacing[0];
	auto image2ExtentToSpacingRatioX = (ioProps2.extent[1] - ioProps2.extent[0]) * ioProps2.spacing[0];
	auto isImage1RatioXGreaterThanImage2 = image1ExtentToSpacingRatioX > image2ExtentToSpacingRatioX;

	mergedBound.Extent[0] = isImage1RatioXGreaterThanImage2 ? ioProps1.extent[0] : ioProps2.extent[0];
	mergedBound.Extent[1] = isImage1RatioXGreaterThanImage2 ? ioProps1.extent[1] : ioProps2.extent[1];
	mergedBound.Spacing[0] = isImage1RatioXGreaterThanImage2 ? ioProps1.spacing[0] : ioProps2.spacing[0];

	auto image1ExtentToSpacingRatioY = (ioProps1.extent[3] - ioProps1.extent[2]) * ioProps1.spacing[1];
	auto image2ExtentToSpacingRatioY = (ioProps2.extent[3] - ioProps2.extent[2]) * ioProps2.spacing[1];
	auto isImage1RatioYGreaterThanImage2 = image1ExtentToSpacingRatioY > image2ExtentToSpacingRatioY;
	mergedBound.Extent[2] = isImage1RatioYGreaterThanImage2 ? ioProps1.extent[2] : ioProps2.extent[2];
	mergedBound.Extent[3] = isImage1RatioYGreaterThanImage2 ? ioProps1.extent[3] : ioProps2.extent[3];
	mergedBound.Spacing[1] = isImage1RatioYGreaterThanImage2 ? ioProps1.spacing[1] : ioProps2.spacing[1];

	auto image1ExtentToSpacingRatioZ = (ioProps1.extent[5] - ioProps1.extent[4]) * ioProps1.spacing[2];
	auto image2ExtentToSpacingRatioZ = (ioProps2.extent[5] - ioProps2.extent[4]) * ioProps2.spacing[2];
	auto isImage1RatioZGreaterThanImage2 = image1ExtentToSpacingRatioZ > image2ExtentToSpacingRatioZ;
	mergedBound.Extent[4] = isImage1RatioZGreaterThanImage2 ? ioProps1.extent[4] : ioProps2.extent[4];
	mergedBound.Extent[5] = isImage1RatioZGreaterThanImage2 ? ioProps1.extent[5] : ioProps2.extent[5];
	mergedBound.Spacing[2] = isImage1RatioZGreaterThanImage2 ? ioProps1.spacing[2] : ioProps2.spacing[2];

	return mergedBound;
}