#include "stdafx.h"
#include "..\Header\mis3DImageRenderer.h"
#include "misImageToTextureMap.h"
#include "IVolume3DRenderer.h"
#include "misCursorService.h"
#include "misCornerProperties.h"
#include "I3DViewer.h"
#include "IWidgetConfigure.h"
#include "IViewerFactory.h"
#include "VolumeViewerInitilizer.h"
#include "misApplicationSetting.h"

mis3DImageRenderer::mis3DImageRenderer(std::shared_ptr<IVolume3DRenderer> viewer, 
	misSurgeryDirectionViewerType currentTypeDir, std::shared_ptr<IViewerFactory> representationFactory,std::shared_ptr<IVolumeViewerInitilizer> volumeInitializer)
	:m_viewer(viewer), 
	m_CurrentTypeDir(currentTypeDir), 
	m_RepresentationFactory(representationFactory),
	m_VolumeInitializer(volumeInitializer)
{
}



void mis3DImageRenderer::ShowImages(ImageDependencyListTypes newImageDataDependencies)
{
	int newSize = newImageDataDependencies.size();
	if (newSize == 0)
		return;

	int currentSize = m_CurrentImageDataDependencies.size();
	int maxSize = std::max(newSize, currentSize);
	if (maxSize != newSize)
		newImageDataDependencies.resize(maxSize);
	else if (maxSize != currentSize)
		m_CurrentImageDataDependencies.resize(maxSize);

	for (auto& imageDep : newImageDataDependencies)
		if (!imageDep)
			imageDep = std::make_shared<misCompeleteImageDependencies>();
	for (auto& imageDep : m_CurrentImageDataDependencies)
		if (!imageDep)
			imageDep = std::make_shared<misCompeleteImageDependencies>();

	int planeIndex = 0;
	for (int index = 0; index < newImageDataDependencies.size(); index++)
	{
		if (!newImageDataDependencies[index]->GetImage())
			continue;
		ShowImageIn3D(newImageDataDependencies, index);
		planeIndex++;
	}
	m_CurrentImageDataDependencies = newImageDataDependencies;

}

void mis3DImageRenderer::Reset()
{
	m_CurrentImageDataDependencies.clear();
 }

 

void mis3DImageRenderer::SetWidgetType(misCursorType val)
{
	m_WidgetType = val;
}

void mis3DImageRenderer::SetImage(std::shared_ptr<IImage> pImage)
 {
	m_viewer->Get3DViewer()->GetWindow()->GetRenderWindow()->MakeCurrent();
	misImageToTextureMap*	TextureHandler = misImageToTextureMap::GetInstance();
	misOpenglTexture* imageTexure = TextureHandler->LookUpTexture(pImage);
	const auto settingContainer = misApplicationSetting::GetInstance()->GetSettingsContainer();
	const auto toleranceFactor = settingContainer->GetDouble("misVisualizationSetting/WidgetProperties/WidgetPickingTolerance");
	m_viewer->InitializeWidget(m_WidgetType, toleranceFactor);
	m_WidgetConfigure->PlaceWidgetatCenter(FirstImage, pImage);
}

void mis3DImageRenderer::ShowImageIn3D(ImageDependencyListTypes &newImageDataDependencies, int index)
{
	std::shared_ptr<IImage> tempImage = newImageDataDependencies[index]->GetImage();
	if (!tempImage)
		return;
	bool imageChnaged = m_CurrentImageDataDependencies[index]->GetObjectUID() != newImageDataDependencies[index]->GetObjectUID();
	if (!imageChnaged)
		return;
	m_VolumeInitializer->Initialize(tempImage);
	return;
}
 