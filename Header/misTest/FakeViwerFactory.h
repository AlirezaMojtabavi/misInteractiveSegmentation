#pragma once
#include "IViewerFactory.h"
#include "MockRepresentation.h"
#include "MockRepresentationFactory.h"

class FakeViwerFactory :public IViewerFactory
{
public:
	std::shared_ptr<misVolumeSlicer> CreateImageViewer(std::shared_ptr<Iwindows> pWindow, int index,
		misSurgeryDirectionViewerType currentViewerProp, double offset, bool) override;
	std::shared_ptr<IVolume3DRenderer> CreateVolumeViewer(std::shared_ptr<Iwindows> pWindow, int index,
		misSurgeryDirectionViewerType currentViewerProp, bool) override;

	std::shared_ptr<IRepresentationFactory> GetRepresentationFactory() const override;
};

inline std::shared_ptr<misVolumeSlicer> FakeViwerFactory::CreateImageViewer (std::shared_ptr<Iwindows> pWindow, int index,
	misSurgeryDirectionViewerType currentViewerProp, double offset, bool)
{
	return {};
}

inline std::shared_ptr<IVolume3DRenderer> FakeViwerFactory::CreateVolumeViewer(std::shared_ptr<Iwindows> pWindow,
	int index, misSurgeryDirectionViewerType currentViewerProp, bool)
{
	return {};
}



inline std::shared_ptr<IRepresentationFactory> FakeViwerFactory::GetRepresentationFactory() const
{
	return {};
}
 
