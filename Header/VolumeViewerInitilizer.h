#pragma once
#include "IVolumeViewerInitilizer.h"
#include "IVolume3DRenderer.h"
#include "IViewerFactory.h"
#include "misSurgeryDirectionViewerType.h"
#include "IRepresentationFactory.h"


class VolumeViewerInitilizer :
	public IVolumeViewerInitilizer
{
public:
	VolumeViewerInitilizer(std::shared_ptr<IVolume3DRenderer> viewer,
	                       std::shared_ptr<IRepresentationFactory> representationFactory,
	                       misSurgeryDirectionViewerType currentTypeDir);

	virtual void Initialize(std::shared_ptr<IImage> tempImage) override;
	void SetWidgetType(misCursorType val) override;
private:
	std::shared_ptr<IVolume3DRenderer> m_viewer;
	std::shared_ptr<IRepresentationFactory> m_RepresentationFactory;
	misSurgeryDirectionViewerType m_CurrentTypeDir;
	misCursorType m_WidgetType;
};
