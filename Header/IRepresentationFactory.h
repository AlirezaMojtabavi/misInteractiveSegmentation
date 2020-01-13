#pragma once
class IRepresentationFactory
{
public:
	virtual std::shared_ptr<IRepresentation> CreateRepresentation(IMAGEORIENTATION pOrientation, misViewerTypeDirection viewerType) = 0;
};