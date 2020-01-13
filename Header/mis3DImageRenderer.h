#pragma once
#include "I3DImageRenderer.h"
#include "misSurgeryDirectionViewerType.h"
#include "IVolumeViewerInitilizer.h"

class IVolume3DRenderer;
class IWidgetConfigure;
class IViewerFactory;
class mis3DImageRenderer :	public I3DImageRenderer
{
public:
	mis3DImageRenderer(std::shared_ptr<IVolume3DRenderer> viewer,
		misSurgeryDirectionViewerType currentTypeDir, 
		std::shared_ptr<IViewerFactory> representationFactory, std::shared_ptr<IVolumeViewerInitilizer> volumeInitializer);

	virtual void ShowImages(ImageDependencyListTypes newImageDataDependencies) override;


	virtual void Reset() override;




	virtual void SetWidgetType(misCursorType val) override;


	virtual void SetImage(std::shared_ptr<IImage> pImage) override;

private:
	void InitilizeRepresentation();

	void ShowImageIn3D(ImageDependencyListTypes &newImageDataDependencies, int index);

	

	std::shared_ptr<IVolume3DRenderer> m_viewer;
	ImageDependencyListTypes m_CurrentImageDataDependencies;
	misSurgeryDirectionViewerType m_CurrentTypeDir;
	misCursorType m_WidgetType;
	std::shared_ptr<IWidgetConfigure> m_WidgetConfigure;
	std::shared_ptr<IViewerFactory> m_RepresentationFactory;
	std::shared_ptr<IVolumeViewerInitilizer> m_VolumeInitializer;
};

