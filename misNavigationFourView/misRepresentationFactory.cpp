#include "stdafx.h"

#include <algorithm>
#include "IRepresentation.h"
#include "misEnumUtilities.h"
#include "misPlanarRepresentation.h"
#include "misRepresentationFactory.h"
#include "misVoreenRepresentation.h"
#include "misImageSlicerMapper.h"
#include "misApplicationSetting.h"
#include "RangeMapper.h"

misRepresentationFactory::misRepresentationFactory()
{
	auto fromRange = std::make_pair(0., 1.);
	auto toRange = std::make_pair(0.6, 4.);
	m_RangeMapper = std::make_unique<parcast::RangeMapper>(fromRange, toRange);
}

std::shared_ptr<IRepresentation> misRepresentationFactory::CreateRepresentation(IMAGEORIENTATION orientation, misViewerTypeDirection viewerType)
{
	if (orientation != UNKnownDirection)
	{
		std::string RepType = misEnumUtilities::ConvertImageOrientationTypeEnumToString(orientation, true);
		auto sliceMapper = new misImageSlicerMapper(orientation);
		return std::make_shared<misPlanarRepresentation>(RepType, sliceMapper);
	}
	auto representation = std::make_shared<misVoreenRepresentation>();
	const auto settingContainer = misApplicationSetting::GetInstance()->GetSettingsContainer();
	const auto normalizedSampleRate = settingContainer->GetDouble("RenderingSampleRate");
	double sampleRate;
	try
	{
		sampleRate = m_RangeMapper->Map(normalizedSampleRate);
	}
	catch (parcast::RangeMapperException)
	{
		const auto clampedSampleRate = tgt::clamp(normalizedSampleRate,0.0,1.0);
		sampleRate = m_RangeMapper->Map(clampedSampleRate);
	}
	representation->SetSampleRate(sampleRate);
	return representation;
}
