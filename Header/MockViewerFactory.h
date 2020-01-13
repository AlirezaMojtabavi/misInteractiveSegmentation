#pragma once

#include "IViewerFactory.h"
#include "misSurgeryDirectionViewerType.h"

MOCK_BASE_CLASS(MockViewerFactory, IViewerFactory)
{
	MOCK_NON_CONST_METHOD(CreateImageViewer,  5,  std::shared_ptr<misVolumeSlicer>(std::shared_ptr<Iwindows>, int,misSurgeryDirectionViewerType , double, bool));
	MOCK_NON_CONST_METHOD(CreateVolumeViewer, 4, std::shared_ptr<IVolume3DRenderer>(std::shared_ptr<Iwindows>, int, misSurgeryDirectionViewerType,bool ));
	MOCK_NON_CONST_METHOD(CreateRepresentation, 2, std::shared_ptr<IRepresentation>(IMAGEORIENTATION pOrientation,
		misViewerTypeDirection viewerType));
	MOCK_CONST_METHOD(GetRepresentationFactory, 0, std::shared_ptr<IRepresentationFactory>());
	MOCK_NON_CONST_METHOD(CreatePanoramicViewer, 2, std::shared_ptr<misPanoramicViewer>(std::shared_ptr<Iwindows>, int));
};

