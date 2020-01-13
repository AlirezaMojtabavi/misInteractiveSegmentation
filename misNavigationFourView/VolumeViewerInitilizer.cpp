#include "stdafx.h"
#include "VolumeViewerInitilizer.h"
#include "misImageToTextureMap.h"
#include "ICornerProperties.h"
#include "ICursorService.h"
#include "misApplicationSetting.h"


VolumeViewerInitilizer::VolumeViewerInitilizer(std::shared_ptr<IVolume3DRenderer> viewer,
                                               std::shared_ptr<IRepresentationFactory> representationFactory,
                                               misSurgeryDirectionViewerType currentTypeDir)
	: m_viewer(viewer),
	  m_RepresentationFactory(representationFactory),
	  m_CurrentTypeDir(currentTypeDir)
{
}



void VolumeViewerInitilizer::Initialize(std::shared_ptr<IImage> tempImage)
{
	misImageToTextureMap* TextureHandler = misImageToTextureMap::GetInstance();
	misOpenglTexture* pTexture = TextureHandler->LookUpTexture(tempImage);
	if (pTexture)
	{
		double* TableRange = pTexture->GetTableRange();
		if (TableRange)
		{
			auto extent = pTexture->GetTexturePropertyStrct().GetExtent();
			auto spacing = pTexture->GetTexturePropertyStrct().Spacing;
			ImageBoundingProperty imageBoundingProp;

			for (int i = 0; i < 6; i++)
			{
				imageBoundingProp.Extent[i] = extent[i];
			}

			for (int i = 0; i < 3; i++)
			{
				imageBoundingProp.Spacing[i] = spacing[i];
			}

			m_viewer->GetCornerProperties()->SetImageBounding(imageBoundingProp);
		}
	}
	if (!m_viewer->GetMainRepresentation())
	{
		auto representation = m_RepresentationFactory->CreateRepresentation(m_CurrentTypeDir.orientation, m_CurrentTypeDir.viewerType);
		m_viewer->SetMainRepresentation(representation, m_CurrentTypeDir.orientation);
		const auto settingContainer = misApplicationSetting::GetInstance()->GetSettingsContainer();
		const auto toleranceFactor = settingContainer->GetDouble("misVisualizationSetting/WidgetProperties/WidgetPickingTolerance");
		m_viewer->InitializeWidget(m_WidgetType, toleranceFactor);
		auto pos = tempImage->GetImageCenter();
		m_viewer->GetCornerProperties()->SetCurrentPosition(pos.Elements());
		m_viewer->GetCursorService()->UpdateWidgetPosition();
		m_viewer->GetCursorService()->Set3DInteractionCapturedFlag(false);

	}

}

void VolumeViewerInitilizer::SetWidgetType(misCursorType val)
{
	m_WidgetType = val;
}
