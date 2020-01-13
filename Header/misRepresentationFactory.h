#pragma once
#include "IRepresentationFactory.h"
#include "RangeMapper.h"

class misRepresentationFactory :public IRepresentationFactory
{

public:
	misRepresentationFactory();
	std::shared_ptr<IRepresentation> CreateRepresentation(IMAGEORIENTATION pOrientation, misViewerTypeDirection viewerType) override;

private:
	std::unique_ptr<parcast::RangeMapper> m_RangeMapper;

};