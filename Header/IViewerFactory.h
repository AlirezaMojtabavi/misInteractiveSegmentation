#pragma once

class IRepresentationFactory;
class misVolumeSlicer;
class misPanoramicViewer;
struct misSurgeryDirectionViewerType;
enum IMAGEORIENTATION;

class IViewerFactory
{
public:
	virtual ~IViewerFactory() = default;
	virtual std::shared_ptr<misVolumeSlicer> CreateImageViewer(std::shared_ptr<Iwindows> pWindow,
	                                                           int index,
	                                                           misSurgeryDirectionViewerType currentViewerProp,
	                                                           double VisibilityMarginInAnatomicalPlanesDirection,
	                                                           bool displayCross) = 0;
	virtual std::shared_ptr<IVolume3DRenderer> CreateVolumeViewer(std::shared_ptr<Iwindows> pWindow, int index,
	                                                              misSurgeryDirectionViewerType currentViewerProp,
	                                                              bool displayCross) = 0;
	virtual std::shared_ptr<IRepresentationFactory> GetRepresentationFactory() const = 0;
};
